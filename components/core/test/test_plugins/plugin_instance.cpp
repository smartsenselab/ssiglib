//          Copyright Jeremy Coulon 2012-2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//[MyPlugin_cpp_file
#include "plugin_instance.hpp"

// The only important thing is to call the macro PLUGIN_FACTORY_DEFINITION(T).
// Define plugin factory. Must be in the global namespace.
PLUGIN_FACTORY_DEFINITION(Example::ResourceSpecialization)


//]

void Example::ResourceSpecialization::initialize(){
	this->setAuthor("Antonio");
	this->setAuthorEmail("antonio@ssig.br");
	this->setDescription("resource_description");
	this->setRequiredVersion(2, 0);

	this->parameters.addParameter(ssf::ParamType::INT, "paramInt", "description_test_int");
	this->parameters.addParameter(ssf::ParamType::LONG, "paramLong", "description_test_long");
	this->parameters.addParameter(ssf::ParamType::FLOAT, "paramFloat", "description_test_float");
	this->parameters.addParameter(ssf::ParamType::DOUBLE, "paramDouble", "description_test_double");
	this->parameters.addParameter(ssf::ParamType::BOOL, "paramBool", "description_test_bool");
	this->parameters.addParameter(ssf::ParamType::STRING, "paramString", "description_test_string");
	this->parameters.addParameter(ssf::ParamType::FILE_HANDLE, "paramFile", "description_test_file");
	this->parameters.addParameter(ssf::ParamType::DIRECTORY_HANDLE, "paramDirectory", "description_test_directory");
}
