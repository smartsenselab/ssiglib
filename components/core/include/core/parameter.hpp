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

#ifndef _SSF_CORE_PARAMETER_HPP_
#define _SSF_CORE_PARAMETER_HPP_

#include <string>
#include <memory>
#include <sstream>
#include <iomanip>
#include <vector>

#include "core/core_defs.hpp"
#include "core/file_handle.hpp"
#include "core/directory_handle.hpp"

#define CHECK_TYPE std::is_arithmetic<T>::value && std::is_convertible<T, std::string>::value

namespace ssf{

	/**
	 * @brief	Expected types of Parameters. Allows user to set which type of value is expected.
	 */
	enum class CORE_EXPORT ParamType{
		INT,	///< Expected a int value
		DOUBLE, ///< Expected a double value
		BOOL,   ///< Expected a bool value
		STRING, ///< Expected a string value
		FILE_HANDLE,	///< Expected a FileHandle value
		DIRECTORY_HANDLE,   ///< Expected a DirectoryHandle value
		INT_VECTOR, ///< Expected vector of int value
		DOUBLE_VECTOR,  ///< Expected vector of double value
		STRING_VECTOR   ///< Expected vector of string value
	};

	/**
	 * @brief	Parameter class.
	 * 			
	 * @detail	Represents a value which is required by a resource. It accept the follow value types:
	 * 			{int, double book, string, FileHandle, DirectoryHandle, vector<int>, vector<double>, vector<string>}. 
	 * 			The default type is string.
	 * 			</br>
	 *			The Parameters values can be set only by the Parameters class.
	 */
	class Parameter{
		friend class ParameterInfo;
		friend class Parameters;

	public:

		/**
		 * @brief	Initializes a new instance of the Parameter class.
		 */
		CORE_EXPORT Parameter(void);

		/**
		 * @brief	Initializes a new instance of the Parameter class.
		 *
		 * @param	name			The parameter name.
		 * @param	defaultValue	The int default value.
		 * @param	description 	The parameter description.
		 */
		CORE_EXPORT Parameter(const std::string& name, const int& defaultValue, const std::string& description = "no description.");

		/**
		 * @brief	Initializes a new instance of the Parameter class.
		 *
		 * @param	name			The parameter name.
		 * @param	defaultValue	The double default value.
		 * @param	description 	The parameter description.
		 */
		CORE_EXPORT Parameter(const std::string& name, const double& defaultValue, const std::string& description = "no description.");

		/**
		 * @brief	Initializes a new instance of the Parameter class.
		 *
		 * @param	name			The parameter name.
		 * @param	defaultValue	The bool default value.
		 * @param	description 	The parameter description.
		 */
		CORE_EXPORT Parameter(const std::string& name, const bool& defaultValue, const std::string& description = "no description.");

		/**
		 * @brief	Initializes a new instance of the Parameter class.
		 *
		 * @param	name			The parameter name.
		 * @param	defaultValue	The const char* default value. Will be converted into a string.
		 * @param	description 	The parameter description.
		 */
		CORE_EXPORT Parameter(const std::string& name, const char* defaultValue, const std::string& description = "no description.");

		/**
		 * @brief	Initializes a new instance of the Parameter class.
		 *
		 * @param	name			The parameter name.
		 * @param	defaultValue	The string default value.
		 * @param	description 	The parameter description.
		 */
		CORE_EXPORT Parameter(const std::string& name, const std::string& defaultValue, const std::string& description = "no description.");

		/**
		 * @brief	Initializes a new instance of the Parameter class.
		 *
		 * @param	name			The parameter name.
		 * @param	defaultValue	The FileHandle default value.
		 * @param	description 	The parameter description
		 */
		CORE_EXPORT Parameter(const std::string& name, const FileHandle& defaultValue, const std::string& description = "no description.");

