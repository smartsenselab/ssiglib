#include <gtest/gtest.h>

#include "core/resource.hpp"
#include "core/resource_info.hpp"

class ResourceSpecialization : public ssf::Resource{

public:
	std::string getName() { return "RESOURCE_SPECIALIZATION"; }
	std::string getType() { return "TYPE_RESOURCE_SPECIALIZATION"; }

	ResourceSpecialization(){

		this->setAuthor("Antonio");
		this->setAuthorEmail("antonio@ssig.br");
		this->setDescription("resource_description");
		this->setRequiredVersion(2, 0);

		intValue = 99;
		doubleValue = 99999.88888888;
		boolValue = true;
		stringValue = "stringValue";
		fileHandleValue = ssf::FileHandle("test_file.txt");
		directoryHandleValue = ssf::DirectoryHandle("folder_test");
		intVectorValue = std::vector < int > {10, 11, 12};
		doubleVectorValue = std::vector < double > {1000, 1100.1, 1200.2};
		stringVectorValue = std::vector < std::string > {"a", "b", "c"};

		EXPECT_NO_THROW(this->PARAMETERS.addParameter("paramInt", intValue, "description_test_int"));
		EXPECT_NO_THROW(this->PARAMETERS.addParameter("paramDouble", doubleValue, "description_test_double"));
		EXPECT_NO_THROW(this->PARAMETERS.addParameter("paramBool", boolValue, "description_test_bool"));
		EXPECT_NO_THROW(this->PARAMETERS.addParameter("paramString", stringValue, "description_test_string"));
		EXPECT_NO_THROW(this->PARAMETERS.addParameter("paramFileHandle", fileHandleValue, "description_test_file"));
		EXPECT_NO_THROW(this->PARAMETERS.addParameter("paramDirectoryHandle", directoryHandleValue, "description_test_directory"));
		EXPECT_NO_THROW(this->PARAMETERS.addParameter("paramIntVector", intVectorValue, "description_test_intVector"));
		EXPECT_NO_THROW(this->PARAMETERS.addParameter("paramDoubleVector", doubleVectorValue, "description_test_doubleVector"));
		EXPECT_NO_THROW(this->PARAMETERS.addParameter("paramStringVector", stringVectorValue, "description_test_stringVector"));

	}

	int intValue;
	double doubleValue;
	bool boolValue;
	std::string stringValue;
	ssf::FileHandle fileHandleValue;
	ssf::DirectoryHandle directoryHandleValue;
	std::vector<int> intVectorValue;
	std::vector<double> doubleVectorValue;
	std::vector<std::string> stringVectorValue;

};


class TestResource : public ::testing::Test{
protected:

	virtual void SetUp(){
		EXPECT_NO_THROW(resource = new ResourceSpecialization());
	}

	virtual void TearDown() {
		delete resource;
	}

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

	std::map<std::string, ssf::ParameterInfo> paramsInfo = info.getParametersInfo();

	EXPECT_EQ(ssf::ParamType::INT, paramsInfo["paramInt"].getExpectedType());
	EXPECT_STREQ("paramInt", paramsInfo["paramInt"].getName().c_str());
	EXPECT_STREQ("description_test_int", paramsInfo["paramInt"].getDescription().c_str());

}