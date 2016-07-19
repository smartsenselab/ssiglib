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


#ifndef _SSIG_CORE_UTIL_HPP_
#define _SSIG_CORE_UTIL_HPP_
// c++
#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>
#include <string>
#include <unordered_map>
#include <vector>
// opencv
#include <opencv2/core.hpp>
// ssiglib
#include "core_defs.hpp"
// flann
#include <flann/flann.hpp>

namespace cv {
class FileStorage;
}

namespace ssig {

class Util {
 public:
  CORE_EXPORT static cv::Mat convertToImg(const cv::Mat& m);

  CORE_EXPORT static std::string ltrim(std::string str);

  CORE_EXPORT static std::string rtrim(std::string str);

  CORE_EXPORT static std::string trim(std::string str);

  CORE_EXPORT static void reorder(const cv::Mat& collection,
    cv::Mat_<int>& ordering, cv::Mat& out);

  template <class T>
  static flann::Matrix<T> convert(cv::Mat& m) {
      flann::Matrix<T> fMat(
        static_cast<T*>(m.ptr<T>(0)),
        m.rows,
        m.cols);
      return fMat;
    }

  template <class T>
  static flann::Matrix<T> convert(cv::Mat_<T>& m) {
    flann::Matrix<T> fMat(
      (T*)(m.ptr(0)),
      m.rows,
      m.cols);
    return fMat;
  }

  template <class T>
  static void reorder(const cv::Mat_<T>& collection, cv::Mat_<int>& ordering,
    cv::Mat_<T>& out) {
    out = cv::Mat_<T>::zeros(collection.rows, collection.cols);
    for (int i = 0; i < ordering.rows; ++i) {
      collection.row(ordering[i][0]).copyTo(out.row(i));
    }
  }

  template <class C>
  static void reorder(const C& collection, const std::vector<int>& ordering,
    C& out) {
    out = collection;
    auto o = ordering;
    for (int i = 0; i < static_cast<int>(ordering.size()); ++i) {
      out[i] = collection[o[i]];
    }
  }

  /** The order of the sorted elements is stored in ordering.
  * This employs an Ascending Order
  **/
  template <class C>
  static C sort(const C& collection, const size_t len,
    std::vector<int>& ordering) {
    for (int i = 0; i < static_cast<int>(len); ++i) {
      ordering.push_back(i);
    }
    std::sort(ordering.begin(), ordering.end(),
              [&collection](const int& i, const int& j) -> bool {
                bool ans = collection[i] < collection[j];
                return ans;
              });
    C out;
    reorder<C>(collection, ordering, out);
    return out;
  }

  template <class K, class V>
  static void write(const std::unordered_map<K, V>& map, cv::FileStorage& fs) {
    fs << "keys"
        << "[";
    for (auto& p : map) {
      fs << p.first;
    }
    fs << "]";

    fs << "values"
        << "[";
    for (auto& p : map) {
      fs << p.second;
    }
    fs << "]";
  }

  template <class K, class V>
  static void read(std::unordered_map<K, V>& map, cv::FileNode& fn) {
    std::vector<K> keys;
    std::vector<V> values;

    fn["keys"] >> keys;

    fn["values"] >> values;

    for (int i = 0; i < static_cast<int>(keys.size()); ++i) {
      map[keys[i]] = values[i];
    }
  }
};

}  // namespace ssig

#endif  // !_SSIG_CORE_UTIL_HPP_PP_