		/**
		 * @brief	Initializes a new instance of the Parameter class.
		 *
		 * @param	name			The parameter name.
		 * @param	defaultValue	The string default value.
		 * @param	description 	The parameter description
		 */
		CORE_EXPORT Parameter(const std::string& name, const DirectoryHandle& defaultValue, const std::string& description = "no description.");

		/**
		 * @brief	Initializes a new instance of the Parameter class.
		 *
		 * @param	name			The parameter name.
		 * @param	defaultValue	The vector<int> default value.
		 * @param	description 	The parameter description
		 */
		CORE_EXPORT Parameter(const std::string& name, const std::vector<int>& defaultValue, const std::string& description = "no description.");

		/**
		 * @brief	Initializes a new instance of the Parameter class.
		 *
		 * @param	name			The parameter name.
		 * @param	defaultValue	The vector<double> default value.
		 * @param	description 	The parameter description
		 */
		CORE_EXPORT Parameter(const std::string& name, const std::vector<double>& defaultValue, const std::string& description = "no description.");

		/**
		 * @brief	Initializes a new instance of the Parameter class.
		 *
		 * @param	name			The parameter name.
		 * @param	defaultValue	The vector<string> default value.
		 * @param	description 	The parameter description
		 */
		CORE_EXPORT Parameter(const std::string& name, const std::vector<std::string>& defaultValue, const std::string& description = "no description.");

		/**
		 * @brief	Finalizes an instance of the Parameter class.
		 */
		CORE_EXPORT virtual ~Parameter(void);

		/**
		 * @brief	Initializes a new instance of the Parameter class.
		 *
		 * @param	rhs	The right hand side.
		 */
		CORE_EXPORT Parameter(const Parameter& rhs);

		/**
		 * @brief	Assignment operator.
		 *
		 * @param	rhs	The right hand side.
		 *
		 * @return	A shallow copy of this object.
		 */
		CORE_EXPORT Parameter& operator=(const Parameter& rhs);

		/**
		 * @brief	Less-than comparison operator.
		 *
		 * @param	rhs	The right hand side.
		 *
		 * @return	true if the first parameter is less than the second.
		 */
		CORE_EXPORT bool operator<(const Parameter& rhs) const;

		/**
		 * @brief	Equality operator.
		 *
		 * @param	rhs	The right hand side.
		 *
		 * @return	true if the parameters are considered equivalent.
		 */
		CORE_EXPORT bool operator==(const Parameter& rhs) const;

		/**
		 * @brief	Inequality operator.
		 *
		 * @param	rhs	The right hand side.
		 *
		 * @return	true if the parameters are not considered equivalent.
		 */
		CORE_EXPORT bool operator!=(const Parameter& rhs) const;

		/**
		 * @brief	Converts the parameter value to an int.
		 *
		 * @return	The parameter value as an int.
		 */
		CORE_EXPORT int toInt() const;

		/**
		 * @brief	Converts the parameter value to a double.
		 *
		 * @return	The parameter value as a double.
		 */
		CORE_EXPORT double toDouble() const;

		/**
		 * @brief	Converts the parameter value to a bool.
		 *
		 * @return	The parameter value as a bool.
		 */
		CORE_EXPORT bool toBool() const;

		/**
		 * @brief	Convert The parameter value into a string representation.
		 *
		 * @return	A std::string that represents The parameter value.
		 */
		CORE_EXPORT std::string toString() const;

		/**
		 * @brief	Converts the parameter value to a file handle.
		 *
		 * @return	The parameter value as a FileHandle.
		 */
		CORE_EXPORT FileHandle toFileHandle() const;

		/**
		 * @brief	Converts the parameter value to a directory handle.
		 *
		 * @return	The parameter value as a DirectoryHandle.
		 */
		CORE_EXPORT DirectoryHandle toDirectoryHandle() const;

		/**
		 * @brief	Converts the parameter value to an int vector.
		 *
		 * @return	The parameter value as a std::vector&lt;int&gt;
		 */
		CORE_EXPORT std::vector<int> toIntVector() const;

