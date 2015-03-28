#include <gtest/gtest.h>

#include "core/resource.hpp"

class ResourceSpecialization : public ssf::Resource{
public:
	std::string getName() { return "RESOURCE_SPECIALIZATION"; }

	void initialize(){

		this->setAuthor("Antonio");
		this->setAuthorEmail("antonio@ssig.br");
		this->setDescription("resource_description");
		this->setRequiredVersion(2, 0);

		this->PARAMETERS.addParameter(ssf::ParamType::INT, "paramInt", "description_test_int");
		this->PARAMETERS.addParameter(ssf::ParamType::LONG, "paramLong", "description_test_long");
		this->PARAMETERS.addParameter(ssf::ParamType::FLOAT, "paramFloat", "description_test_float");
		this->PARAMETERS.addParameter(ssf::ParamType::DOUBLE, "paramDouble", "description_test_double");
		this->PARAMETERS.addParameter(ssf::ParamType::BOOL, "paramBool", "description_test_bool");
		this->PARAMETERS.addParameter(ssf::ParamType::STRING, "paramString", "description_test_string");
		this->PARAMETERS.addParameter(ssf::ParamType::FILE_HANDLE, "paramFile", "description_test_file");
		this->PARAMETERS.addParameter(ssf::ParamType::DIRECTORY_HANDLE, "paramDirectory", "description_test_directory");
	}

};


class TestResource : public ::testing::Test{
protected:

	virtual void SetUp(){
		intValue = 99;
		longValue = 99999;
		floatValue = float(99.88);
		doubleValue = 99999.88888888;
		boolValue = true;
		stringValue = "stringValue";
		fileHandleValue = ssf::FileHandle("test_file.txt");
		directoryHandleValue = ssf::DirectoryHandle("folder_test");

		EXPECT_NO_THROW(resource = new ResourceSpecialization());
		resource->initialize();
	}

	virtual void TearDown() {
		delete resource;
	}

	int intValue;
	long longValue;
	float floatValue;
	double doubleValue;
	bool boolValue;
	std::string stringValue;
	ssf::FileHandle fileHandleValue;
	ssf::DirectoryHandle directoryHandleValue;


	ResourceSpecialization* resource;
};

TEST_F(TestResource, resourceInfo){
	ssf::ResourceInfo info = this->resource->getInfo();
	EXPECT_STREQ("Antonio", info.getAuthor().c_str());
	EXPECT_STREQ("antonio@ssig.br", info.getAuthorEmail().c_str());
	EXPECT_STREQ("resource_description", info.getDescription().c_str());
	EXPECT_STREQ("2.0", info.getRequiredVersion().c_str());
	EXPECT_EQ(2, info.getMajorRequiredVersion());
	EXPECT_EQ(0, info.getMinorRequiredVersion());

	std::map<std::string, ssf::Param> paramsInfo = info.getParams();

	EXPECT_EQ(ssf::ParamType::INT, paramsInfo["paramInt"].getType());
	EXPECT_STREQ("paramInt", paramsInfo["paramInt"].getName().c_str());
	EXPECT_STREQ("description_test_int", paramsInfo["paramInt"].getDescription().c_str());

}