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

#include "ml/pls.hpp"

#include <random>
#include <map>
#include <utility>
#include <string>
#include <vector>

#include <core/math.hpp>
#include <opencv2/ml.hpp>

namespace ssig {

void PLS::learn(cv::Mat_<float>& X, cv::Mat_<float>& Y, int nfactors) {
  int i;
  int kk;
  float dt;
  int maxsteps, step;
  int nsamples, nfeatures;
  cv::Mat_<float> c, t, u, t0, Vcol, Vrow, w, p, C, U, b_l;
  cv::Mat_<float> tmpM;

  // initially, clear current PLS model (if there is one)
  // ClearPLS();

  nsamples = X.rows;
  nfeatures = X.cols;

  if (X.rows != Y.rows) {
    char msg[2048];
    throw(std::invalid_argument(msg));
  }

  maxsteps = 100;
  computeMeanStd(X, cv::ml::COL_SAMPLE, mXmean, mXstd);
  computeZScore(X, mXmean, mXstd);

  // Y
  // ymean = new Vector<float> (1);
  // ystd = new Vector<float> (1);
  // mean(Y, ymean);
  // std(Y, ymean, ystd);
  // zscore(Y, ymean, ystd);
  computeMeanStd(Y, cv::ml::COL_SAMPLE, mYmean, mYstd);
  computeZScore(Y, mYmean, mYstd);

  // Yscaled = Y->Copy();
  mYscaled = Y.clone();

  U.create(nsamples, nfactors);   // U = new Matrix<float> (nsamples, nfactor);
  C.create(1, nfactors);          // C = new Vector<float> (nfactor);
  mT.create(nsamples, nfactors);  // T = new Matrix<float> (nsamples, nfactor);
  mP.create(nfeatures,
            nfactors);  // P = new Matrix<float> (nfeatures, nfactor);
  mW.create(nfeatures,
            nfactors);  // W = new Matrix<float> (nfeatures, nfactor);
  mB.create(1, nfactors);

  // sumY2 = SSFMatrixSquare(Y);
  // sumX2 = SSFMatrixSquare(X);

  // printf("\rsumX: %5.3f, sumY: %5.3f", sumX2, sumY2);

  for (i = 0; i < nfactors; i++) {
    // normaliz(Y, t);
    cv::normalize(Y.col(0), t, 1, 0, cv::NORM_L2);

    // CopyVector(t, u);
    u = t.clone();

    // ReportStatus("Extracting PLS factor %d/%d", i + 1, nfactors);

    step = 0;
    do {
      // t0 = CopyVector(t, rY);
      // CopyVector(t, t0);
      t0 = t.clone();

      // w=normaliz(Xres'*u)
      // tmp = MultiplyTransposeMatrixbyVector(X, rX, cX, u, rY);
      // w = normaliz(tmp, cX);
      // free(tmp);
      // MultiplyTransposeMatrixbyVector(X, u, Vcol);
      // normaliz(Vcol, w);
      tmpM = X.t() * u;
      cv::normalize(tmpM, w, 1, 0, cv::NORM_L2);

      // t=normaliz(Xres*w);
      // tmp = MultiplyMatrixbyVector(X, rX, cX, w, cX);
      // free(t);
      // t = normaliz(tmp, rX);
      // free(tmp);
      // MultiplyMatrixbyVector(X, w, Vrow);
      // normaliz(Vrow, t);
      tmpM = X * w;
      cv::normalize(tmpM, t, 1, 0, cv::NORM_L2);

      // c = normaliz(Yres'*t); c is 1xrY
      // tmpscalar = MultiplyVectorTransposedbyVector(Y, rY, t);
      // c = normaliz(&tmpscalar, 1);
      // tmpscalar = MultiplyVectorTransposedbyVector(Y, t);
      // c = tmpscalar/tmpscalar;  //dummy step, because it normalizes a
      // constant
      tmpM = Y.t() * t;
      cv::normalize(tmpM, c, 1, 0, cv::NORM_L2);

      // u=Yres*c
      // free(u);
      // u = MultiplyVectorandScalar(Y, rY, c[0]);
      // MultiplyVectorandScalar(Y, c, u);
      u = Y * c;

      dt = 0;
      for (kk = 0; kk < nsamples; kk++) {
        dt += (t0(kk, 0) - t(kk, 0)) * (t0(kk, 0) - t(kk, 0));
      }
      if (cvIsNaN(static_cast<double>(dt))) {
        char msg[2048];
        throw std::logic_error(msg);
      }

      step++;

      // ReportStatus("Latent Variable #%d, iteration #:%d", i, step);
      // disp(['Latent Variable #',int2str(l),'  Iteration #:',int2str(nstep)])
    } while (dt > 0.000001 && step < maxsteps);

    // p=Xres'*t; p is cX by 1
    // p = MultiplyTransposeMatrixbyVector(X, rX, cX, t, rX);
    // MultiplyTransposeMatrixbyVector(X, t, p);
    p = X.t() * t;

    // b_l=((t'*t)^(-1))*(u'*t); // ||t|| = 1
    // b_l = MultiplyVectorTransposedbyVector(u, t);
    b_l = t.t() * t;
    b_l = b_l.inv() * (u.t() * t);

    // store matrices
    // b[i] = b_l;
    // b->SetElement(i, b_l);
    mB[0][i] = b_l[0][0];

    p.copyTo(mP.col(i));
    w.copyTo(mW.col(i));

    t.copyTo(mT.col(i));
    u.copyTo(U.col(i));

    // c->SetElement(i, c);
    C[0][1] = c[0][0];

    // deflation of X and Y
    // Xres=Xres-t*p';
    // SubtractFromMatrix(X, rX, cX, t, rX, p, cX);
    // SubtractFromMatrix(X, t, p);
    X = X - (t * p.t());

    // Yres=Yres-(b(l)*(t*c'));
    // SubtractFromVector(Y, rY, t, rX, c, 1, b[i]);
    // SubtractFromVector(Y, t, c, b->GetElement(i));
    Y = Y - (mB[0][i] * (t * c.t()));
  }

  // ComputeWstar();
  // Wstar=W*inv(P'*W);
  tmpM = mP.t() * mW;
  mWstar = mW * tmpM.inv();

  // Bstar = Wstar*inv(T'*T)*T'*Y;
  tmpM = (mT.t() * mT).inv();
  mBstar = mWstar * tmpM * mT.t() * mYscaled;
  // computeBstar(nfactors);

  // set max number of factors
  this->mNFactors = nfactors;
}

void PLS::computeBstar(int nfactors) {
  cv::Mat_<float> tmpM;

  if (nfactors > this->mNFactors) {
    char msg[2048];
    throw(std::logic_error(msg));
  }

  tmpM = (mT.colRange(0, nfactors).t() * mT.colRange(0, nfactors)).inv();
  this->mBstar = mWstar.colRange(0, nfactors) * tmpM *
                 mT.colRange(0, nfactors).t() * mYscaled;
}

int PLS::getNFactors() { return this->mNFactors; }

void PLS::predict(const cv::Mat_<float>& X, cv::Mat_<float>& projX,
                  int nfactors) {
  cv::Mat_<float> aux, aux2;
  int i, y;

  if (nfactors > this->mNFactors) {
    char msg[2048];
    throw(std::logic_error(msg));
  }

  projX.create(X.rows, nfactors);

  for (y = 0; y < X.rows; y++) {
    aux = X.row(y);

    // zscore
    mZDataV = aux - mXmean;
    mZDataV /= mXstd;

    for (i = 0; i < nfactors; i++) {
      aux2 = mWstar.col(i);
      projX[y][i] = static_cast<float>(mZDataV.dot(aux2.t()));
    }
  }
}

void PLS::predict(const cv::Mat_<float>& X, cv::Mat_<float>& ret) {
  cv::Mat_<float> aux, tmp;
  int y, i;

  ret.create(X.rows, mBstar.cols);

  for (y = 0; y < X.rows; y++) {
    aux = X.row(y);

    if (aux.cols != mXmean.cols) {
      throw std::logic_error("Inconsistent data matrix");
    }

    // zscore
    mZDataV = aux - mXmean;
    mZDataV /= mXstd;

    // X * Bstar .* Ydata.std) +  Ydata.mean;
    tmp = mZDataV * mBstar;
    tmp = tmp.mul(mYstd) + mYmean;

    for (i = 0; i < tmp.cols; i++) {
      ret[y][i] = tmp[0][i];
    }
  }
}

void PLS::save(cv::FileStorage& storage) {
  if (storage.isOpened() == false) {
    throw std::logic_error("Invalid file storage!");
  }

  storage << "PLS"
          << "{";
  storage << "nfactors" << mNFactors;
  storage << "Xmean" << mXmean;
  storage << "Xstd" << mXstd;
  // storage << "b" << b;
  // storage << "T" << T;
  // storage << "P" << P;
  // storage << "W" << W;
  storage << "Wstar" << mWstar;
  storage << "Bstar" << mBstar;
  storage << "Ymean" << mYmean;
  storage << "Ystd" << mYstd;

  storage << "}";
}

void PLS::load(const cv::FileNode& node) {
  cv::FileNode n;

  n = node["PLS"];

  n["nfactors"] >> mNFactors;
  n["Xmean"] >> mXmean;
  n["Xstd"] >> mXstd;
  // n["b"] >> b;
  // n["T"] >> T;
  // n["P"] >> P;
  // n["W"] >> W;
  n["Wstar"] >> mWstar;
  n["Bstar"] >> mBstar;
  n["Ymean"] >> mYmean;
  n["Ystd"] >> mYstd;
}

void PLS::save(std::string filename) {
  cv::FileStorage storage;

  storage.open(filename, cv::FileStorage::WRITE);
  this->save(storage);
  storage.release();
}

void PLS::load(std::string filename) {
  cv::FileStorage storage;

  storage.open(filename, cv::FileStorage::READ);
  this->load(storage.root());
  storage.release();
}

void PLS::setMatrix(cv::Mat_<float>& input, cv::Mat_<float>& output,
                    std::vector<size_t>& indices) {
  size_t i;

  output.create(0, 0);

  for (i = 0; i < indices.size(); i++) {
    output.push_back(input.row(static_cast<int>(indices[i])));
  }
}

float PLS::regError(cv::Mat_<float>& Y, cv::Mat_<float>& responses) {
  float error = 0.0f;
  int i;

  if (Y.rows != responses.rows) {
    char msg[2048];
    throw std::logic_error(msg);
  }

  for (i = 0; i < Y.rows; i++) {
    error += fabs(Y[i][0] - responses[i][0]);
  }

  return error;
}

void PLS::learnWithCrossValidation(int folds, cv::Mat_<float>& X,
                                   cv::Mat_<float>& Y, int minDims, int maxDims,
                                   int step) {
  std::map<int, float>::iterator it;
  std::vector<size_t> featurePerm;
  std::vector<std::vector<size_t>> permTrain, permTest;
  std::map<int, float> errors;
  size_t nsamples, k;
  int i;
  int j;
  std::vector<float> currErr;  // error for a given number of factors
  float error;
  cv::Mat_<float> Xtmp, Ytmp, Xvalidate, Yvalidate, responses;
  PLS* tmpPLS = nullptr;
  float minError;
  int minIdx;

  if (Y.cols != 1) {
    throw std::length_error(
        "Cross-validation only works for a single response variable!");
  }

  if (X.rows != Y.rows) {
    throw std::length_error("Inconsistent number of samples with responses!");
  }

  nsamples = X.rows;

  // permutation to perform the k-fold
  for (i = 1; i < static_cast<int>(nsamples); ++i) {
    featurePerm.push_back(i);
  }
  std::shuffle(featurePerm.begin(), featurePerm.end(),
               std::default_random_engine());

  for (i = 0; i < static_cast<int>(folds); i++) {
    permTrain.push_back(std::vector<size_t>());
    permTest.push_back(std::vector<size_t>());
  }

  for (i = 0; i < static_cast<int>(featurePerm.size()); i++) {
    for (k = 0; k < static_cast<size_t>(folds); k++) {
      if (i % folds == 0)
        permTest[k].push_back(featurePerm[i]);
      else
        permTrain[k].push_back(featurePerm[i]);
    }
  }

  // run for each fold
  for (k = 0; k < static_cast<size_t>(folds); k++) {
    // compose X matrix
    setMatrix(X, Xtmp, permTrain[k]);

    // compose Y matrix
    setMatrix(Y, Ytmp, permTrain[k]);

    // get validation data
    setMatrix(X, Xvalidate, permTest[k]);
    setMatrix(Y, Yvalidate, permTest[k]);

    // create PLS model
    if (tmpPLS != nullptr) delete tmpPLS;
    tmpPLS = new PLS();

    // estimate model
    // fprintf(stdout, "Building PLS model for fold %llu/%d", k + 1, folds);
    auto xx = Xtmp.clone();
    auto yy = Ytmp.clone();
    tmpPLS->learn(xx, yy, maxDims);

    // run for each number of dimensions
    for (j = minDims; j <= maxDims; j += step) {
      // fprintf(stdout, "CV in PLS [%d factors, fold %llu/%d]", j, k + 1,
      // folds);

      // compute bstar
      tmpPLS->computeBstar(j);

      // project test data
      tmpPLS->predict(Xvalidate, responses);

      // compute the regression error
      error = regError(Yvalidate, responses);

      it = errors.find(j);
      if (it == errors.end())
        errors.insert(std::pair<int, float>(j, error));
      else
        errors[j] += error;
    }
  }

  // search for the smallest error
  minIdx = errors.begin()->first;
  minError = errors.begin()->second;
  it = errors.begin();
  ++it;
  for (; it != errors.end(); ++it) {
    if (it->second < minError) {
      minError = it->second;
      minIdx = it->first;
    }
  }

  if (tmpPLS != nullptr) delete tmpPLS;

  // fprintf(stdout, "Building PLS model with %d factors", minIdx);

  // build the actual model
  this->learn(X, Y, minIdx);
}

}  // namespace ssig
