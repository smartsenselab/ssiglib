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

#ifndef _SSF_CORE_PARAMETER_SETUP_HPP_
#define _SSF_CORE_PARAMETER_SETUP_HPP_

#include <map>
#include <string>
#include <vector>

#include "core/core_defs.hpp"
#include "core/directory_handle.hpp"
#include "core/param_exception.hpp"

namespace cv{
	class FileNode;
}

namespace ssf{

	class ParametersSetup{

		/**
		 * @brief	This is a group of values for setup a Parameters object.
		 *
		 * @detail	The ParametersSetup must be used by final user for setup any Resource (for instance Modules).
		 */
		friend class Parameters;

	public:

		/**
		 * @brief	Initializes a new instance of the ParametersSetup class.
		 *
		 * @param	ID	The setup identifier.
		 */
		CORE_EXPORT ParametersSetup(const std::string& ID = "");

		/**
		 * @brief	Initializes a new instance of the ParametersSetup class.
		 *
		 * @param	paramFile	The file that describe the parameters values.
		 * @param	nodeID   	Identifier for the node (nodeID will be the parameter setup id).
		 */
		CORE_EXPORT ParametersSetup(const std::string& paramFile, const std::string& nodeID);

		/**
		 * @brief	Initializes a new instance of the ParametersSetup class.
		 *
		 * @param	paramFile	The file that describe the parameters values.
		 * @param	nodeID   	Identifier for the node (nodeID will be the parameter setup id).
		 */
		CORE_EXPORT ParametersSetup(const FileHandle& paramFile, const std::string& nodeID);

		/**
		 * @brief	Finalizes an instance of the ParametersSetup class.
		 */
		CORE_EXPORT virtual ~ParametersSetup(void);

		/**
		 * @brief	Initializes a new instance of the ParametersSetup class.
		 *
		 * @param	rhs	The right hand side.
		 */
		CORE_EXPORT ParametersSetup(const ParametersSetup& rhs);

		/**
		 * @brief	Assignment operator.
		 *
		 * @param	rhs	The right hand side.
		 *
		 * @return	A shallow copy of this object.
		 */
		CORE_EXPORT ParametersSetup& operator=(const ParametersSetup& rhs);

		/**
		 * @brief	Adds a parameter with a int value.
		 *
		 * @param	parameterName	Name of the parameter.
		 * @param	value		 	The int value.
		 */
		CORE_EXPORT void addParameter(const std::string& parameterName, const int& value);

		/**
		 * @brief	Adds a parameter with a double value.
		 *
		 * @param	parameterName	Name of the parameter.
		 * @param	value		 	The double value.
		 */
		CORE_EXPORT void addParameter(const std::string& parameterName, const double& value);

		/**
		 * @brief	Adds a parameter with a bool value.
		 *
		 * @param	parameterName	Name of the parameter.
		 * @param	value		 	The bool value.
		 */
		CORE_EXPORT void addParameter(const std::string& parameterName, const bool& value);

		/**
		 * @brief	Adds a parameter with a const char* value.
		 *
		 * @param	parameterName	Name of the parameter.
		 * @param	value		 	The char* value value.
		 */
		CORE_EXPORT void addParameter(const std::string& parameterName, const char* value);

		/**
		 * @brief	Adds a parameter with a string value.
		 *
		 * @param	parameterName	Name of the parameter.
		 * @param	value		 	The string value.
		 */
		CORE_EXPORT void addParameter(const std::string& parameterName, const std::string& value);

		/**
		 * @brief	Adds a parameter with a FileHandle value.
		 *
		 * @param	parameterName	Name of the parameter.
		 * @param	value		 	The FileHandle value.
		 */
		CORE_EXPORT void addParameter(const std::string& parameterName, const FileHandle& value);

		/**
		 * @brief	Adds a parameter with a DirectoryHandle value.
		 *
		 * @param	parameterName	Name of the parameter.
		 * @param	value		 	The DirectoryHandle value.
		 */
		CORE_EXPORT void addParameter(const std::string& parameterName, const DirectoryHandle& value);

		/**
		 * @brief	Adds a parameter with a vector<int> value.
		 *
		 * @param	parameterName	Name of the parameter.
		 * @param	value		 	The vector<int> value.
		 */
		CORE_EXPORT void addParameter(const std::string& parameterName, const std::vector<int>& value);

		/**
		 * @brief	Adds a parameter with a vector<double> value.
		 *
		 * @param	parameterName	Name of the parameter.
		 * @param	value		 	The vector<double> value.
		 */
		CORE_EXPORT void addParameter(const std::string& parameterName, const std::vector<double>& value);

		/**
		 * @brief	Adds a parameter with a vector<string> value.
		 *
		 * @param	parameterName	Name of the parameter.
		 * @param	value		 	The vector<string> value.
		 */
		CORE_EXPORT void addParameter(const std::string& parameterName, const std::vector<std::string>& value);

		/**
		 * @brief	Sets a new int value to parameter.
		 *
		 * @param	parameterName	Name of the parameter.
		 * @param	value		 	The new int value.
		 */
		CORE_EXPORT void setValue(const std::string& parameterName, const int& value);

		/**
		 * @brief	Sets a new double value to parameter.
		 *
		 * @param	parameterName	Name of the parameter.
		 * @param	value		 	The new double value.
		 */
		CORE_EXPORT void setValue(const std::string& parameterName, const double& value);

		/**
		 * @brief	Sets a new bool value to parameter.
		 *
		 * @param	parameterName	Name of the parameter.
		 * @param	value		 	The new bool value.
		 */
		CORE_EXPORT void setValue(const std::string& parameterName, const bool& value);

