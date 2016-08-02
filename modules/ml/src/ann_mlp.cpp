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

int MultilayerPerceptron::predict(
  const cv::Mat_<float>& _inp,
  cv::Mat_<float>& resp,
  cv::Mat_<int>& labels) const {
  std::vector<cv::Mat> layerOut;
  std::vector<cv::Mat> activations;
  predict(
          _inp,
          resp,
          labels,
          activations,
          layerOut);

  return NAN;
}

void MultilayerPerceptron::learn(
  const cv::Mat_<float>& _input,
  const cv::Mat& labels) {
  mIsTrained = false;
  for (int it = 0; it < mMaxIterations; ++it) {
    learnWeights(
                 _input,
                 labels,
                 mWeights,
                 mActivationsTypes,
                 mDropoutWeights);
  }
  mIsTrained = true;
}

void MultilayerPerceptron::predict(
  const int layerIdx,
  const cv::Mat_<float>& _inp,
  cv::Mat_<float>& resp,
  cv::Mat_<int>& labels) {
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
  resp = activations.back();
  labels = cv::Mat::zeros(inp.rows, activations.back().cols, CV_32F);
  for (int r = 0; r < resp.rows; ++r) {
    int maxIdx[2];
    cv::minMaxIdx(resp.row(r), nullptr, nullptr, nullptr, maxIdx);
    labels.at<int>(r) == maxIdx[1];
  }
}

cv::Mat MultilayerPerceptron::getLabels() const {
  return cv::Mat();
}

cv::Mat MultilayerPerceptron::getWeights(const int layerIndex) {
  return mWeights[layerIndex];
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
  const std::vector<cv::Mat>& weights,
  const std::vector<std::string>& activationTypes,
  const std::vector<float>& dropout) const {
  const int numLayers = weights.size() + 1;
  CV_Assert(weights.size() == numLayers - 1);
  CV_Assert(activationTypes.size() == numLayers);
  CV_Assert(dropout.size() == numLayers - 1);
  char* loss_msg =
      "The average loss in the output layer of this epoch is [%g]\n";

  std::vector<cv::Mat> activations;
  std::vector<cv::Mat> net_out;
  doForwardPass(inputs, weights,
                activationTypes,
                dropout,
                net_out,
                activations);
  std::vector<cv::Mat> errors;
  auto avg_loss = computeErrors(
                                labels,
                                activationTypes,
                                weights,
                                net_out,
                                activations,
                                errors);
  gradientUpdate<cv::Mat>(
                          mLearningRate,
                          weights,
                          activations,
                          errors);
  verboseLog(loss_msg, avg_loss);
}

template <class MatType>
float MultilayerPerceptron::computeErrors(
  const MatType& labels,
  const std::vector<std::string>& activationTypes,
  const std::vector<MatType>& weights,
  const std::vector<MatType>& outputs,
  const std::vector<MatType>& activations,
  std::vector<MatType>& errors) const {
  //////////////////////////////////////////////////////
  const int numLayers = mNumLayers;
  errors.resize(numLayers + 1);
  // When Using softmax in last layer:
  cv::subtract(activations.back(), labels, errors.back());
  // TODO(Ricardo): Change this line above to any activation
  float avg_loss = 0;
  avg_loss = static_cast<float>(cv::mean(errors.back())[0]);
  for (int L = numLayers - 1; L >= 0; --L) {
    MatType aux;
    cv::gemm(errors[L + 1], weights[L], 1,
             cv::noArray(), 0, aux, cv::GEMM_2_T);
    MatType derivative;
    applyDerivative(activationTypes[L], outputs[L], derivative);
    cv::multiply(aux, derivative, errors[L]);
  }
  return avg_loss;
}

template <class MatType>
void MultilayerPerceptron::gradientUpdate(
  const float learningRate,
  const std::vector<MatType>& weights,
  const std::vector<MatType>& activations,
  const std::vector<MatType>& errors) const {
  const int len = static_cast<int>(weights.size());
  std::vector<MatType> newWeights(weights.size());
  for (int i = 0; i < len; ++i) {
    MatType G_l;
    cv::gemm(activations[i], errors[i], 1, cv::noArray(), 1, G_l);
    cv::addWeighted(weights[i], 1, G_l, learningRate, 0, newWeights);
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
    cv::UMat out = cv::max(cv::UMat::zeros(inp.size(), CV_32F), inp);
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
    cv::exp(inp, out);
    cv::add(out, 1, out);
    cv::divide(1, out, out);
    out.copyTo(_out);
  } else {
    cv::Mat inp = _inp.getMat();
    cv::Mat out;
    cv::exp(inp, out);
    out = 1 + out;
    out = 1 / out;
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
    for (int r = 0; r < out.rows; ++r) {
      cv::normalize(out.row(r), out.row(r), 1, 0, cv::NORM_L1);
    }
    out.copyTo(_out);
  } else {
    cv::Mat inp = _inp.getMat();
    cv::Mat out;
    cv::exp(inp, out);
    for (int r = 0; r < out.rows; ++r) {
      cv::normalize(out.row(r), out.row(r), 1, 0, cv::NORM_L1);
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
    cv::UMat aux(out.size(), CV_32F, EULER);
    cv::log(aux, aux);
    cv::divide(out, aux, out);
    out.copyTo(_out);
  } else {
    cv::Mat out;
    cv::Mat aux(out.size(), CV_32F, EULER);
    // for finding the natural log
    cv::exp(_inp, out);
    cv::add(1, out, out);
    cv::log(out, out);
    cv::log(aux, aux);
    cv::divide(out, aux, out);
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
    cv::multiply(_out, aux, out);
  } else {
    cv::Mat out;
    logistic(_inp, out);
    cv::Mat aux;
    cv::subtract(1, out, aux);
    cv::multiply(_out, aux, out);
  }
}

void MultilayerPerceptron::dSoftmax(
  cv::InputArray _inp,
  cv::OutputArray _out) {
  // TODO(Ricardo): implement this
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
    cv::Mat layerResponse = outputs[l] * weights[l];
    outputs[l] = layerResponse;
    applyActivation(activationTypes[l], layerResponse, layerResponse);
    if (dropout[l] > 0.05f && dropout[l] < 0.8f) {
      cv::multiply(mDropouts[l], layerResponse, layerResponse);
    }
    activations[l + 1] = layerResponse;
  }
}
}  // namespace ssig
