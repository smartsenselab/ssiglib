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
#include <algorithm>
#include <vector>
#include <string>
// cv
#include <opencv2/core.hpp>
// ssig

// local
#include "ssiglib/ml/ann_mlp.hpp"

namespace ssig {
MultilayerPerceptron::MultilayerPerceptron() {
  // Constructor
}

float MultilayerPerceptron::computeLoss(
  const std::string& loss,
  const cv::Mat& out,
  const cv::Mat& target) const {
  float avg_loss = 0.f;
  if (loss == "log") {
    cv::Mat m1, m2;
    cv::log(out, m1);
    cv::multiply(target, m1, m1);
    avg_loss = static_cast<float>(
      (cv::sum(m1) / (target.rows * target.cols))[0]);
    cv::subtract(1, out, m2);
    cv::log(m2, m2);
    cv::Mat aux;
    cv::subtract(1, target, aux);
    cv::multiply(aux, m2, m2);
    avg_loss += static_cast<float>(
      (cv::sum(m2) / (target.rows * target.cols))[0]);
    avg_loss = -avg_loss;
  } else if (loss == "quadratic") {
    cv::Mat aux = out - target;
    cv::pow(aux, 2, aux);
    avg_loss = static_cast<float>(cv::sum(aux)[0]);
    avg_loss = avg_loss / (target.rows * target.cols);
  }
  return avg_loss;
}

cv::Ptr<MultilayerPerceptron> MultilayerPerceptron::create() {
  auto ans = cv::Ptr<MultilayerPerceptron>(new MultilayerPerceptron());
  return ans;
}

cv::Ptr<MultilayerPerceptron> MultilayerPerceptron::create(
  const std::vector<std::string>& activationTypes,
  const std::vector<int>& layersLength,
  const std::vector<float>& dropouts) {
  auto ans = cv::Ptr<MultilayerPerceptron>(new MultilayerPerceptron());
  ans->setDropoutWeights(dropouts);
  ans->setActivationsTypes(activationTypes);
  ans->setLayersLength(layersLength);

  return ans;
}

MultilayerPerceptron::~MultilayerPerceptron() {
  // Destructor
}

MultilayerPerceptron::MultilayerPerceptron(const MultilayerPerceptron& rhs) {
  // Constructor Copy
}

template <class MatType>
void MultilayerPerceptron::doForwardPass(
  const MatType& input,
  const std::vector<MatType>& weights,
  const std::vector<std::string>& activationTypes,
  const std::vector<float>& dropout,
  std::vector<MatType>& outputs,
  std::vector<MatType>& activations) const {
  const int numLayers = mNumLayers;
  outputs.resize(numLayers + 1);
  activations.resize(numLayers + 1);

  outputs[0] = input;
  activations[0] = input;

  for (int l = 0; l < numLayers; ++l) {
    cv::Mat layerResponse = weights[l] * activations[l];
    outputs[l] = layerResponse;
    applyActivation(activationTypes[l], layerResponse, layerResponse);
    if (dropout[l] > 0.05f && dropout[l] < 0.8f) {
      cv::multiply(mDropouts[l], layerResponse, layerResponse);
    }
    activations[l + 1] = layerResponse;
  }
}

void MultilayerPerceptron::setWeights(const int startNodes) {
  mWeights.resize(mActivationsTypes.size());
  const int numWeights = static_cast<int>(mWeights.size());
  const int weightEnd = numWeights - 1;
  mWeights[0] = cv::Mat::zeros(
    mNumNodesConfiguration[0] + 1,
    startNodes, CV_32F);
  cv::randn(mWeights[0],
            cv::Mat(1, 1, CV_32F, 0.f),
            cv::Mat(1, 1, CV_32F, 1.f));
  for (int i = 1; i < weightEnd - 1; ++i) {
    const int ncols = mNumNodesConfiguration[i - 1] + 1,
      nrows = mNumNodesConfiguration[i] + 1;
    // plus one due to the bias factor
    mWeights[i] = cv::Mat::zeros(nrows, ncols, CV_32F);
    cv::randn(
      mWeights[i], cv::Mat(1, 1, CV_32F, 0.f),
      cv::Mat(1, 1, CV_32F, 1.f));
  }
  mWeights[weightEnd] = cv::Mat::zeros(
    mNumNodesConfiguration[weightEnd],
    mWeights[weightEnd - 1].rows, CV_32F);
  cv::randn(
    mWeights[weightEnd],
    cv::Mat(1, 1, CV_32F, 0.f),
    cv::Mat(1, 1, CV_32F, 1.f));
}

void MultilayerPerceptron::learn(
  const cv::Mat_<float>& _input,
  const cv::Mat& labels) {
  mIsTrained = false;

  cv::Mat input;
  cv::Mat target = labels.t();

  cv::Mat ones = cv::Mat(_input.rows, 1, CV_32F, 1);
  cv::hconcat(_input, ones, input);
  input = input.t();
  // create weight matrices
  setWeights(input.rows);
  // END Weights
  char* loss_msg =
    "The average loss in the output layer of this epoch is [%g]\n";
  for (int it = 0; it < mMaxIterations; ++it) {
    learnWeights(
      input,
      target,
      mActivationsTypes,
      mDropoutWeights,
      mLayerActivations,
      mWeights);
    cv::Mat out;
    mLayerActivations.back().copyTo(out);

    if (it % 100 == 0) {
      auto avg_loss = computeLoss(mLoss, out, target);
      verboseLog(loss_msg, avg_loss);
    }
  }
  mIsTrained = true;
}

int MultilayerPerceptron::predict(
  const cv::Mat_<float>& _inp,
  cv::Mat_<float>& resp,
  cv::Mat_<int>& labels) const {
  std::vector<cv::Mat> layerOut;
  std::vector<cv::Mat> activations;
  cv::Mat inp;
  cv::Mat ones = cv::Mat(_inp.rows, 1, CV_32F, 1);
  cv::hconcat(_inp, ones, inp);
  inp = inp.t();

  predict(
    inp,
    resp,
    labels,
    activations,
    layerOut);

  return static_cast<int>(NAN);
}

void MultilayerPerceptron::predict(
  const int layerIdx,
  const cv::Mat_<float>& _inp,
  cv::Mat_<float>& resp,
  cv::Mat_<int>& labels) const {
  std::vector<cv::Mat> activations,
                       outputs;
  predict(_inp, resp, labels, activations, outputs);
  resp = activations[layerIdx];
}

void MultilayerPerceptron::predict(
  const cv::Mat& inp,
  cv::Mat& resp,
  cv::Mat& labels,
  std::vector<cv::Mat>& activations,
  std::vector<cv::Mat>& outputs) const {
  doForwardPass<cv::Mat>(
    inp,
    mWeights,
    mActivationsTypes,
    mDropoutWeights,
    outputs,
    activations);
  resp = activations.back().t();
  labels = cv::Mat(resp.rows, 1, CV_32S, -1);
  for (int r = 0; r < resp.rows; ++r) {
    int maxIdx[2];
    cv::minMaxIdx(resp.row(r), nullptr, nullptr, nullptr, maxIdx);
    labels.at<int>(r) = maxIdx[1];
  }
}

void MultilayerPerceptron::addLayer(
  const int numNodes,
  const int poolingSize,
  const float dropout,
  const std::string& activation) {
  CV_Assert(numNodes > 0);
  if (poolingSize > 0) {
    // TODO(Ricardo): pooling
  }

  mDropoutWeights.push_back(dropout);
  mNumNodesConfiguration.push_back(numNodes);
  mActivationsTypes.push_back(activation);
}

bool MultilayerPerceptron::empty() const {
  return mWeights.empty();
}

bool MultilayerPerceptron::isTrained() const {
  return mIsTrained;
}

Classifier* MultilayerPerceptron::clone() const {
  return new MultilayerPerceptron(*this);
}

void MultilayerPerceptron::learnWeights(
  const cv::Mat& inputs,
  const cv::Mat& labels,
  const std::vector<std::string>& activationTypes,
  const std::vector<float>& dropout,
  std::vector<cv::Mat>& activations,
  std::vector<cv::Mat>& weights) const {
  const int numLayers = static_cast<int>(weights.size()) + 1;
  CV_Assert(weights.size() == numLayers - 1);
  CV_Assert(activationTypes.size() == numLayers - 1);
  CV_Assert(dropout.size() == numLayers - 1);

  std::vector<cv::Mat> net_out;
  doForwardPass(inputs, weights,
                activationTypes,
                dropout,
                net_out,
                activations);
  std::vector<cv::Mat> errors;
  computeErrors(
    labels,
    activationTypes,
    weights,
    net_out,
    activations,
    errors);
  gradientUpdate<cv::Mat>(
    mLearningRate,
    activations,
    errors,
    weights);
}

template <class MatType>
void MultilayerPerceptron::computeErrors(
  const MatType& target,
  const std::vector<std::string>& activationTypes,
  const std::vector<MatType>& weights,
  const std::vector<MatType>& outputs,
  const std::vector<MatType>& activations,
  std::vector<MatType>& errors) const {
  //////////////////////////////////////////////////////
  const int numLayers = mNumLayers;
  errors.resize(numLayers + 1);
  // this is the derivative of the loss function
  // In the case of quadratic loss:
  // TODO(Ricardo): instead call computeLossDerivative()
  cv::subtract(activations.back(), target, errors.back());
  // TODO(Ricardo): Change this line above to any loss
  for (int L = numLayers - 1; L > 0; --L) {
    MatType aux;
    cv::gemm(weights[L], errors[L + 1], 1,
             cv::noArray(), 0, aux, cv::GEMM_1_T);
    MatType derivative;
    applyDerivative(activationTypes[L - 1], outputs[L - 1], derivative);
    cv::multiply(aux, derivative, errors[L]);
  }
}

template <class MatType>
void MultilayerPerceptron::gradientUpdate(
  const float learningRate,
  const std::vector<MatType>& activations,
  const std::vector<MatType>& errors,
  std::vector<MatType>& weights) const {
  const int len = static_cast<int>(weights.size());
  std::vector<MatType> newWeights(weights.size());
  for (int i = 1; i <= len; ++i) {
    MatType G_l;
    cv::gemm(
      errors[i], activations[i - 1],
      1, cv::noArray(), 1, G_l, cv::GEMM_2_T);
    cv::addWeighted(
      weights[i - 1], 1, G_l, -learningRate, 0, newWeights[i - 1]);
  }
  weights = std::move(newWeights);
}

void MultilayerPerceptron::applyActivation(
  const std::string& type,
  cv::InputArray _inp,
  cv::OutputArray _out) {
  if (type == "relu") {
    relu(_inp, _out);
  } else if (type == "logistic") {
    logistic(_inp, _out);
  } else if (type == "softmax") {
    softmax(_inp, _out);
  } else if (type == "softplus") {
    softplus(_inp, _out);
  } else {
    _inp.copyTo(_out);
  }
}

void MultilayerPerceptron::applyDerivative(
  const std::string& type,
  cv::InputArray _inp,
  cv::OutputArray _out) {
  if (type == "relu") {
    dRelu(_inp, _out);
  } else if (type == "logistic") {
    dLogistic(_inp, _out);
  } else if (type == "softmax") {
    dSoftmax(_inp, _out);
  } else if (type == "softplus") {
    dSoftplus(_inp, _out);
  } else {
    _inp.copyTo(_out);
  }
}

void MultilayerPerceptron::relu(
  const cv::InputArray& _inp,
  cv::OutputArray& _out) {
  if (_inp.isUMat()) {
    cv::UMat inp = _inp.getUMat();
    cv::UMat out;
    cv::max(cv::UMat::zeros(inp.size(), CV_32F), inp, out);
    out.copyTo(_out);
  } else {
    cv::Mat inp = _inp.getMat();
    cv::Mat out = cv::max(0, inp);
    out.copyTo(_out);
  }
}

void MultilayerPerceptron::logistic(
  const cv::InputArray& _inp,
  cv::OutputArray& _out) {
  if (_inp.isUMat()) {
    cv::UMat inp = _inp.getUMat();
    cv::UMat out;
    cv::multiply(-1, inp, out);
    cv::exp(out, out);
    cv::add(1, out, out);
    cv::divide(1, out, out);
    out.copyTo(_out);
  } else {
    cv::Mat inp = _inp.getMat();
    cv::Mat out;
    cv::multiply(-1, inp, out);
    cv::exp(out, out);
    cv::add(1, out, out);
    cv::divide(1, out, out);
    out.copyTo(_out);
  }
}

void MultilayerPerceptron::softmax(
  cv::InputArray _inp,
  cv::OutputArray _out) {
  if (_inp.isUMat()) {
    cv::UMat inp = _inp.getUMat();
    cv::UMat out;
    cv::exp(inp, out);
    for (int c = 0; c < out.cols; ++c) {
      cv::normalize(out.col(c), out.col(c), 1, 0, cv::NORM_L1);
    }
    out.copyTo(_out);
  } else {
    cv::Mat inp = _inp.getMat();
    cv::Mat out;
    cv::exp(inp, out);
    for (int c = 0; c < out.cols; ++c) {
      cv::normalize(out.col(c), out.col(c), 1, 0, cv::NORM_L1);
    }
    out.copyTo(_out);
  }
}

void MultilayerPerceptron::softplus(
  cv::InputArray _inp,
  cv::OutputArray _out) {
  static const float EULER = 2.7182818284590452353602874713527f;
  if (_inp.isUMat()) {
    cv::UMat out;
    cv::exp(_inp, out);
    cv::add(1, out, out);
    cv::log(out, out);
    // cv::UMat aux(out.size(), CV_32F, EULER);
    // cv::log(aux, aux);
    // cv::divide(out, aux, out);
    out.copyTo(_out);
  } else {
    cv::Mat out;
    cv::Mat aux(out.size(), CV_32F, EULER);
    // for finding the natural log
    cv::exp(_inp, out);
    cv::add(1, out, out);
    // cv::log(out, out);
    // cv::log(aux, aux);
    // cv::divide(out, aux, out);
    // ln(x) = log(x) / log(e)
    out.copyTo(_out);
  }
}

void MultilayerPerceptron::dRelu(
  cv::InputArray _inp,
  cv::OutputArray _out) {
  if (_inp.isUMat()) {
    cv::UMat comp_mask;
    cv::UMat local_zeros = cv::UMat::zeros(_inp.size(), CV_32F);
    cv::compare(_inp, local_zeros, comp_mask, CV_CMP_EQ);
    cv::UMat::ones(_inp.size(), CV_32F).copyTo(_out);
    local_zeros.copyTo(_out, comp_mask);
  } else {
    cv::Mat comp_mask;
    cv::Mat local_zeros = cv::Mat::zeros(_inp.size(), CV_32F);
    cv::compare(_inp, local_zeros, comp_mask, CV_CMP_EQ);
    cv::Mat out = cv::Mat::ones(_inp.size(), CV_32F);
    local_zeros.copyTo(out, comp_mask);
    out.copyTo(_out);
  }
}

void MultilayerPerceptron::dSoftplus(
  cv::InputArray _inp,
  cv::OutputArray _out) {
  logistic(_inp, _out);
}

void MultilayerPerceptron::dLogistic(
  cv::InputArray _inp,
  cv::OutputArray _out) {
  if (_inp.isUMat()) {
    cv::UMat out;
    logistic(_inp, out);
    cv::UMat aux;
    cv::subtract(1, out, aux);
    cv::multiply(out, aux, _out);
  } else {
    cv::Mat out;
    logistic(_inp, out);
    cv::Mat aux;
    cv::subtract(1, out, aux);
    cv::multiply(out, aux, _out);
  }
}

void MultilayerPerceptron::dSoftmax(
  cv::InputArray _inp,
  cv::OutputArray _out) {
  // TODO(Ricardo): implement this
}

void MultilayerPerceptron::read(const cv::FileNode& fn) {
  // TODO(Ricardo): implement this
}

void MultilayerPerceptron::write(cv::FileStorage& fs) const {
  // TODO(Ricardo): implement this
}

cv::Mat MultilayerPerceptron::getLabels() const {
  return cv::Mat();
}

cv::Mat MultilayerPerceptron::getWeights(const int layerIndex) {
  return mWeights[layerIndex];
}

std::unordered_map<int, int> MultilayerPerceptron::getLabelsOrdering() const {
  std::unordered_map<int, int> ans;
  return {{0, 1}};
}

float MultilayerPerceptron::getLearningRate() const {
  return mLearningRate;
}

void MultilayerPerceptron::setLearningRate(const float learningRate) {
  mLearningRate = learningRate;
}

int MultilayerPerceptron::getNumLayers() const {
  return mNumLayers;
}

void MultilayerPerceptron::setNumLayers(const int numLayers) {
  mNumLayers = numLayers;
}

std::vector<cv::Mat> MultilayerPerceptron::getWeightMatrices() const {
  return mWeights;
}

void MultilayerPerceptron::setWeights(const std::vector<cv::Mat>& weights) {
  mWeights = weights;
}

std::vector<cv::Mat> MultilayerPerceptron::getDropouts() const {
  return mDropouts;
}

void MultilayerPerceptron::setDropouts(const std::vector<cv::Mat>& dropouts) {
  mDropouts = dropouts;
}

std::vector<cv::Mat> MultilayerPerceptron::getLayerActivations() const {
  return mLayerActivations;
}

void MultilayerPerceptron::setLayerActivations
(const std::vector<cv::Mat>& layerActivations) {
  mLayerActivations = layerActivations;
}

std::vector<cv::Mat> MultilayerPerceptron::getLayerOut() const {
  return mLayerOut;
}

void MultilayerPerceptron::setLayerOut(const std::vector<cv::Mat>& layerOut) {
  mLayerOut = layerOut;
}

std::vector<int> MultilayerPerceptron::getNumNodesConfiguration() const {
  return mNumNodesConfiguration;
}

void MultilayerPerceptron::setLayersLength(
  const std::vector<int>& numNodesConfiguration) {
  mNumNodesConfiguration = numNodesConfiguration;
}

std::vector<std::string> MultilayerPerceptron::getActivationsTypes() const {
  return mActivationsTypes;
}

void MultilayerPerceptron::setActivationsTypes(
  const std::vector<std::string>& activationsTypes) {
  mActivationsTypes = activationsTypes;
}

std::vector<float> MultilayerPerceptron::getDropoutWeights() const {
  return mDropoutWeights;
}

void MultilayerPerceptron::setDropoutWeights(
  const std::vector<float>& dropoutWeights) {
  mDropoutWeights = dropoutWeights;
}
}  // namespace ssig
