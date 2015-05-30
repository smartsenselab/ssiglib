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

#ifndef _SSF_CORE_PARAMETER_LIST_HPP_
#define _SSF_CORE_PARAMETER_LIST_HPP_

#include <string>
#include <map>
#include <vector>
#include <memory>

#include "core/parameter.hpp"
#include "core/file_handle.hpp"

#include "parameters_setup.hpp"
#include "parameter_info.hpp"

namespace ssf{

	/**
	 * @brief	Used by user to create parameters and access its values.
	 */
	class Parameters{

	public:

		/**
		 * @brief	Initializes a new instance of the Parameters class.
		 */
		CORE_EXPORT Parameters(void);

		/**
		 * @brief	Finalizes an instance of the Parameters class.
		 */
		CORE_EXPORT virtual ~Parameters(void);

		/**
		 * @brief	Initializes a new instance of the Parameters class.
		 *
		 * @param	rhs	The right hand side.
		 */
		CORE_EXPORT Parameters(const Parameters& rhs);

		/**
		 * @brief	Assignment operator.
		 *
		 * @param	rhs	The right hand side.
		 *
		 * @return	A shallow copy of this object.
		 */
		CORE_EXPORT Parameters& operator=(const Parameters& rhs);

		/**
		 * @brief	Array indexer operator.
		 *
		 * @param	parameterName	Name of the parameter.
		 *
		 * @return	The indexed value.
		 */
		CORE_EXPORT Parameter& operator[](const std::string& parameterName);

		/**
		 * @brief	Gets a parameter.
		 *
		 * @param	parameterName	Name of the parameter.
		 *
		 * @return	The parameter.
		 */
		CORE_EXPORT Parameter& getParameter(const std::string& parameterName);

		/**
		 * @brief	Adds a parameter to 'description'.
		 *
		 * @param	paramName  	Name of the parameter.
		 * @param	description	The description.
		 */
		CORE_EXPORT void addParameter(const std::string& parameterName, const std::string& description = "no description.");

		/**
		 * @brief	Adds a int parameter.
		 *
		 * @param	paramName   	Name of the parameter.
		 * @param	defaultValue	The default int value.
		 * @param	description 	The description.
		 */
		CORE_EXPORT void addParameter(const std::string& parameterName, const int& defaultValue, const std::string& description = "no description.");

		/**
		 * @brief	Adds a double parameter.
		 *
		 * @param	paramName   	Name of the parameter.
		 * @param	defaultValue	The default double value.
		 * @param	description 	The description.
		 */
		CORE_EXPORT void addParameter(const std::string& parameterName, const double& defaultValue, const std::string& description = "no description.");

		/**
		 * @brief	Adds a bool parameter.
		 *
		 * @param	paramName   	Name of the parameter.
		 * @param	defaultValue	The default bool value.
		 * @param	description 	The description.
		 */
		CORE_EXPORT void addParameter(const std::string& parameterName, const bool& defaultValue, const std::string& description = "no description.");

		/**
		 * @brief	Adds a const char* parameter.
		 *
		 * @param	paramName   	Name of the parameter.
		 * @param	defaultValue	The default const char* value.
		 * @param	description 	The description.
		 */
		CORE_EXPORT void addParameter(const std::string& parameterName, const char* defaultValue, const std::string& description = "no description.");

		/**
		 * @brief	Adds a string parameter.
		 *
		 * @param	paramName   	Name of the parameter.
		 * @param	defaultValue	The default string value.
		 * @param	description 	The description.
		 */
		CORE_EXPORT void addParameter(const std::string& parameterName, const std::string& defaultValue, const std::string& description = "no description.");

		/**
		 * @brief	Adds a FileHandle parameter.
		 *
		 * @param	paramName   	Name of the parameter.
		 * @param	defaultValue	The default FileHandle value.
		 * @param	description 	The description.
		 */
		CORE_EXPORT void addParameter(const std::string& parameterName, const FileHandle& defaultValue, const std::string& description = "no description.");

		/**
		 * @brief	Adds a DirectoryHandle parameter.
		 *
		 * @param	paramName   	Name of the parameter.
		 * @param	defaultValue	The default DirectoryHandle value.
		 * @param	description 	The description.
		 */
		CORE_EXPORT void addParameter(const std::string& parameterName, const DirectoryHandle& defaultValue, const std::string& description = "no description.");

		/**
		 * @brief	Adds a vector<int> parameter.
		 *
		 * @param	paramName   	Name of the parameter.
		 * @param	defaultValue	The default vector<int> value.
		 * @param	description 	The description.
		 */
		CORE_EXPORT void addParameter(const std::string& parameterName, const std::vector<int>& defaultValue, const std::string& description = "no description.");

		/**
		 * @brief	Adds a vector<double> parameter.
		 *
		 * @param	paramName   	Name of the parameter.
		 * @param	defaultValue	The default vector<double> value.
		 * @param	description 	The description.
		 */
		CORE_EXPORT void addParameter(const std::string& parameterName, const std::vector<double>& defaultValue, const std::string& description = "no description.");

		/**
		 * @brief	Adds a vector<string> parameter.
		 *
		 * @param	paramName   	Name of the parameter.
		 * @param	defaultValue	The default vector<string> value.
		 * @param	description 	The description.
		 */
		CORE_EXPORT void addParameter(const std::string& parameterName, const std::vector<std::string>& defaultValue, const std::string& description = "no description.");

		/**
		 * @brief	Adds a parameter.
		 *
		 * @param	parameter	The parameter.
		 */
		CORE_EXPORT void addParameter(const Parameter& parameter);

		/**
		 * @brief	Setup the parameters value by a parameter file.
		 *
		 * @param	paramFile	The parameter file.
		 * @param	nodeID   	Identifier for the node.
		 */
		CORE_EXPORT void setup(const std::string& paramFile, const std::string& nodeID);

		/**
		 * @brief	Setup the parameters value by a parameter file.
		 *
		 * @param	paramFile	The parameter file.
		 * @param	nodeID   	Identifier for the node.
		 */
		CORE_EXPORT void setup(const FileHandle& paramFile, const std::string& nodeID);

		/**
		 * @brief	Setup the parameters value by a ParametersSetup.
		 *
		 * @param	paramSetup	The parameter setup.
		 */
		CORE_EXPORT void setup(const ParametersSetup& paramSetup);

		/**
		 * @brief	Has a parameter with the name.
		 *
		 * @param	paramName	Name of the parameter.
		 *
		 * @return	true if it succeeds, false if it fails.
		 */
		CORE_EXPORT bool has(const std::string& parameterName);

		/**
		 * @brief	Gets parameters information.
		 *
		 * @return	A std::map&lt;std::string,ParameterInfo&gt;
		 */
		CORE_EXPORT std::map<std::string, ParameterInfo> parametersInfo();

	private:
		std::map<std::string, Parameter> mParameters;   ///< Options for controlling the operation
	
	};

}

#endif // !_SSF_CORE_PARAMETER_LIST_HPP_PP_