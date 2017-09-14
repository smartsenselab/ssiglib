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

#include "ssiglib/core/cube.hpp"

namespace ssig {
  Cube::Cube() {
    // Constructor
    this->x0 = -1;
    this->y0 = -1;
    this->t0 = -1;
    this->w = -1;
    this->h = -1;
    this->l = -1;
  }

  Cube::Cube(int x, int y, int t, int width, int height, int length) {
    this->x0 = x;
    this->y0 = y;
    this->t0 = t;
    this->w = width;
    this->h = height;
    this->l = length;
  }

  Cube::~Cube() {
    // Destructor
  }

  Cube::Cube(const Cube& rhs) {
    // Constructor Copy
    this->x0 = rhs.x0;
    this->y0 = rhs.y0;
    this->t0 = rhs.t0;
    this->w = rhs.w;
    this->h = rhs.h;
    this->l = rhs.l;
  }

  // return true if this cube has been set
  bool Cube::isCubeValid() {
    if (this->x0 != -1 && this->y0 != -1 && this->t0 != -1 && this->w > 0 && this->h > 0 && this->l > 0)
      return true;

    return false;
  }

  void Cube::setCube(int x0, int y0, int t0, int w, int h, int l) {
    this->x0 = x0;
    this->y0 = y0;
    this->t0 = t0;
    this->w = w;
    this->h = h;
    this->l = l;
  }

  Cube& Cube::operator = (const Cube& rhs) {
    if (this != &rhs) {
      this->x0 = rhs.x0;
      this->y0 = rhs.y0;
      this->t0 = rhs.t0;
      this->w = rhs.w;
      this->h = rhs.h;
      this->l = rhs.l;
    }
    return *this;
  }

}  // namespace ssig
