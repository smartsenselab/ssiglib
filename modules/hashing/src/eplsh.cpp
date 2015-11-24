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

#include "hashing/eplsh.hpp"

#include <vector>
#include <utility>
#include <algorithm>
#include <unordered_set>

namespace ssig {

class PLSB : public PLS {
 public:
  cv::Mat_<float>& getBStar() {
    return mBstar;
  }
};

EPLSH::EPLSH(const cv::Mat_<float> samples, const cv::Mat_<int> labels,
             const int models, const int factors, const int ndim)
    : mHashModels(models), mFactors(factors) {

  std::default_random_engine gen;

  std::unordered_set<int> ulab;
  for (const int label : labels)
    ulab.insert(label);
  for (const int label : ulab)
    mSubjects.push_back(label);

  std::uniform_int_distribution<int> dist(0, 1);

  for (size_t m = 0; m < mHashModels.size(); ++m) {
    cv::Mat_<float> responses(samples.rows, 1);
    responses = -1.0f;

    for (int l = 0; l < static_cast<int> (mSubjects.size()); ++l) {
      if (dist(gen) == 0) {
        for (int row = 0; row < samples.rows; ++row)
          if (labels.at<int>(row, 0) == mSubjects[l]) {
            mHashModels[m].mSubjects.push_back(l);
            responses(row) = 1.0f;
          }
      }
    }

    PLSB pls;
    cv::Mat_<float> s = samples.clone();
    cv::Mat_<float> r = responses.clone();

    pls.learn(s, r, factors);
    s.release();
    r.release();

    cv::Mat_<float> beta = pls.getBStar();
    beta = cv::abs(beta);

    std::vector<std::pair<int, float>> weights(beta.rows);
    for (int col = 0; col < beta.rows; ++col) {
      weights[col].first = col;
      weights[col].second = beta.at<float>(0, col);
    }

    std::sort(weights.begin(), weights.end(),
         [](const std::pair<int, float> &a, const std::pair<int, float> &b) {
           return a.second > b.second;
         });

    mHashModels[m].mIndexes.clear();
    for (int col = 0; col < ndim; ++col)
      mHashModels[m].mIndexes.push_back(weights[col].first);
    weights.clear();

    for (const int col : mHashModels[m].mIndexes) {
      if (s.empty())
        s = samples.col(col).clone();
      else
        cv::hconcat(s, samples.col(col), s);
    }

    mHashModels[m].mHashFunc.learn(s, responses, std::min(factors, ndim));
    s.release();
  }
}

EPLSH::CandListType& EPLSH::query(const cv::Mat_<float> sample,
                                  EPLSH::CandListType &candidates) {
  if (candidates.size() != mSubjects.size())
    candidates.resize(mSubjects.size());

  for (size_t i = 0; i < candidates.size(); ++i) {
    candidates[i].first = mSubjects[i];
    candidates[i].second = 0;
  }

  cv::Mat_<float> r, s;
  for (size_t m = 0; m < mHashModels.size(); ++m) {
    for (const int col : mHashModels[m].mIndexes)
      if (s.empty())
        s = sample.col(col).clone();
      else
        cv::hconcat(s, sample.col(col), s);

    mHashModels[m].mHashFunc.predict(s, r);
    s.release();

    float x = r.at<float>(0, 0);
    for (const int s : mHashModels[m].mSubjects)
      candidates[s].second += x;
  }

  std::sort(candidates.begin(), candidates.end(),
       [](const std::pair<int, float> &a, const std::pair<int, float> & b) {
         return a.second > b.second;
       });

  return candidates;
}

};  // namespace ssig
