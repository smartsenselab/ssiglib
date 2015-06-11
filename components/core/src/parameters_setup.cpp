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

#include "core/parameters_setup.hpp"

#include <boost/lexical_cast.hpp>
#include <opencv2/core/core.hpp>

#include "core/param_exception.hpp"

namespace ssf{

	ParametersSetup::ParametersSetup(const std::string& ID)
		: mID(ID){
		//Constructor
	}

	ParametersSetup::ParametersSetup(const std::string& paramFile, const std::string& nodeID)
		: mID(nodeID){
		this->_readParamsFromFile(paramFile, nodeID);
	}

	ParametersSetup::ParametersSetup(const FileHandle& paramFile, const std::string& nodeID)
		: mID(nodeID){
		this->_readParamsFromFile(paramFile.absolutePath(), nodeID);
	}

	ParametersSetup::~ParametersSetup(){
		//Destructor
	}

	ParametersSetup::ParametersSetup(const ParametersSetup& rhs){
		this->mParametersValues = rhs.mParametersValues;
		this->mID = rhs.mID;
	}

	ParametersSetup& ParametersSetup::operator=(const ParametersSetup& rhs){
		if (this != &rhs){
			this->mParametersValues = rhs.mParametersValues;
			this->mID = rhs.mID;
		}
		return *this;
	}

	void ParametersSetup::addParameter(const std::string& paramName, const int& value){
		this->_addParameter(paramName, value);
	}

	void ParametersSetup::addParameter(const std::string& paramName, const double& value){
		this->_addParameter(paramName, value);
	}

	void ParametersSetup::addParameter(const std::string& paramName, const bool& value){
		this->_addParameter(paramName, value);
	}

	void ParametersSetup::addParameter(const std::string& paramName, const char* value){
		this->_addParameter(paramName, value);
	}

	void ParametersSetup::addParameter(const std::string& paramName, const std::string& value){
		this->_addParameter(paramName, value);
	}

	void ParametersSetup::addParameter(const std::string& paramName, const FileHandle& value){
		this->_addParameter(paramName, value);
	}

	void ParametersSetup::addParameter(const std::string& paramName, const DirectoryHandle& value){
		this->_addParameter(paramName, value);
	}

	void ParametersSetup::addParameter(const std::string& paramName, const std::vector<int>& value){
		this->_addParameter(paramName, value);
	}

	void ParametersSetup::addParameter(const std::string& paramName, const std::vector<double>& value){
		this->_addParameter(paramName, value);
	}

	void ParametersSetup::addParameter(const std::string& paramName, const std::vector<std::string>& value){
		this->_addParameter(paramName, value);
	}

	void ParametersSetup::setValue(const std::string& paramName, const int& value){
		std::string convertString = std::to_string(value);
		this->_setParameter(paramName, std::vector < std::string > {convertString});
	}

	void ParametersSetup::setValue(const std::string& paramName, const double& value){
		std::string convertString = std::to_string(value);
		this->_setParameter(paramName, std::vector < std::string > {convertString});
	}

	void ParametersSetup::setValue(const std::string& paramName, const bool& value){
		std::string convertString = value ? "true" : "false";
		this->_setParameter(paramName, std::vector < std::string > {convertString});
	}

	void ParametersSetup::setValue(const std::string& paramName, const char* value){
		std::string convertString(value);
		this->_setParameter(paramName, std::vector < std::string > {convertString});
	}

	void ParametersSetup::setValue(const std::string& paramName, const std::string& value){
		this->_setParameter(paramName, std::vector < std::string > {value});
	}

	void ParametersSetup::setValue(const std::string& paramName, const FileHandle& value){
		std::string convertString = value.absolutePath();
		this->_setParameter(paramName, std::vector < std::string > {convertString});
	}

	void ParametersSetup::setValue(const std::string& paramName, const DirectoryHandle& value){
		std::string convertString = value.absolutePath();
		this->_setParameter(paramName, std::vector < std::string > {convertString});
	}

	void ParametersSetup::setValue(const std::string& paramName, const std::vector<int>& value){
		std::vector<std::string> convertValues;
		for (auto singleValue : value)
			convertValues.push_back(std::to_string(singleValue));
		this->_setParameter(paramName, convertValues);
	}

	void ParametersSetup::setValue(const std::string& paramName, const std::vector<double>& value){
		std::vector<std::string> convertValues;
		for (auto singleValue : value)
			convertValues.push_back(std::to_string(singleValue));
		this->_setParameter(paramName, convertValues);
	}

	void ParametersSetup::setValue(const std::string& paramName, const std::vector<std::string>& value){
		this->_setParameter(paramName, value);
	}

	int ParametersSetup::toInt(const std::string& paramName){
		int convert_value;
		try{
			double temp_value;
			temp_value = boost::lexical_cast<double>(this->mParametersValues[paramName][0]);
			convert_value = boost::numeric_cast<int>(temp_value);
		}
		catch (std::exception e){
			if (this->mParametersValues[paramName][0] == "true")
				return 1;

			if (this->mParametersValues[paramName][0] == "false")
				return 0;
			throw ParamException(paramName, "Is not possible convert this parameter to int.");
		}
		return convert_value;
	}

	double ParametersSetup::toDouble(const std::string& paramName){
		double convert_value;
		try{
			convert_value = boost::lexical_cast<double>(this->mParametersValues[paramName][0]);
		}
		catch (std::exception e){
			if (this->mParametersValues[paramName][0] == "true")
				return 1;

			if (this->mParametersValues[paramName][0] == "false")
				return 0;
			throw ParamException(paramName, "Is not possible convert this parameter to double.");
		}
		return convert_value;
	}

