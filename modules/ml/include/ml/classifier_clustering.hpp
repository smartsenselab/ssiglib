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

#ifndef _SSF_ML_CLASSIFICATION_CLUSTERING_HPP_
#define _SSF_ML_CLASSIFICATION_CLUSTERING_HPP_

#include "ml/ml_defs.hpp"
#include "clustering_method.hpp"
#include "classification.hpp"

namespace ssf{

	class ClassifierClustering : public ClusteringMethod{
	public:
		ML_EXPORT virtual ~ClassifierClustering(void);

		ML_EXPORT virtual void setup(cv::Mat_<float>& input) override;

		ML_EXPORT void learn(cv::Mat_<float>& input) override;

		ML_EXPORT virtual void predict(cv::Mat_<float>& inp,
			cv::Mat_<float>& resp) const override = 0;

		ML_EXPORT virtual std::vector<Cluster> getClustering() const override;
		ML_EXPORT virtual bool empty() const override = 0;
		ML_EXPORT virtual bool isTrained() const override = 0;
		ML_EXPORT virtual bool isClassifier() const override = 0;

		ML_EXPORT bool iterate();

		ML_EXPORT virtual void getCentroids(cv::Mat_<float>& centroidsMatrix) const override = 0;

		ML_EXPORT virtual void load(const std::string& filename,
			const std::string& nodename) override = 0;
		ML_EXPORT virtual void save(const std::string& filename,
			const std::string& nodename)const override = 0;


		/**
		This function works as a setter for the natural samples and its split subsets distribution.

		@param[natSamples]    this argument is the matrix contaning the features of the natural world.
		@param[distribution]  this is a vector of two vector of integers, the vectors represents how the set is split in the two n1 and n2 subset for learning.
		*/
		ML_EXPORT void addNaturalWorld(cv::Mat_<float>& natSamples, std::vector<std::vector<int>>& distribution);

		ML_EXPORT int getInitialK() const;

		ML_EXPORT void setInitialK(int mInitialK1);

		ML_EXPORT int getMValue() const;

		ML_EXPORT void setMValue(int m);


		ML_EXPORT std::vector<std::vector<float>> getClustersResponses() const;

		ML_EXPORT std::vector<std::vector<int>> getDiscovery() const;

		ML_EXPORT void setDiscoveryConfiguration(const
			std::vector<std::vector<int>>& discoveryConfiguration);

		ML_EXPORT virtual void setClassifier(Classification& classifier) = 0;

	protected:
		ML_EXPORT virtual void precondition();

		virtual void initializeClusterings(const std::vector<int>& assignmentSet) = 0;
		virtual void initializeClassifiers() = 0;
		virtual void trainClassifiers(
			const cv::Mat_<float>& samples,
			const std::vector<Cluster>& clusters,
			const std::vector<int>& negativeLearningSet) = 0;
		virtual bool isFinished() = 0;

		virtual void postCondition() = 0;

		virtual void assignment(const cv::Mat_<float>& samples,
			const int clusterSize,
			const int nClusters,
			const std::vector<int>& assignmentSet,
			std::vector<std::vector<float>>& clusterResponses,
			std::vector<int>& clusterIds,
			std::vector<Cluster>& out) = 0;

		//Attributes /////////

		cv::Mat_<float> mNaturalSamples;
		int mInitialK = 0;
		int mMaximumK = 100;
		int mMValue = 5;
		int mIt = 0;

		std::vector<std::vector<int>> mDiscovery;
		std::vector<std::vector<int>> mNatural;

		std::vector<Cluster> mClustersOld, mNewClusters;
		std::vector<std::vector<float>> mClustersResponses;
		std::vector<int> mClustersIds;

	private:
		//private members
	};


}

#endif // !_SSF_ML_CLASSIFICATION_CLUSTERING_HPP_