		/**
		 * @brief	Converts the parameter value to a double vector.
		 *
		 * @return	The parameter value as a std::vector&lt;double&gt;
		 */
		CORE_EXPORT std::vector<double> toDoubleVector() const;

		/**
		 * @brief	Converts the parameter value to a string vector.
		 *
		 * @return	The parameter value as a std::vector&lt;std::string&gt;
		 */
		CORE_EXPORT std::vector<std::string> toStringVector() const;

		/**
		 * @brief	Query if the parameter value is int.
		 *
		 * @return	true if int, false if not.
		 */
		CORE_EXPORT bool isInt();

		/**
		 * @brief	Query if the parameter value is double.
		 *
		 * @return	true if double, false if not.
		 */
		CORE_EXPORT bool isDouble();

		/**
		 * @brief	Query if the parameter value is int vector.
		 *
		 * @return	true if int vector, false if not.
		 */
		CORE_EXPORT bool isIntVector();

		/**
		 * @brief	Query if the parameter value is double vector.
		 *
		 * @return	true if double vector, false if not.
		 */
		CORE_EXPORT bool isDoubleVector();

		/**
		 * @brief	Query if 'stringValue' is int.
		 *
		 * @param	stringValue	The string value.
		 *
		 * @return	true if int, false if not.
		 */
		CORE_EXPORT static bool isInt(const std::string& stringValue);

		/**
		 * @brief	Query if 'stringValue' is double.
		 *
		 * @param	stringValue	The string value.
		 *
		 * @return	true if double, false if not.
		 */
		CORE_EXPORT static bool isDouble(const std::string& stringValue);

		/**
		 * @brief	Query if 'vectorStringValue' is int vector.
		 *
		 * @param	vectorStringValue	The vector string value.
		 *
		 * @return	true if int vector, false if not.
		 */
		CORE_EXPORT static bool isIntVector(const std::vector<std::string> vectorStringValue);

		/**
		 * @brief	Query if 'vectorStringValue' is double vector.
		 *
		 * @param	vectorStringValue	The vector string value.
		 *
		 * @return	true if double vector, false if not.
		 */
		CORE_EXPORT static bool isDoubleVector(const std::vector<std::string> vectorStringValue);

		/**
		 * @brief	Gets the name.
		 *
		 * @return	A std::string.
		 */
		CORE_EXPORT std::string name() const;

		/**
		 * @brief	Restore to default value.
		 */
		CORE_EXPORT void restoreToDefaultValue();

		/**
		 * @brief	Expected type.
		 *
		 * @return	A ParamType.
		 */
		CORE_EXPORT ParamType expectedType() const;

		/**
		 * @brief	Sets expected type.
		 *
		 * @param	expectedType	Type of the expected.
		 */
		CORE_EXPORT void setExpectedType(const ssf::ParamType& expectedType);

		/**
		 * @brief	Gets the description.
		 *
		 * @return	A std::string.
		 */
		CORE_EXPORT std::string description() const;

		/**
		 * @brief	Sets a description.
		 *
		 * @param	description	The description.
		 */
		CORE_EXPORT void setDescription(const std::string& description);

		/**
		 * @brief	Query if the parameter value is required. In other words, a required parameter must be
		 * 			set.
		 *
		 * @return	true if required, false if not.
		 */
		CORE_EXPORT bool isRequired() const;

		/**
		 * @brief	Sets as a required parameter.
		 *
		 * @param	required	Boolean value (true if required, false if not).
		 */
		CORE_EXPORT void setRequired(const bool& required);

	private:
		std::string mName;  ///< The parameter name
		std::string mDescription;   ///< The parameter description
		ParamType mExpectedType;	///< The expected type of parameter

		std::vector<std::string> mValue;	///< The value
		std::vector<std::string> mDefaultValue; ///< The default value

		bool mRequired; ///< true if required
	};

}

#endif // !_SSF_CORE_PARAMETER_HPP_PP_