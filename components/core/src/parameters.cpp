//#include "core/parameters.hpp"
//
//
//#include <iostream>
//#include <opencv/cv.h>
//
//
//#include <core/param_exception.hpp>
//
//
//namespace ssf{
//
//	Parameters::Parameters(){
//		
//	}
//
//	Parameters::~Parameters(){
//
//	}
//
//	Parameters::Parameters(const FileHandle& fileHandle, const std::string& node /*= ""*/){
//		this->readParamsFromFile(fileHandle.getAbsoluteFileName(), node);
//	}
//
//	Parameters::Parameters(const std::string& fileName, const std::string& node /*= ""*/){
//		this->readParamsFromFile(fileName, node);
//	}
//
//	Parameters::Parameters(const Parameters& rhs){
//		this->mParameters = rhs.mParameters;
//	}
//
//	Parameters& Parameters::operator=(const Parameters& rhs){
//		if (this != &rhs){
//			this->mParameters = rhs.mParameters;
//		}
//		return *this;
//	}
//
//	Parameter& Parameters::operator[](const std::string& parameterName){
//		if (this->mParameters.find(parameterName) == this->mParameters.end()){
//			throw ParamException(parameterName, "Parameter with this name does not exists.");
//		}
//		return this->mParameters[parameterName];
//	}
//
//	void Parameters::addParameter(const std::string& name, const std::string& description /*= ""*/, const ParamType& type /*= ParamType::STRING*/){
//		if (this->mParameters.find(name) != this->mParameters.end()){
//			throw ParamException(name, "Parameter name already used. Please, try other name.");
//		}
//		this->mParameters[name] = Parameter(name, description, type);
//	}
//
//	void Parameters::addParameter(const Parameter& parameter){
//		if (this->mParameters.find(parameter.getName()) != this->mParameters.end()){
//			throw ParamException(parameter.getName(), "Parameter name already used. Please, try other name.");
//		}
//		this->mParameters[parameter.getName()] = parameter;
//	}
//
//	const std::map<std::string, Parameter>& Parameters::getParameters() const{
//		return this->mParameters;
//	}
//
//	void Parameters::readParamsFromFile(const std::string& fileName, const std::string& nodeName /*= ""*/){
//		cv::FileStorage fs(fileName, cv::FileStorage::READ);
//		cv::FileNode node = (nodeName == "") ? fs.root() : fs[nodeName];
//		for (auto current = node.begin(); current != node.end(); current++){
//			try{
//				Parameter param = this->converNodeToParameter(*current);
//				this->addParameter(param);
//			}
//			catch (Exception* e){
//				throw ParamException(fileName, e->what());
//			}			
//		}
//	}
//
//	Parameter Parameters::converNodeToParameter(const cv::FileNode& fileNode){
//		if (fileNode.size() != 1 || !fileNode.isNamed())
//			throw Exception("Parameters file with incorrect syntax!");
//		std::string paramName, paramValue;
//		paramName = fileNode.name();
//		fileNode >> paramValue;
//		ParamType paramType;
//		if (fileNode.isInt())
//			paramType = ParamType::INTEGER;
//		else if (fileNode.isReal())
//			paramType = ParamType::REAL;
//		else if (fileNode.isString())
//			paramType = ParamType::STRING;
//		else
//			throw Exception("Parameters file with incorrect syntax!");
//		Parameter param(paramName, "", paramType);
//		param.setValue(paramValue);
//		return param;
//	}
//
//}
//
