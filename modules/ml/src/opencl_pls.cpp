/*L*****************************************************************************
*
*  Copyright (c) 2015, Smart Surveillance Interest Group, all rights reserved.
*
*  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
*
*  By downloading, copying, installing or using the software you agree to this
*  license. If you do not agree to this license, do not download, install, copy
*  or use the software.
*
*                Software License Agreement (BSD License)
*             For Smart Surveillance Interest Group Library
*                         http://ssig.dcc.ufmg.br
*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions are met:
*
*    1. Redistributions of source code must retain the above copyright notice,
*       this list of conditions and the following disclaimer.
*
*    2. Redistributions in binary form must reproduce the above copyright
*       notice, this list of conditions and the following disclaimer in the
*       documentation and/or other materials provided with the distribution.
*
*    3. Neither the name of the copyright holder nor the names of its
*       contributors may be used to endorse or promote products derived from
*       this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
*  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
*  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
*  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
*  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
*  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
*  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
*  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
*  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
*  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
*  POSSIBILITY OF SUCH DAMAGE.
*****************************************************************************L*/
// c++

// opencv
#include <opencv2/core.hpp>
#include <opencv2/core/ocl.hpp>
// ssiglib
#include "ssiglib/core/math.hpp"
#include "ssiglib/ml/opencl_pls.hpp"