		/**
		 * @brief	Sets a new const char* value to parameter.
		 *
		 * @param	parameterName	Name of the parameter.
		 * @param	value		 	The new const char* value.
		 */
		CORE_EXPORT void setValue(const std::string& parameterName, const char* value);

		/**
		 * @brief	Sets a new string value to parameter.
		 *
		 * @param	parameterName	Name of the parameter.
		 * @param	value		 	The new string value.
		 */
		CORE_EXPORT void setValue(const std::string& parameterName, const std::string& value);

		/**
		 * @brief	Sets a new FileHandle value to parameter.
		 *
		 * @param	parameterName	Name of the parameter.
		 * @param	value		 	The new FileHandle value.
		 */
		CORE_EXPORT void setValue(const std::string& parameterName, const FileHandle& value);

		/**
		 * @brief	Sets a new DirectoryHandle value to parameter.
		 *
		 * @param	parameterName	Name of the parameter.
		 * @param	value		 	The new DirectoryHandle value.
		 */
		CORE_EXPORT void setValue(const std::string& parameterName, const DirectoryHandle& value);

		/**
		 * @brief	Sets a new vector<int> value to parameter.
		 *
		 * @param	parameterName	Name of the parameter.
		 * @param	value		 	The new vector<int> value.
		 */
		CORE_EXPORT void setValue(const std::string& parameterName, const std::vector<int>& value);

		/**
		 * @brief	Sets a new vector<double> value to parameter.
		 *
		 * @param	parameterName	Name of the parameter.
		 * @param	value		 	The new vector<double> value.
		 */
		CORE_EXPORT void setValue(const std::string& parameterName, const std::vector<double>& value);

		/**
		 * @brief	Sets a new vector<string> value to parameter.
		 *
		 * @param	parameterName	Name of the parameter.
		 * @param	value		 	The new vector<string> value.
		 */
		CORE_EXPORT void setValue(const std::string& parameterName, const std::vector<std::string>& value);

		/**
		 * @brief	Converts the parameter value to an int.
		 *
		 * @param	parameterName	Name of the parameter.
		 *
		 * @return	The parameter value as an int.
		 */
		CORE_EXPORT int toInt(const std::string& parameterName);

		/**
		 * @brief	Converts the parameter value to a double.
		 *
		 * @param	parameterName	Name of the parameter.
		 *
		 * @return	The parameter value as a double.
		 */
		CORE_EXPORT double toDouble(const std::string& parameterName);

		/**
		 * @brief	Converts the parameter value to a bool.
		 *
		 * @param	parameterName	Name of the parameter.
		 *
		 * @return	The parameter value as a bool.
		 */
		CORE_EXPORT bool toBool(const std::string& parameterName);

		/**
		 * @brief	Converts the parameter value to a string.
		 *
		 * @param	parameterName	Name of the parameter.
		 *
		 * @return	The parameter value as a string.
		 */
		CORE_EXPORT std::string toString(const std::string& parameterName);

		/**
		 * @brief	Converts the parameter to a file handle.
		 *
		 * @param	parameterName	Name of the parameter.
		 *
		 * @return	The parameter value as a FileHandle.
		 */
		CORE_EXPORT FileHandle toFileHandle(const std::string& parameterName);

		/**
		 * @brief	Converts the parameter to a directory handle.
		 *
		 * @param	parameterName	Name of the parameter.
		 *
		 * @return	The parameter value as a DirectoryHandle.
		 */
		CORE_EXPORT DirectoryHandle toDirectoryHandle(const std::string& parameterName);

		/**
		 * @brief	Converts the parameter to an int vector.
		 *
		 * @param	parameterName	Name of the parameter.
		 *
		 * @return	The parameter value as a vector<int>;
		 */
		CORE_EXPORT std::vector<int> toIntVector(const std::string& parameterName);

		/**
		 * @brief	Converts the parameter to a double vector.
		 *
		 * @param	parameterName	Name of the parameter.
		 *
		 * @return	The parameter value as a vector<double>;
		 */
		CORE_EXPORT std::vector<double> toDoubleVector(const std::string& parameterName);

		/**
		 * @brief	Converts the parameter to a string vector.
		 *
		 * @param	parameterName	Name of the parameter.
		 *
		 * @return	The parameter value as a vector<string>;
		 */
		CORE_EXPORT std::vector<std::string> toStringVector(const std::string& parameterName);

		/**
		 * @brief	Gets the identifier.
		 *
		 * @return	A std::string.
		 */
		CORE_EXPORT std::string ID() const;

		/**
		 * @brief	Sets an identifier.
		 *
		 * @param	setupID	Identifier for the setup.
		 */
		CORE_EXPORT void setID(const std::string& setupID);

	protected:

		template<class T>
		CORE_EXPORT void _addParameter(const std::string& parameterName, const T& value){
			if (this->mParametersValues.find(parameterName) != this->mParametersValues.end())
				throw ParamException(parameterName, "Already exists a parameter with it name.");
			this->mParametersValues[parameterName] = std::vector<std::string>(1); 

			/**
			 * @brief	Initializes a new instance of the ParametersSetup class.
			 *
			 * @param	parameter1	The first parameter.
			 * @param	parameter2	The second parameter.
			 */
			this->setValue(parameterName, value);
		}

		CORE_EXPORT void _setParameter(const std::string& parameterName, const std::vector<std::string>& value);
		CORE_EXPORT void _readParamsFromFile(const std::string& fileName, const std::string& node = "");
		CORE_EXPORT void _convertNodeToValue(const cv::FileNode& fileNode);

	private:
		std::string mID;	///< The setup identifier
		std::map<std::string, std::vector<std::string>> mParametersValues;  ///< The parameters values
	};

}

#endif // !_SSF_CORE_PARAMETER_SETUP_HPP_PP_