	bool ParametersSetup::toBool(const std::string& paramName){
		int tempValue;
		try{
			tempValue = this->toInt(paramName);
		}
		catch (std::exception e){
			if (this->mParametersValues[paramName][0] == "false")
				return false;
		}
		return (tempValue != 0);
	}

	std::string ParametersSetup::toString(const std::string& paramName){
		return this->mParametersValues[paramName][0];
	}

	FileHandle ParametersSetup::toFileHandle(const std::string& paramName){
		return FileHandle(this->mParametersValues[paramName][0]);
	}

	DirectoryHandle ParametersSetup::toDirectoryHandle(const std::string& paramName){
		return DirectoryHandle(this->mParametersValues[paramName][0]);
	}

	std::vector<int> ParametersSetup::toIntVector(const std::string& paramName){
		std::vector<int> retVector;
		int convert_value;
		for (auto strValue : this->mParametersValues[paramName]){
			try{
				double temp_value;
				temp_value = boost::lexical_cast<double>(strValue);
				convert_value = boost::numeric_cast<int>(temp_value);
			}
			catch (std::exception e){
				if (strValue == "true")
					convert_value = 1;
				else if (strValue == "false")
					convert_value = 0;
				else
					throw ParamException(paramName, "Is not possible convert this parameter to int.");
			}
			retVector.push_back(convert_value);
		}
		return retVector;
	}

	std::vector<double> ParametersSetup::toDoubleVector(const std::string& paramName){
		std::vector<double> retVector;
		for (auto strValue : this->mParametersValues[paramName]){
			double convert_value;
			try{
				convert_value = boost::lexical_cast<double>(strValue);
			}
			catch (std::exception e){
				if (strValue == "true")
					convert_value = 1;
				else if (strValue == "false")
					convert_value = 0;
				else
					throw ParamException(paramName, "Is not possible convert this parameter to double.");
			}
			retVector.push_back(convert_value);
		}
		return retVector;
	}

	std::vector<std::string> ParametersSetup::toStringVector(const std::string& paramName){
		return this->mParametersValues[paramName];
	}

	std::string ParametersSetup::ID() const{
		return this->mID;
	}

	void ParametersSetup::setID(const std::string& setupID){
		this->mID = setupID;
	}

	void ParametersSetup::_setParameter(const std::string& paramName, const std::vector<std::string>& value){
		if (this->mParametersValues.find(paramName) == this->mParametersValues.end())
			throw ParamException(paramName, "Does not exists a parameter with it name.");
		this->mParametersValues[paramName] = value;
	}

	void ParametersSetup::_readParamsFromFile(const std::string& fileName, const std::string& nodeName){
		if (!FileHandle::exists(fileName))
			throw ParamException("Parameter File: " + fileName, "This parameter file is invalid!");

		cv::FileStorage fs;
		cv::FileNode node;
		try{
			fs = cv::FileStorage(fileName, cv::FileStorage::READ);
			if (!fs.isOpened())
				throw ParamException("Parameter File: " + fileName, "This parameter file is invalid!");
			if (fs[nodeName].size() == 0)
				throw ParamException("Parameter File: " + fileName, "This file node " + nodeName + " is invalid!");
			node = (nodeName == "") ? fs.root() : fs[nodeName];
		}
		catch (std::exception* e){
			throw ParamException("Parameter File: " + fileName, e->what());
		}
		for (auto current = node.begin(); current != node.end(); current++){
			try{
				this->_convertNodeToValue(*current);
			}
			catch (Exception* e){
				throw ParamException(fileName, e->what());
			}
		}
		this->setID(nodeName);
		fs.release();
	}

	void ParametersSetup::_convertNodeToValue(const cv::FileNode& fileNode){

		try{
			if (!(fileNode.isInt() || fileNode.isReal() || fileNode.isString() || fileNode.isSeq()) || !fileNode.isNamed())
				throw ParamException("Parameter: " + fileNode.name(), "Parameters file with incorrect syntax!");

			std::string paramName = fileNode.name();

			int intSingleValue;
			double doubleSingleValue;
			std::string singleValue;
			std::vector<std::string> values;

			if (fileNode.isInt()){
				fileNode >> intSingleValue;
				this->addParameter(paramName, intSingleValue);
			}
			else if (fileNode.isReal()){
				fileNode >> doubleSingleValue;
				this->addParameter(paramName, doubleSingleValue);
			}
			else if (fileNode.isString()){
				fileNode >> singleValue;
				this->addParameter(paramName, singleValue);
			}
			else if (fileNode.isSeq()){
				values.clear();
				for (auto current = fileNode.begin(); current != fileNode.end(); current++){
					if ((*current).isInt()){
						(*current) >> intSingleValue;
						values.push_back(std::to_string(intSingleValue));
					}
					else if ((*current).isReal()){
						(*current) >> doubleSingleValue;
						values.push_back(std::to_string(doubleSingleValue));
					}
					else if ((*current).isString()){
						(*current) >> singleValue;
						values.push_back(singleValue);
					}
					else{
						throw ParamException("Parameter: " + fileNode.name(), "Parameters file with incorrect syntax!");
					}
				}
				if (values.empty())
					throw ParamException("Parameter: " + fileNode.name(), "Parameters file with incorrect syntax!");
				this->addParameter(paramName, values);
			}
			else{
				throw ParamException("Parameter: " + fileNode.name(), "Parameters file with incorrect syntax!");
			}

		}
		catch (Exception* e){
			throw ParamException("Parameter: " + fileNode.name(), e->what());
		}

	}

}



