#include "core/parameters_setup.hpp"

#include <opencv/cv.h>

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
		this->_readParamsFromFile(paramFile.getAbsoluteFileName(), nodeID);
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

	void ParametersSetup::addParameter(const std::string& name, const int& value){
		this->_addParameter(name, value);
	}

	void ParametersSetup::addParameter(const std::string& name, const double& value){
		this->_addParameter(name, value);
	}

	void ParametersSetup::addParameter(const std::string& name, const bool& value){
		this->_addParameter(name, value);
	}

	void ParametersSetup::addParameter(const std::string& name, const char* value){
		this->_addParameter(name, value);
	}

	void ParametersSetup::addParameter(const std::string& name, const std::string& value){
		this->_addParameter(name, value);
	}

	void ParametersSetup::addParameter(const std::string& name, const FileHandle& value){
		this->_addParameter(name, value);
	}

	void ParametersSetup::addParameter(const std::string& name, const DirectoryHandle& value){
		this->_addParameter(name, value);
	}

	void ParametersSetup::addParameter(const std::string& name, const std::vector<int>& value){
		this->_addParameter(name, value);
	}

	void ParametersSetup::addParameter(const std::string& name, const std::vector<double>& value){
		this->_addParameter(name, value);
	}

	void ParametersSetup::addParameter(const std::string& name, const std::vector<std::string>& value){
		this->_addParameter(name, value);
	}

	void ParametersSetup::setValue(const std::string& name, const int& value){
		std::string convertString = std::to_string(value);
		this->_setParameter(name, std::vector < std::string > {convertString});
	}

	void ParametersSetup::setValue(const std::string& name, const double& value){
		std::string convertString = std::to_string(value);
		this->_setParameter(name, std::vector < std::string > {convertString});
	}

	void ParametersSetup::setValue(const std::string& name, const bool& value){
		std::string convertString = value ? "true" : "false";
		this->_setParameter(name, std::vector < std::string > {convertString});
	}

	void ParametersSetup::setValue(const std::string& name, const char* value){
		std::string convertString(value);
		this->_setParameter(name, std::vector < std::string > {convertString});
	}

	void ParametersSetup::setValue(const std::string& name, const std::string& value){
		this->_setParameter(name, std::vector < std::string > {value});
	}

	void ParametersSetup::setValue(const std::string& name, const FileHandle& value){
		std::string convertString = value.getAbsoluteFileName();
		this->_setParameter(name, std::vector < std::string > {convertString});
	}

	void ParametersSetup::setValue(const std::string& name, const DirectoryHandle& value){
		std::string convertString = value.getAbsolutePath();
		this->_setParameter(name, std::vector < std::string > {convertString});
	}

	void ParametersSetup::setValue(const std::string& name, const std::vector<int>& value){
		std::vector<std::string> convertValues;
		for (auto singleValue : value)
			convertValues.push_back(std::to_string(singleValue));
		this->_setParameter(name, convertValues);
	}

	void ParametersSetup::setValue(const std::string& name, const std::vector<double>& value){
		std::vector<std::string> convertValues;
		for (auto singleValue : value)
			convertValues.push_back(std::to_string(singleValue));
		this->_setParameter(name, convertValues);
	}

	void ParametersSetup::setValue(const std::string& name, const std::vector<std::string>& value){
		this->_setParameter(name, value);
	}

	std::string ParametersSetup::getID() const{
		return this->mID;
	}

	void ParametersSetup::setID(const std::string& setupID){
		this->mID = setupID;
	}

	const std::map<std::string, std::vector<std::string>>& ParametersSetup::getParametersValues() const{
		return this->mParametersValues;
	}

	void ParametersSetup::_setParameter(const std::string& name, const std::vector<std::string>& value){
		if (this->mParametersValues.find(name) == this->mParametersValues.end())
			throw ParamException(name, "Does not exists a parameter with it name.");
		this->mParametersValues[name] = value;
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
				this->_converNodeToValue(*current);
			}
			catch (Exception* e){
				throw ParamException(fileName, e->what());
			}
		}
		this->setID(nodeName);
		fs.release();
	}

	void ParametersSetup::_converNodeToValue(const cv::FileNode& fileNode){

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

