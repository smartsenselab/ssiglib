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

#ifndef _SSIG_CORE_CUBE_HPP_
#define _SSIG_CORE_CUBE_HPP_

#include "core_defs.hpp"
#include <algorithm>

namespace ssig {
class Cube {
  public:
    int x0, y0, t0;
    int w, h, l;  // width, height, length

    CORE_EXPORT Cube(void);
    CORE_EXPORT Cube(int x, int y, int t, int width, int height, int length);
    CORE_EXPORT ~Cube(void);
    CORE_EXPORT bool isCubeValid();
    CORE_EXPORT void setCube(int x0, int y0, int t0, int w, int h, int l);
    CORE_EXPORT Cube(const Cube& rhs);
    CORE_EXPORT Cube& operator = (const Cube& rhs);

  private:
    // private members
  };

  static inline bool operator == (const Cube& a, const Cube& b) {
    return a.x0 == b.x0 && a.y0 == b.y0 && a.t0 == b.t0 && a.w == b.w &&
      a.h == b.h && a.l == b.l;
  }

  static inline bool operator != (const Cube& a, const Cube& b) {
    return a.x0 != b.x0 || a.y0 != b.y0 || a.t0 != b.t0 || a.w != b.w ||
      a.h != b.h || a.l != b.l;
  }

  static inline Cube& operator&= (Cube& a, const Cube& b) {
    int x1 = std::max(a.x0, b.x0);
    int y1 = std::max(a.y0, b.y0);
    int t1 = std::max(a.t0, b.t0);
    a.w = std::min(a.x0 + a.w, b.x0 + b.w) - x1;
    a.h = std::min(a.y0 + a.h, b.y0 + b.h) - y1;
    a.l = std::min(a.t0 + a.l, b.t0 + b.l) - t1;
    a.x0 = x1;
    a.y0 = y1;
    a.t0 = t1;
    if (a.w <= 0 || a.h <= 0 || a.l <= 0)
      a = Cube();
    return a;
  }

  static inline Cube operator & (const Cube& a, const Cube& b) {
    ssig::Cube c = a;
    return c &= b;
  }

}  // namespace ssig
#endif  // !_SSF_CORE_CUBE_HPP_