namespace ssig {

cv::Ptr<OpenClPLS> OpenClPLS::create() {
  return cv::makePtr<OpenClPLS>();
}

void OpenClPLS::learn(
  cv::Mat_<float>& Xmat,
  cv::Mat_<float>& Ymat,
  int nfactors) {
  cv::ocl::setUseOpenCL(true);
  cv::UMat X, Y;
  Xmat.copyTo(X);
  Ymat.copyTo(Y);

  int i;
  float dt;
  int maxsteps, step;
  int nsamples, nfeatures;
  cv::UMat c, t, u, t0, Vcol, Vrow, w, p, C, U, b_l;
  cv::UMat tmpM;

  nsamples = X.rows;
  nfeatures = X.cols;

  if (X.rows != Y.rows) {
    char msg[2048];
    throw(std::invalid_argument(msg));
  }

  maxsteps = 100;
  cv::UMat uAux;

  clComputeMeanStd(X, cv::ml::COL_SAMPLE, mXmean, mXstd);
  clComputeZScore(X, mXmean, mXstd);

  clComputeMeanStd(Y, cv::ml::COL_SAMPLE, mYmean, mYstd);
  clComputeZScore(Y, mYmean, mYstd);

  Y.copyTo(mYscaled);

  U.create(nsamples, nfactors, CV_32F);
  C.create(1, nfactors, CV_32F);
  mT.create(nsamples, nfactors, CV_32F);
  mP.create(nfeatures,
            nfactors, CV_32F);
  mW.create(nfeatures,
            nfactors, CV_32F);
  mB.create(1, nfactors, CV_32F);

  for (i = 0; i < nfactors; i++) {
    cv::normalize(Y.col(0), t, 1, 0, cv::NORM_L2);

    u = t.clone();

    step = 0;
    do {
      t0 = t.clone();

      cv::gemm(X, u, 1, cv::noArray(), 0, tmpM, cv::GEMM_1_T);
      cv::normalize(tmpM, w, 1, 0, cv::NORM_L2);

      cv::gemm(X, w, 1, cv::noArray(), 0, tmpM);
      cv::normalize(tmpM, t, 1, 0, cv::NORM_L2);

      cv::gemm(Y, t, 1, cv::noArray(), 0, tmpM, cv::GEMM_1_T);
      cv::normalize(tmpM, c, 1, 0, cv::NORM_L2);

      cv::gemm(Y, c, 1, cv::noArray(), 0, u);

      dt = 0;
      cv::subtract(t0, t, uAux);
      uAux = uAux.dot(uAux);
      dt = static_cast<float>(cv::sum(uAux)[0]);

      if (cvIsNaN(static_cast<double>(dt))) {
        char msg[2048];
        throw std::logic_error(msg);
      }

      step++;
      // ReportStatus("Latent Variable #%d, iteration #:%d", i, step);
      // disp(['Latent Variable #',int2str(l),'  Iteration #:',int2str(nstep)])
    } while (dt > 0.000001 && step < maxsteps);

    cv::gemm(X, t, 1, cv::noArray(), 0, p, cv::GEMM_1_T);

    // b_l=((t'*t)^(-1))*(u'*t); // ||t|| = 1
    // b_l = MultiplyVectorTransposedbyVector(u, t);
    cv::mulTransposed(t, b_l, true);

    cv::gemm(u, t, 1, cv::noArray(), 0, uAux, cv::GEMM_1_T);
    cv::gemm(b_l.inv(), uAux, 1, cv::noArray(), 0, b_l);

    // store matrices
    b_l.row(0).copyTo(mB.col(i));

    p.copyTo(mP.col(i));
    w.copyTo(mW.col(i));

    t.copyTo(mT.col(i));
    u.copyTo(U.col(i));

    // deflation of X and Y
    cv::gemm(t, p, 1, cv::noArray(), 0, uAux, cv::GEMM_2_T);
    cv::subtract(X, uAux, X);

    cv::gemm(t, c, 1, cv::noArray(), 0, uAux, cv::GEMM_2_T);
    float auxScalar = (mB.col(i)).getMat(0).at<float>(0);

    uAux.mul(cv::UMat::eye(uAux.size(), CV_32F), auxScalar);

    cv::subtract(Y, uAux, Y);
  }

  cv::gemm(mP, mW, 1, cv::noArray(), 0, tmpM, cv::GEMM_1_T);
  cv::gemm(mW, tmpM.inv(), 1, cv::noArray(), 0, mWstar);

  cv::mulTransposed(mT, tmpM, true);
  tmpM = tmpM.inv();

  cv::gemm(mT, mYscaled, 1, cv::noArray(), 0, uAux, cv::GEMM_1_T);
  cv::gemm(tmpM, uAux, 1, cv::noArray(), 0, uAux);
  cv::gemm(mWstar, uAux, 1, cv::noArray(), 0, mBstar);

  // set max number of factors
  this->mNFactors = nfactors;

  cv::ocl::setUseOpenCL(false);
}

void OpenClPLS::predict(
  const cv::Mat_<float>& X,
  cv::Mat_<float>& projX,
  int nfactors) {

  cv::UMat aux, aux2;
  int i, y;

  if (nfactors > this->mNFactors) {
    char msg[2048];
    throw(std::logic_error(msg));
  }

  projX.create(X.rows, nfactors);

  for (y = 0; y < X.rows; y++) {
    X.row(y).copyTo(aux);
    // zscore
    cv::subtract(aux, mXmean, mZDataV);
    cv::divide(mZDataV, mXstd, mZDataV);

    for (i = 0; i < nfactors; i++) {
      aux2 = mWstar.col(i);
      projX[y][i] = static_cast<float>(mZDataV.dot(aux2.t()));
    }
  }
}

int OpenClPLS::getNFactors() const {
  return mNFactors;
}

void OpenClPLS::predict(
  const cv::Mat_<float>& X,
  cv::Mat_<float>& ret) {
  ret.create(X.rows, mBstar.cols);

  for (int y = 0; y < X.rows; y++) {
    cv::UMat aux;
    X.row(y).copyTo(aux);

    if (aux.cols != mXmean.cols) {
      throw std::logic_error("Inconsistent data matrix");
    }

    // zscore
    cv::subtract(aux, mXmean, mZDataV);
    cv::divide(mZDataV, mXstd, mZDataV);

    // X * Bstar .* Ydata.std +  Ydata.mean;
    cv::UMat tmp;
    cv::gemm(mZDataV, mBstar, 1, cv::noArray(), 0, tmp);
    cv::gemm(tmp, mYstd, 1, cv::noArray(), 0, tmp);
    cv::add(tmp, mYmean, tmp);
    cv::Mat tmpMat;
    tmp.copyTo(tmpMat);
    for (int i = 0; i < tmp.cols; i++) {
      ret[y][i] = tmpMat.at<float>(0, i);
    }
  }
}

void OpenClPLS::save(std::string filename) const {
  cv::FileStorage storage;

  storage.open(filename, cv::FileStorage::WRITE);
  storage << "root" << "{";
  this->save(storage);
  storage << "}";
  storage.release();
}

void OpenClPLS::save(cv::FileStorage& storage) const {
  if (storage.isOpened() == false) {
    throw std::logic_error("Invalid file storage!");
  }
  cv::Mat Xmean, Xstd, Ymean, Ystd, Wstar, Bstar;
  mXmean.copyTo(Xmean);
  mXstd.copyTo(Xstd);
  mYmean.copyTo(Ymean);
  mYstd.copyTo(Ystd);
  mWstar.copyTo(Wstar);
  mBstar.copyTo(Bstar);


  storage << "PLS"
      << "{";
  storage << "nfactors" << mNFactors;
  storage << "Xmean" << Xmean;
  storage << "Xstd" << Xstd;
  // storage << "b" << b;
  // storage << "T" << T;
  // storage << "P" << P;
  // storage << "W" << W;
  storage << "Wstar" << Wstar;
  storage << "Bstar" << Bstar;
  storage << "Ymean" << Ymean;
  storage << "Ystd" << Ystd;

  storage << "}";
}

void OpenClPLS::load(std::string filename) {
  cv::FileStorage storage;

  storage.open(filename, cv::FileStorage::READ);
  this->load(storage.root());
  storage.release();
}

void OpenClPLS::load(const cv::FileNode& node) {
  cv::FileNode n;

  n = node["PLS"];
  cv::Mat Xmean, Xstd, Ymean, Ystd, Wstar, Bstar;

  n["nfactors"] >> mNFactors;
  n["Xmean"] >> Xmean;
  n["Xstd"] >> Xstd;
  n["Wstar"] >> Wstar;
  n["Bstar"] >> Bstar;
  n["Ymean"] >> Ymean;
  n["Ystd"] >> Ystd;

  Xmean.copyTo(mXmean);
  Xstd.copyTo(mXstd);
  Ymean.copyTo(mYmean);
  Ystd.copyTo(mYstd);
  Wstar.copyTo(mWstar);
  Bstar.copyTo(mBstar);
}

void OpenClPLS::learnWithCrossValidation(
  int folds,
  cv::Mat_<float>& X,
  cv::Mat_<float>& Y,
  int minDims,
  int maxDims,
  int step) {
  // TODO(Ricardo):
}
} // namespace ssig
