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
    mParams.C = 0.1;
    mParams.kernel_type = LINEAR;
    mParams.svm_type = C_SVC;
    mParams.cache_size = 10;
    mParams.eps = 0.001;
    mParams.nr_weight = 0;
    mParams.gamma = 0;
    mParams.coef0 = 0;
    mParams.degree = 0;
    mParams.shrinking = 0;
    mParams.probability = 0;
  }

  SVMClassifier::~SVMClassifier() {
    // Destructor
    svm_free_and_destroy_model(&mModel);
  }

  std::unordered_map<int, int> SVMClassifier::getLabelsOrdering() const {
    std::unordered_map<int, int> ordering = { { 1, 0 }, { -1, 1 } };
    return ordering;
  }

  void SVMClassifier::setClassWeights(const int classLabel, const float weight) { }

  bool SVMClassifier::empty() const {
    return mModel == nullptr ? true : false;
  }

  bool SVMClassifier::isTrained() const {
    return false;
  }

  bool SVMClassifier::isClassifier() const {
    return true;
  }

  Classifier* SVMClassifier::clone() const {
    return nullptr;
  }

  int SVMClassifier::getKernelType() const {
    return mParams.kernel_type;
  }

  void SVMClassifier::setKernelType(KernelType kernelType) {
    mParams.kernel_type = kernelType;
  }

  int SVMClassifier::getModelType() const {
    return mParams.svm_type;
  }

  void SVMClassifier::setModelType(ModelType modelType) {
    mParams.svm_type = modelType;
  }

  double SVMClassifier::getC() const {
    return mParams.C;
  }

  void SVMClassifier::setC(double c) {
    mParams.C = c;
  }

  double SVMClassifier::getGamma() const {
    return mParams.gamma;
  }

  void SVMClassifier::setGamma(double gamma) {
    mParams.gamma = gamma;
  }

  double SVMClassifier::getP() const {
    return mParams.p;
  }

  void SVMClassifier::setP(double p) {
    mParams.p = p;
  }

  double SVMClassifier::getNu() const {
    return mParams.nu;
  }

  void SVMClassifier::setNu(double nu) {
    mParams.nu = nu;
  }

  double SVMClassifier::getCoef() const {
    return mParams.coef0;
  }

  void SVMClassifier::setCoef(double coef) {
    mParams.coef0 = coef;
  }

  int SVMClassifier::getDegree() const {
    return mParams.degree;
  }

  void SVMClassifier::setDegree(int degree) {
    mParams.degree = degree;
  }

  void SVMClassifier::setProbabilisticModel(bool b) {
    mParams.probability = (b) ? 1 : 0;
  }

  bool SVMClassifier::getProbabilisticModel() const {
    return (mParams.probability)?true:false;
  }

  svm_problem* SVMClassifier::convertToLibSVM(
    const cv::Mat_<int>& labels,
    const cv::Mat_<float>& features) const {
    const int nSamples = labels.rows;

    svm_problem* ans = new svm_problem[nSamples];
    double* y = new double[nSamples];
    ans->l = nSamples;
    ans->y = y;
    for (int i = 0; i < nSamples; ++i) {
      y[i] = labels.at<int>(i);
    }

    auto nodes = convertToLibSVM(features);
    ans->x = nodes;

    return ans;
  }

  svm_node** SVMClassifier::convertToLibSVM(const cv::Mat_<float>& features) const {
    const int nSamples = features.rows;
    const int ncols = features.cols;
    svm_node** featNode = new svm_node*[nSamples];
    for (int i = 0; i < nSamples; ++i) {
      std::vector<svm_node> row_nodes;
      for (int j = 0; j < ncols; ++j) {
        float feat = features.at<float>(i, j);
        if (cv::abs(feat) > FLT_EPSILON) {
          row_nodes.push_back(svm_node{ j, feat });
        }
      }
      row_nodes.push_back(svm_node {-1, 0.0});
      const int len = static_cast<int>(row_nodes.size());
      featNode[i] = new svm_node[len];
      for (int j = 0; j < len; ++j) {
        featNode[i][j] = row_nodes[j];
      }
    }
    return featNode;
  }

  void SVMClassifier::learn(
    const cv::Mat_<float>& input,
    const cv::Mat_<int>& labels) {

    if(mParams.eps < 0.0001)
      mParams.shrinking = 1;

    svm_problem* problem = convertToLibSVM(labels, input);

    const char* errMsg = svm_check_parameter(problem, &mParams);
    if (errMsg) {
      printf("%s", errMsg);
      exit(-1);
    }

    mModel = svm_train(problem, &mParams);
  }

  int SVMClassifier::predict(
    const cv::Mat_<float>& inp,
    cv::Mat_<float>& resp) const {
    resp = cv::Mat_<float>::zeros(inp.rows, 2);
    int label = 0;
    auto featNode = convertToLibSVM(inp);
    const int len = inp.rows;
    double dec_value = 0;
    for (int i = 0; i < len; ++i) {
      if(getProbabilisticModel()) {
        if (svm_check_probability_model(mModel)) {
          label = static_cast<int>(svm_predict_probability(mModel, featNode[i], &dec_value));
        }else {
          std::runtime_error("Model not fit for probability estimates");
        }
      } else {
        label = static_cast<int>(svm_predict_values(mModel, featNode[i], &dec_value));
      }
       resp[i][0] = static_cast<float>(dec_value);
    }
    if (getProbabilisticModel()) {
      resp.col(1) = 1 - resp.col(0);
    } else {
      resp.col(1) = -1 * resp.col(0);
    }

    delete[] featNode;

    return label;
  }

  void SVMClassifier::read(const cv::FileNode& fn) {
    std::string model;
    fn["model"] >> model;
    FILE* tmpf = tmpfile();
    auto buffer = reinterpret_cast<const uchar*>(model.c_str());
    auto size = model.size();
    auto nsymbols = fwrite(buffer, 1, size, tmpf);
    rewind(tmpf);

    mModel = svm_load_model(tmpf);
    fclose(tmpf);
  }

  void SVMClassifier::write(cv::FileStorage& fs) const {
    FILE* tmpf = tmpfile();
    if(svm_save_model(tmpf, mModel)) {
      perror("hi");
    };
    std::string model;

    // obtain file size:
    fseek(tmpf, 0, SEEK_END);
    auto lSize = static_cast<size_t>(ftell(tmpf));
    rewind(tmpf);
    
    char *buffer = new char[lSize+1];
    auto nread = fread(buffer, 1, lSize, tmpf);
    buffer[nread] = 0;
    model = buffer;

    fs<<"model" << model;

    delete[] buffer;
    fclose(tmpf);
  }

  cv::Mat_<int> SVMClassifier::getLabels() const {
    return mLabels;
  }
} // namespace ssig


