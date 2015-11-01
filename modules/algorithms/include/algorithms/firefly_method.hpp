/*L*************************************************************************************************
*
*  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
*
*  By downloading, copying, installing or using the software you agree to this license. If you do
*  not agree to this license, do not download, install, copy or use the software.
*
*                            Software License Agreement (BSD License)
*                               For Smart Surveillance Framework
*                                 http://ssig.dcc.ufmg.br/ssf/
*
*  Copyright (c) 2013, Smart Surveillance Interest Group, all rights reserved.
*
*  Redistribution and use in source and binary forms, with or without modification, are permitted
*  provided that the following conditions are met:
*
*    1. Redistributions of source code must retain the above copyright notice, this list of
*       conditions and the following disclaimer.
*
*    2. Redistributions in binary form must reproduce the above copyright notice, this list of
*       conditions and the following disclaimer in the documentation and/or other materials
*       provided with the distribution.
*
*    3. Neither the name of the copyright holder nor the names of its contributors may be used to
*       endorse or promote products derived from this software without specific prior written
*       permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
*  IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
*  AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
*  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
*  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
*  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
*  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
*  POSSIBILITY OF SUCH DAMAGE.
*************************************************************************************************L*/

#ifndef _SSF_ALGORITHMS_FIREFLY_METHOD_HPP_
#define _SSF_ALGORITHMS_FIREFLY_METHOD_HPP_

#include "core/util.hpp"
#include "core/algorithm.hpp"
#include <opencv2/core.hpp>

namespace ssf{

	template<class UtilityFunction, class DistanceFunction>
	class Firefly : public ssf::Algorithm{
		cv::Mat_<float> randomVector();
	public:
		Firefly() = default;

		void setup(cv::Mat_<float>& input);

		bool iterate();

		cv::Mat_<float> learn
			(cv::Mat_<float>& input);

		cv::Mat_<float> getResults();

		cv::Mat_<float> getState();

		virtual void save(const std::string& filename,
			const std::string& nodename) const override;
		virtual void load(const std::string& filename,
			const std::string& nodename) override;

	private:

		cv::Mat_<float> mPopulation;
		cv::Mat_<float> mUtilities;
		float mAbsorption = 0.01f;
		int mIterations = 0;
		int mMaxIterations = 10;
		float mAnnealling = 0.97f;
		float mStep = 0.01f;
		cv::RNG mRng;
	public:
		float getAbsorption() const{
			return mAbsorption;
		}

		void setAbsorption(float absorption){
			mAbsorption = absorption;
		}

		int getMaxIterations() const{
			return mMaxIterations;
		}

		void setMaxIterations(int maxIterations){
			mMaxIterations = maxIterations;
		}

		float getAnnealling() const{
			return mAnnealling;
		}

		void setAnnealling(float annealling){
			mAnnealling = annealling;
		}

		float getStep() const{
			return mStep;
		}

		void setStep(float step){
			mStep = step;
		}

	};

	template<class UtilityFunction, class DistanceFunction>
	cv::Mat_<float> Firefly<UtilityFunction, DistanceFunction>::
		randomVector(){
		const int d = mPopulation.cols;
		cv::Mat_<float> vec(1, d);
		cv::randu(vec, cv::Scalar::all(-0.5), cv::Scalar::all(0.5));
		return vec;
	}

	template<class UtilityFunction, class DistanceFunction>
	void Firefly<UtilityFunction, DistanceFunction>::setup(cv::Mat_<float>& input){
		UtilityFunction evaluateUtility;

		mIterations = 0;
		mPopulation = input;
		mUtilities = cv::Mat::zeros(mPopulation.rows, 1, CV_32F);

		for (int i = 0; i < mPopulation.rows; ++i){
			mUtilities[0][i] = evaluateUtility(mPopulation.row(i));
		}

		mRng = cv::theRNG();

		cv::Mat_<int> order;
		cv::sortIdx(mUtilities, order, cv::SORT_EVERY_COLUMN + cv::SORT_ASCENDING);
		cv::Mat_<float> npop;
		cv::Mat_<float> nuti;
		ssf::Util::reorder(mPopulation, order, npop);
		ssf::Util::reorder(mUtilities, order, nuti);
		mPopulation = npop;
		mUtilities = nuti;
	}

	template<class UtilityFunction, class DistanceFunction>
	bool Firefly<UtilityFunction, DistanceFunction>::iterate(){
		DistanceFunction evaluateDistance;
		for (int i = 0; i < mPopulation.rows; ++i){
			for (int j = 0; j < mPopulation.rows; ++j){
				if (mUtilities[0][j] > mUtilities[0][i]){
					auto xj = mPopulation.row(j);
					auto xi = mPopulation.row(i);
					auto dist = evaluateDistance(xi, xj);
					auto expX = (mAbsorption * dist * dist);
					auto attractiveness = mUtilities[0][j] / (1 + expX + expX * expX / 2);
					mPopulation.row(i) = xi * (1 - attractiveness) +
						attractiveness * (xj)+mStep * randomVector();
				}
			}
		}
		UtilityFunction evaluateUtility;

		for (int i = 0; i < mPopulation.rows; ++i){
			mUtilities[0][i] = evaluateUtility(mPopulation.row(i));
		}

		mStep = mStep * mAnnealling;

		cv::Mat_<int> order;
		cv::sortIdx(mUtilities, order, cv::SORT_EVERY_COLUMN + cv::SORT_ASCENDING);
		cv::Mat_<float> npop;
		cv::Mat_<float> nuti;
		ssf::Util::reorder(mPopulation, order, npop);
		ssf::Util::reorder(mUtilities, order, nuti);
		mPopulation = npop;
		mUtilities = nuti;

		if (++mIterations > mMaxIterations) return true;
		return false;
	}

	template<class UtilityFunction, class DistanceFunction>
	cv::Mat_<float> Firefly<UtilityFunction, DistanceFunction>::learn(cv::Mat_<float>& input){
		setup(input);
		while (!iterate()){}
		return getResults();
	}

	template<class UtilityFunction, class DistanceFunction>
	cv::Mat_<float>
		Firefly<UtilityFunction, DistanceFunction>::getResults(){
		return mUtilities;
	}

	template<class UtilityFunction, class DistanceFunction>
	cv::Mat_<float> Firefly<UtilityFunction, DistanceFunction>::getState(){
		return mPopulation;
	}

	template<class UtilityFunction, class DistanceFunction>
	void Firefly<UtilityFunction, DistanceFunction>::save(const std::string& filename, const std::string& nodename) const{ }

	template<class UtilityFunction, class DistanceFunction>
	void Firefly<UtilityFunction, DistanceFunction>::load(const std::string& filename, const std::string& nodename){ }
}

#endif // !_SSF_ALGORITHMS_FIREFLY_METHOD_HPP_

