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

#include "ssiglib/ml/pls.hpp"

#include <random>
#include <map>
#include <utility>
#include <vector>
#include <string>

#include <ssiglib/core/math.hpp>
#include <opencv2/ml.hpp>

namespace ssig {

// cv::Ptr<PLS> PLS::create() {
//  return cv::Ptr<PLS>(new PLS);
// }

void PLS::learn(cv::Mat_<float>& X, cv::Mat_<float>& Y, int nfactors) {
  int i;
  float dt;
  int maxsteps, step;
  int nsamples, nfeatures;
  cv::Mat_<float> c, t, u, t0, Vcol, Vrow, w, p, C, U, b_l;
  cv::Mat_<float> tmpM;

  // initially, clear current PLS model (if there is one)
  nsamples = X.rows;
  nfeatures = X.cols;

  if (X.rows != Y.rows) {
    char msg[2048];
    throw(std::invalid_argument(msg));
  }

  maxsteps = 100;
  computeMeanStd(X, cv::ml::COL_SAMPLE, mXmean, mXstd);
  computeZScore(X, mXmean, mXstd);

  computeMeanStd(Y, cv::ml::COL_SAMPLE, mYmean, mYstd);
  computeZScore(Y, mYmean, mYstd);

  mYscaled = Y.clone();

  U.create(nsamples, nfactors);
  mT.create(nsamples, nfactors);
  mP.create(nfeatures, nfactors);
  mW.create(nfeatures, nfactors);
  mB.create(1, nfactors);

  for (i = 0; i < nfactors; i++) {
    cv::normalize(Y.col(0), t, 1, 0, cv::NORM_L2);

    u = t.clone();
    // ReportStatus("Extracting PLS factor %d/%d", i + 1, nfactors);
    step = 0;
    do {
      t0 = t.clone();

      w = X.t() * u;
      cv::normalize(w, w, 1, 0, cv::NORM_L2);

      t = X * w;
      cv::normalize(t, t, 1, 0, cv::NORM_L2);

      c = Y.t() * t;
      cv::normalize(c, c, 1, 0, cv::NORM_L2);

      u = Y * c;

      dt = 0;
      cv::Mat_<float> tempT = t0 - t;
      dt = static_cast<float>(tempT.dot(tempT));

      if (cvIsNaN(static_cast<double>(dt))) {
        char msg[2048];
        throw std::logic_error(msg);
      }
      step++;

      // ReportStatus("Latent Variable #%d, iteration #:%d", i, step);
      // disp(['Latent Variable #',int2str(l),'  Iteration #:',int2str(nstep)])
    } while (dt > 0.000001 && step < maxsteps);

    p = X.t() * t;

    b_l = (t.t() * t).inv() * (u.t() * t);

    mB[0][i] = b_l[0][0];

    p.copyTo(mP.col(i));
    w.copyTo(mW.col(i));

    t.copyTo(mT.col(i));
    u.copyTo(U.col(i));

    // deflation of X and Y
    X = X - (t * p.t());

    Y = Y - (b_l[0][0] * (t * c.t()));
  }
  tmpM = mP.t() * mW;
  mWstar = mW * tmpM.inv();

  tmpM = (mT.t() * mT).inv();
  mBstar = mWstar * tmpM * mT.t() * mYscaled;

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

int PLS::getNFactors() const { return this->mNFactors; }

void PLS::predict(const cv::Mat_<float>& X,
                  cv::Mat_<float>& projX,
                  int nfactors) const {
  if (nfactors > this->mNFactors) {
    char msg[2048];
    throw(std::logic_error(msg));
  }

  projX.create(X.rows, nfactors);

  cv::Mat ZData = X.clone();
  for (int y = 0; y < X.rows; y++) {
    ZData.row(y) = ZData.row(y) - mXmean;
    ZData.row(y) = ZData.row(y) / mXstd;
  }
  projX = ZData * (mWstar.colRange(0, nfactors));
}

void PLS::predict(const cv::Mat_<float>& X, cv::Mat_<float>& ret) const {
  ret.create(X.rows, mBstar.cols);
  for (int y = 0; y < X.rows; y++) {
    cv::Mat_<float> aux = X.row(y);

    if (aux.cols != mXmean.cols) {
      throw std::logic_error("Inconsistent data matrix");
    }

    cv::Mat zData;
    // zscore
    zData = aux - mXmean;
    zData /= mXstd;

    // X * Bstar .* Ydata.std +  Ydata.mean;
    cv::Mat_<float> tmp = zData * mBstar;
    tmp = tmp.mul(mYstd) + mYmean;
    tmp.copyTo(ret.row(y));
  }
}

void PLS::save(cv::FileStorage& storage) const {
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

void PLS::save(std::string filename) const {
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

void PLS::setMatrix(
                    cv::Mat_<float>& input,
                    cv::Mat_<float>& output,
                    std::vector<size_t>& indices) {
  size_t i;

  output.create(0, 0);

  for (i = 0; i < indices.size(); i++) {
    output.push_back(input.row(static_cast<int>(indices[i])));
  }
}

float PLS::regError(cv::Mat_<float>& Y, cv::Mat_<float>& responses) const {
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

cv::Mat_<float> PLS::getXmean() const {
  return mXmean;
}

void PLS::setXmean(const cv::Mat_<float>& xmean) {
  mXmean = xmean;
}

cv::Mat_<float> PLS::getXstd() const {
  return mXstd;
}

void PLS::setXstd(const cv::Mat_<float>& xstd) {
  mXstd = xstd;
}

cv::Mat_<float> PLS::getYmean() const {
  return mYmean;
}

void PLS::setYmean(const cv::Mat_<float>& ymean) {
  mYmean = ymean;
}

cv::Mat_<float> PLS::getYstd() const {
  return mYstd;
}

void PLS::setYstd(const cv::Mat_<float>& ystd) {
  mYstd = ystd;
}

cv::Mat_<float> PLS::getB() const {
  return mB;
}

void PLS::setB(const cv::Mat_<float>& xes) {
  mB = xes;
}

cv::Mat_<float> PLS::getT() const {
  return mT;
}

void PLS::setT(const cv::Mat_<float>& xes) {
  mT = xes;
}

cv::Mat_<float> PLS::getP() const {
  return mP;
}

void PLS::setP(const cv::Mat_<float>& xes) {
  mP = xes;
}

cv::Mat_<float> PLS::getW() const {
  return mW;
}

void PLS::setW(const cv::Mat_<float>& xes) {
  mW = xes;
}

cv::Mat_<float> PLS::getWstar() const {
  return mWstar;
}

void PLS::setWstar(const cv::Mat_<float>& wstar) {
  mWstar = wstar;
}

cv::Mat_<float> PLS::getBstar() const {
  return mBstar;
}

void PLS::setBstar(const cv::Mat_<float>& bstar) {
  mBstar = bstar;
}
}  // namespace ssig
