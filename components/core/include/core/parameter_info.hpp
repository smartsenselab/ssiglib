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

#ifndef _SSF_CORE_PARAMETER_INFO_HPP_
#define _SSF_CORE_PARAMETER_INFO_HPP_

#include <string>
#include "core/parameter.hpp"

namespace ssf{

	/**
	 * @brief	Information about a Parameter.
	 * 			
	 * @detail	Used for extract information about a Parameter.
	 */
	class ParameterInfo{

	public:

		/**
		 * @brief	Initializes a new instance of the ParameterInfo class.
		 */
		CORE_EXPORT ParameterInfo(void);

		/**
		 * @brief	Initializes a new instance of the ParameterInfo class.
		 *
		 * @param	parameter	The parameter in which info will be extracted.
		 */
		CORE_EXPORT ParameterInfo(const Parameter& parameter);

		/**
		 * @brief	Finalizes an instance of the ParameterInfo class.
		 */
		CORE_EXPORT virtual ~ParameterInfo(void);

		/**
		 * @brief	Initializes a new instance of the ParameterInfo class.
		 *
		 * @param	rhs	The right hand side.
		 */
		CORE_EXPORT ParameterInfo(const ParameterInfo& rhs);

		/**
		 * @brief	Assignment operator.
		 *
		 * @param	rhs	The right hand side.
		 *
		 * @return	A shallow copy of this object.
		 */
		CORE_EXPORT ParameterInfo& operator=(const ParameterInfo& rhs);

		/**
		 * @brief	Less-than comparison operator.
		 *
		 * @param	rhs	The right hand side.
		 *
		 * @return	true if the first parameter is less than the second.
		 */
		CORE_EXPORT bool operator<(const ParameterInfo& rhs);

		/**
		 * @brief	Equality operator.
		 *
		 * @param	rhs	The right hand side.
		 *
		 * @return	true if the parameters are considered equivalent.
		 */
		CORE_EXPORT bool operator==(const ParameterInfo& rhs);

		/**
		 * @brief	Inequality operator.
		 *
		 * @param	rhs	The right hand side.
		 *
		 * @return	true if the parameters are not considered equivalent.
		 */
		CORE_EXPORT bool operator!=(const ParameterInfo& rhs);

		/**
		 * @brief	Gets the parameter name.
		 *
		 * @return	A string with the parameter name.
		 */
		CORE_EXPORT std::string name() const;

		/**
		 * @brief	Gets the parameter description.
		 *
		 * @return	A string with the parameter description.
		 */
		CORE_EXPORT std::string description() const;

		/**
		 * @brief	Gets the expected parameter type.
		 *
		 * @return	The expected ParamType.
		 */
		CORE_EXPORT ParamType expectedType() const;

		/**
		 * @brief	Query if the parameter values is required.
		 *
		 * @return	true if required, false if not.
		 */
		CORE_EXPORT bool isRequired() const;

		/**
		 * @brief	Default value of parameter.
		 *
		 * @return	A default value as string.
		 */
		CORE_EXPORT std::string defaultValue() const;

		
		/**
		 * @brief	Default vector value of parameter.
		 *
		 * @return	A vector of strings;
		 */
		CORE_EXPORT std::vector<std::string> defaultVectorValue() const;


	private:
		Parameter mParameter;   ///< The internal parameter where information will be extracted

	};

}

#endif // !_SSF_CORE_PARAMETER_INFO_HPP_PP_