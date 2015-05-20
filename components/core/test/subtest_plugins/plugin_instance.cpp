#include "plugin_instance.hpp"

PLUGIN_DEFINITION(ResourceSpecialization)

void ResourceSpecialization::initialize(){
	this->setAuthor("Antonio");
	this->setAuthorEmail("antonio@ssig.br");
	this->setDescription("resource_description");
	this->setRequiredVersion(2, 0);

	this->PARAMETERS.addParameter("paramInt", "description_test_int", ssf::ParamType::INTEGER);
	this->PARAMETERS.addParameter("paramLong", "description_test_long", ssf::ParamType::INTEGER);
	this->PARAMETERS.addParameter("paramFloat", "description_test_float", ssf::ParamType::REAL);
	this->PARAMETERS.addParameter("paramDouble", "description_test_double", ssf::ParamType::REAL);
	this->PARAMETERS.addParameter("paramBool", "description_test_bool", ssf::ParamType::BOOL);
	this->PARAMETERS.addParameter("paramString", "description_test_string", ssf::ParamType::STRING);
	this->PARAMETERS.addParameter("paramFile", "description_test_file", ssf::ParamType::FILE_HANDLE);
	this->PARAMETERS.addParameter("paramDirectory", "description_test_directory", ssf::ParamType::DIRECTORY_HANDLE);
}
