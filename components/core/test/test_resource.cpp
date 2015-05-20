#include <gtest/gtest.h>

#include "core/resource.hpp"

class ResourceSpecialization : public ssf::Resource{
public:
	std::string getName() { return "RESOURCE_SPECIALIZATION"; }
	std::string getType() { return "TYPE_RESOURCE_SPECIALIZATION"; }

	void initialize(){

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

	EXPECT_STREQ("RESOURCE_SPECIALIZATION", this->resource->getName().c_str());
	EXPECT_STREQ("TYPE_RESOURCE_SPECIALIZATION", this->resource->getType().c_str());

	ssf::ResourceInfo info = this->resource->getInfo();
	EXPECT_STREQ("Antonio", info.getAuthor().c_str());
	EXPECT_STREQ("antonio@ssig.br", info.getAuthorEmail().c_str());
	EXPECT_STREQ("resource_description", info.getDescription().c_str());
	EXPECT_STREQ("2.0.0", info.getRequiredVersion().toString().c_str());
	EXPECT_EQ(2, info.getRequiredVersion().getMajor());
	EXPECT_EQ(0, info.getRequiredVersion().getMinor());

	std::map<std::string, ssf::Parameter> paramsInfo = this->resource->getParameters();

	EXPECT_EQ(ssf::ParamType::INTEGER, paramsInfo["paramInt"].getType());
	EXPECT_STREQ("paramInt", paramsInfo["paramInt"].getName().c_str());
	EXPECT_STREQ("description_test_int", paramsInfo["paramInt"].getDescription().c_str());

}