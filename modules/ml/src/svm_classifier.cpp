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


#include <ml/svm_classifier.hpp>

#include <opencv2/ml.hpp>

#include <cassert>
#include <string>
#include <unordered_set>

namespace ssig {

  SVMClassifier::SVMClassifier() {
    // Constructor
  }

  SVMClassifier::~SVMClassifier() {
    // Destructor
  }

  std::unordered_map<int, int> SVMClassifier::getLabelsOrdering() const {
    return {{1, 0}, {-1, 1}};
  }

  void SVMClassifier::setup(const cv::Mat_<float>& input) {
    mSamples = input;
    cv::TermCriteria termCrit(mTermType, mMaxIterations, mEpsilon);

    if (!mWeights.empty()) {
      mClassWeights = cv::Mat::ones(
        static_cast<int>(mWeights.size()), 1, CV_32F);
      for (auto& it : mWeights) {
        mClassWeights.at<float>(it.first) = it.second;
      }
      mWeights.clear();
    }

    mSvm = cv::ml::SVM::create();
    mSvm->setC(mC);
    mSvm->setType(mModelType);
    mSvm->setKernel(mKernelType);
    mSvm->setDegree(mDegree);
    if (!mClassWeights.empty()) mSvm->setClassWeights(mClassWeights);
    mSvm->setTermCriteria(termCrit);
    mSvm->setGamma(mGamma);
    mSvm->setCoef0(mCoef);
    mSvm->setNu(mNu);
    mSvm->setP(mP);
  }

  void SVMClassifier::addLabels(const cv::Mat_<int>& labels) {
    std::unordered_set<int> labelsSet;
    for (int r = 0; r < labels.rows; ++r)
      labelsSet.insert(labels[r][0]);
    if (labelsSet.size() > 2) {
      std::runtime_error(std::string("Number of Labels is greater than 2.\n") +
        "This is a binary classifier!\n");
    }
    mLabels = labels;
  }

  void SVMClassifier::learn(
    const cv::Mat_<float>& input,
    const cv::Mat_<int>& labels) {
    setup(input);
    assert(!labels.empty());
    addLabels(labels);

    if (mCvEnabled) {
      auto data = cv::ml::TrainData::create(
        mSamples, cv::ml::ROW_SAMPLE, mLabels);
      mSvm->trainAuto(data, mKfolds);
    } else {
      mSvm->train(mSamples, cv::ml::ROW_SAMPLE, mLabels);
    }
  }

  int SVMClassifier::predict(
    const cv::Mat_<float>& inp,
    cv::Mat_<float>& resp) const {
    cv::Mat_<float> label;
    mSvm->predict(inp, resp, cv::ml::StatModel::RAW_OUTPUT);
    mSvm->predict(inp, label);
    cv::Mat_<float> ans;
    ans.create(resp.rows, 2);
    for (int r = 0; r < resp.rows; ++r) {
      if (label[r][0] * resp[r][0] < 0) {
        ans[r][0] = -1 * resp[r][0];
        ans[r][1] = resp[r][0];
      } else {
        ans[r][0] = resp[r][0];
        ans[r][1] = -1 * resp[r][0];
      }
    }
    resp = ans;

    int labelIdx = ans[0][0] > 0 ? 1 : -1;

    return inp.rows > 1 ? 0 : labelIdx;
  }

  cv::Mat_<int> SVMClassifier::getLabels() const {
    return mLabels;
  }

  void SVMClassifier::setClassWeights(
    const int classLabel,
    const float weight) {
    mWeights[classLabel] = weight;
  }

  bool SVMClassifier::empty() const {
    return mSvm.empty();
  }

  bool SVMClassifier::isTrained() const {
    return mSvm->isTrained();
  }

  bool SVMClassifier::isClassifier() const {
    return mSvm->isClassifier();
  }

  void SVMClassifier::load(const std::string& filename,
    const std::string& nodename) {
    cv::FileStorage fs(filename, cv::FileStorage::READ);
    auto node = fs[nodename];
    read(node);
  }

  void SVMClassifier::save(const std::string& filename,
    const std::string& nodename) const {
    cv::FileStorage fs(filename, cv::FileStorage::WRITE);

    fs << nodename << "{";
    write(fs);
    fs << "}";
  }

  void SVMClassifier::read(const cv::FileNode& fn) {
    mSvm = cv::ml::SVM::create();
    mSvm->read(fn);
  }

  void SVMClassifier::write(cv::FileStorage& fs) const {
    mSvm->write(fs);
  }

  Classifier* SVMClassifier::clone() const {
    auto copy = new SVMClassifier();
    copy->setMaxIterations(getMaxIterations());
    copy->setC(getC());
    copy->setCoef(getCoef());
    copy->setDegree(getDegree());
    copy->setGamma(getGamma());
    copy->setKernelType(getKernelType());
    copy->setModelType(getModelType());
    copy->setNu(getNu());
    copy->setEpsilon(getEpsilon());
    copy->setTermType(getTermType());
    copy->setP(getP());

    return copy;
  }

  int SVMClassifier::getKernelType() const {
    return mKernelType;
  }

  void SVMClassifier::setKernelType(int kernelType) {
    mKernelType = kernelType;
  }

  int SVMClassifier::getModelType() const {
    return mModelType;
  }

  void SVMClassifier::setModelType(int modelType) {
    mModelType = modelType;
  }

  float SVMClassifier::getC() const {
    return mC;
  }

  void SVMClassifier::setC(float c) {
    mC = c;
  }

  float SVMClassifier::getGamma() const {
    return mGamma;
  }

  void SVMClassifier::setGamma(float gamma) {
    mGamma = gamma;
  }

  float SVMClassifier::getP() const {
    return mP;
  }

  void SVMClassifier::setP(float p) {
    mP = p;
  }

  float SVMClassifier::getNu() const {
    return mNu;
  }

  void SVMClassifier::setNu(float nu) {
    mNu = nu;
  }

  float SVMClassifier::getCoef() const {
    return mCoef;
  }

  void SVMClassifier::setCoef(float coef) {
    mCoef = coef;
  }

  float SVMClassifier::getDegree() const {
    return mDegree;
  }

  void SVMClassifier::setDegree(float degree) {
    mDegree = degree;
  }

  size_t SVMClassifier::getCrossValidationState() const {
    return mCvEnabled? mKfolds : 0;
  }

  void SVMClassifier::setCrossValidationState(int kfolds) {
    mCvEnabled = true;
    mKfolds = kfolds;
  }
}  // namespace ssig


