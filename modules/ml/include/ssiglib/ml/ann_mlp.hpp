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

#ifndef _SSIG_ML_ANN_MLP_HPP_
#define _SSIG_ML_ANN_MLP_HPP_
// c++
#include <vector>
#include <functional>
#include <string>
// cv
#include <opencv2/core/mat.hpp>
// ssig
#include <ssiglib/core/algorithm.hpp>
#include <ssiglib/ml/classification.hpp>
#include <ssiglib/ml/multiclass.hpp>
#include <ssiglib/ml/ml_defs.hpp>

namespace ssig {
class MultilayerPerceptron : ssig::Multiclass {
 public:
  static cv::Ptr<MultilayerPerceptron> create(
    const std::vector<std::string>& activationTypes,
    const std::vector<int>& layersLength,
    const std::vector<float>& dropouts = std::vector<float>());

  virtual ~MultilayerPerceptron(void);
  MultilayerPerceptron(const MultilayerPerceptron& rhs);
  MultilayerPerceptron& operator=(const MultilayerPerceptron& rhs);

  int predict(
    const cv::Mat_<float>& inp,
    cv::Mat_<float>& resp,
    cv::Mat_<int>& labels) const override;
  void learn(
    const cv::Mat_<float>& input,
    const cv::Mat& labels) override;

  void predict(
    const int layerIdx,
    const cv::Mat_<float>& inp,
    cv::Mat_<float>& resp,
    cv::Mat_<int>& labels);

  void predict(
    const cv::Mat& inp,
    cv::Mat& resp,
    cv::Mat& labels,
    std::vector<cv::Mat>& activations,
    std::vector<cv::Mat>& outputs) const;

  cv::Mat getLabels() const override;
  cv::Mat getWeights(const int layerIndex);


  std::unordered_map<int, int> getLabelsOrdering() const override;


  float getLearningRate() const;
  void setLearningRate(const float learningRate);
  int getNumLayers() const;
  void setNumLayers(const int numLayers);

  std::vector<cv::Mat> getWeightMatrices() const;
  void setWeights(const std::vector<cv::Mat>& weights);
  std::vector<cv::Mat> getDropouts() const;
  void setDropouts(const std::vector<cv::Mat>& dropouts);
  std::vector<cv::Mat> getLayerActivations() const;
  void setLayerActivations(const std::vector<cv::Mat>& layerActivations);
  std::vector<cv::Mat> getLayerOut() const;
  void setLayerOut(const std::vector<cv::Mat>& layerOut);
  std::vector<int> getNumNodesConfiguration() const;
  void setLayersLength(const std::vector<int>& numNodesConfiguration);
  std::vector<std::string> getActivationsTypes() const;
  void setActivationsTypes(const std::vector<std::string>& activationsTypes);
  std::vector<float> getDropoutWeights() const;
  void setDropoutWeights(const std::vector<float>& dropoutWeights);

  bool empty() const override;
  bool isTrained() const override;
  Classifier* clone() const override;

 protected:
  MultilayerPerceptron(void);
  template <class MatType>
  void doForwardPass(
    const MatType& input,
    const std::vector<MatType>& weights,
    const std::vector<std::string>& activationTypes,
    const std::vector<float>& dropout,
    std::vector<MatType>& outputs,
    std::vector<MatType>& activations) const;

  // backpropagation
  void learnWeights(
    const cv::Mat& inputs,
    const cv::Mat& labels,
    const std::vector<cv::Mat>& weights,
    const std::vector<std::string>& activationTypes,
    const std::vector<float>& dropout) const;

  template <class MatType>
  float computeErrors(
    const MatType& labels,
    const std::vector<std::string>& activationTypes,
    const std::vector<MatType>& weights,
    const std::vector<MatType>& outputs,
    const std::vector<MatType>& activations,
    std::vector<MatType>& errors) const;

  template <class MatType>
  void gradientUpdate(
    const float learningRate,
    const std::vector<MatType>& weights,
    const std::vector<MatType>& activations,
    const std::vector<MatType>& errors) const;

  // Activation Functions:
  static void applyActivation(
    const std::string& type,
    cv::InputArray& _inp,
    cv::OutputArray& _out);
  static void applyDerivative(
    const std::string& type,
    cv::InputArray& _inp,
    cv::OutputArray& _out);

  static void relu(
    const cv::InputArray& _inp,
    cv::OutputArray& _out);
  static void logistic(
    const cv::InputArray& _inp,
    cv::OutputArray& _out);
  static void softmax(
    const cv::InputArray& _inp,
    cv::OutputArray& _out);
  static void softplus(
    const cv::InputArray& _inp,
    cv::OutputArray& _out);
  // derivative of activation
  static void dRelu(
    const cv::InputArray& _inp,
    cv::OutputArray& _out);
  static void dSoftplus(
    const cv::InputArray& _inp,
    cv::OutputArray& _out);
  static void dLogistic(
    const cv::InputArray& _inp,
    cv::OutputArray& _out);
  static void dSoftmax(
    const cv::InputArray& _inp,
    cv::OutputArray& _out);

  void read(const cv::FileNode& fn) override;
  void write(cv::FileStorage& fs) const override;

 private:
  // private members
  bool mIsTrained = false;;
  float mLearningRate = 0.5f;
  int mNumLayers = 2;

  // the Weights matrix for each layer
  std::vector<cv::Mat> mWeights;
  std::vector<cv::Mat> mDropouts;
  std::vector<float> mDropoutWeights;

  // the layer output, at index 0 is the input, at index 'n' is the final output
  std::vector<cv::Mat> mLayerActivations;
  std::vector<std::string> mActivationsTypes;
  std::vector<cv::Mat> mLayerOut;
  // this vector holds the number of nodes in each layer;
  std::vector<int> mNumNodesConfiguration;
};
}  // namespace ssig
#endif  // !_SSIG_ML_ANN_MLP_HPP_
