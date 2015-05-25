#include <gtest/gtest.h>

#include <map>

#include "core/parameter.hpp"

class TestParameter : public ::testing::Test{
public:

	virtual void SetUp(){

		intValue = 99;
		doubleValue = 99999.88888888;
		boolValue = true;
		stringValue = "stringValue";
		fileHandleValue = ssf::FileHandle("test_file.txt");
		directoryHandleValue = ssf::DirectoryHandle("folder_test");
		intVectorValue = std::vector < int > {10, 11, 12};
		doubleVectorValue = std::vector < double > {1000, 1100.1, 1200.2};
		stringVectorValue = std::vector < std::string > {"a", "b", "c"};

		EXPECT_NO_THROW(parameters["paramInt"] = ssf::Parameter("paramInt", intValue, "description_test_int"));
		EXPECT_NO_THROW(parameters["paramDouble"] = ssf::Parameter("paramDouble", doubleValue, "description_test_double"));
		EXPECT_NO_THROW(parameters["paramBool"] = ssf::Parameter("paramBool", boolValue, "description_test_bool"));
		EXPECT_NO_THROW(parameters["paramString"] = ssf::Parameter("paramString", stringValue, "description_test_string"));
		EXPECT_NO_THROW(parameters["paramFileHandle"] = ssf::Parameter("paramFileHandle", fileHandleValue, "description_test_file"));
		EXPECT_NO_THROW(parameters["paramDirectoryHandle"] = ssf::Parameter("paramDirectoryHandle", directoryHandleValue, "description_test_directory"));
		EXPECT_NO_THROW(parameters["paramIntVector"] = ssf::Parameter("paramIntVector", intVectorValue, "description_test_intVector"));
		EXPECT_NO_THROW(parameters["paramDoubleVector"] = ssf::Parameter("paramDoubleVector", doubleVectorValue, "description_test_doubleVector"));
		EXPECT_NO_THROW(parameters["paramStringVector"] = ssf::Parameter("paramStringVector", stringVectorValue, "description_test_stringVector"));
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


	std::map<std::string, ssf::Parameter> parameters;
};

TEST_F(TestParameter, getName){
	EXPECT_EQ("paramInt", parameters["paramInt"].getName());
	EXPECT_EQ("paramDouble", parameters["paramDouble"].getName());
	EXPECT_EQ("paramBool", parameters["paramBool"].getName());
	EXPECT_EQ("paramString", parameters["paramString"].getName());
	EXPECT_EQ("paramFileHandle", parameters["paramFileHandle"].getName());
	EXPECT_EQ("paramDirectoryHandle", parameters["paramDirectoryHandle"].getName());
	EXPECT_EQ("paramIntVector", parameters["paramIntVector"].getName());
	EXPECT_EQ("paramDoubleVector", parameters["paramDoubleVector"].getName());
	EXPECT_EQ("paramStringVector", parameters["paramStringVector"].getName());
}

TEST_F(TestParameter, getDescription){
	EXPECT_EQ("description_test_int", parameters["paramInt"].getDescription());
	EXPECT_EQ("description_test_double", parameters["paramDouble"].getDescription());
	EXPECT_EQ("description_test_bool", parameters["paramBool"].getDescription());
	EXPECT_EQ("description_test_string", parameters["paramString"].getDescription());
	EXPECT_EQ("description_test_file", parameters["paramFileHandle"].getDescription());
	EXPECT_EQ("description_test_directory", parameters["paramDirectoryHandle"].getDescription());
	EXPECT_EQ("description_test_intVector", parameters["paramIntVector"].getDescription());
	EXPECT_EQ("description_test_doubleVector", parameters["paramDoubleVector"].getDescription());
	EXPECT_EQ("description_test_stringVector", parameters["paramStringVector"].getDescription());
}

TEST_F(TestParameter, getType){
	EXPECT_EQ(ssf::ParamType::INT, parameters["paramInt"].getExpectedType());
	EXPECT_EQ(ssf::ParamType::DOUBLE, parameters["paramDouble"].getExpectedType());
	EXPECT_EQ(ssf::ParamType::BOOL, parameters["paramBool"].getExpectedType());
	EXPECT_EQ(ssf::ParamType::STRING, parameters["paramString"].getExpectedType());
	EXPECT_EQ(ssf::ParamType::FILE_HANDLE, parameters["paramFileHandle"].getExpectedType());
	EXPECT_EQ(ssf::ParamType::DIRECTORY_HANDLE, parameters["paramDirectoryHandle"].getExpectedType());
	EXPECT_EQ(ssf::ParamType::INT_VECTOR, parameters["paramIntVector"].getExpectedType());
	EXPECT_EQ(ssf::ParamType::DOUBLE_VECTOR, parameters["paramDoubleVector"].getExpectedType());
	EXPECT_EQ(ssf::ParamType::STRING_VECTOR, parameters["paramStringVector"].getExpectedType());
	
}

TEST_F(TestParameter, isRequired){
	EXPECT_FALSE(parameters["paramInt"].isRequired());
	EXPECT_FALSE(parameters["paramDouble"].isRequired());
	EXPECT_FALSE(parameters["paramBool"].isRequired());
	EXPECT_FALSE(parameters["paramString"].isRequired());
	EXPECT_FALSE(parameters["paramFileHandle"].isRequired());
	EXPECT_FALSE(parameters["paramDirectoryHandle"].isRequired());
	EXPECT_FALSE(parameters["paramIntVector"].isRequired());
	EXPECT_FALSE(parameters["paramDoubleVector"].isRequired());
	EXPECT_FALSE(parameters["paramStringVector"].isRequired());

	parameters["paramInt"].setRequired(true);
	EXPECT_TRUE(parameters["paramInt"].isRequired());
	parameters["paramInt"].setRequired(false);
	EXPECT_FALSE(parameters["paramInt"].isRequired());

}

TEST_F(TestParameter, testCopy){
	ssf::Parameter copyParameter(this->parameters["paramInt"]);
	EXPECT_EQ("paramInt", copyParameter.getName());
	EXPECT_EQ("description_test_int", copyParameter.getDescription());
	EXPECT_EQ(ssf::ParamType::INT, copyParameter.getExpectedType());
	EXPECT_FALSE(copyParameter.isRequired());

	ssf::Parameter lhsParameter = this->parameters["paramInt"];
	EXPECT_EQ("paramInt", lhsParameter.getName());
	EXPECT_EQ("description_test_int", lhsParameter.getDescription());
	EXPECT_EQ(ssf::ParamType::INT, lhsParameter.getExpectedType());
	EXPECT_FALSE(lhsParameter.isRequired());
}

TEST_F(TestParameter, toIntRegular){

	ssf::Parameter param("a", 10);
	EXPECT_EQ(10, param.toInt());
	param = ssf::Parameter("a", 10.5);
	EXPECT_EQ(10, param.toInt());
	param = ssf::Parameter("a", -10);
	EXPECT_EQ(-10, param.toInt());
	param = ssf::Parameter("a", -10.5);
	EXPECT_EQ(-10, param.toInt());

	int i = 10;
	param = ssf::Parameter("a", i);
	EXPECT_EQ(10, param.toInt());
	double d = 10.5;
	param = ssf::Parameter("a", d);
	EXPECT_EQ(10, param.toInt());

	param = ssf::Parameter("a", "10");
	EXPECT_EQ(10, param.toInt());
	param = ssf::Parameter("a", "-10");
	EXPECT_EQ(-10, param.toInt());

	param = ssf::Parameter("a", true);
	EXPECT_EQ(1, param.toInt());
	param = ssf::Parameter("a", false);
	EXPECT_EQ(0, param.toInt());

	param = ssf::Parameter("a", "true");
	EXPECT_EQ(1, param.toInt());
	param = ssf::Parameter("a", "false");
	EXPECT_EQ(0, param.toInt());

	param = ssf::Parameter("a", std::vector < int > {10, 20, 30});
	EXPECT_EQ(10, param.toInt());
	param = ssf::Parameter("a", std::vector < double > {10.1, 20.2, 30.3});
	EXPECT_EQ(10, param.toInt());
	param = ssf::Parameter("a", std::vector < std::string > {"10", "20", "30"});
	EXPECT_EQ(10, param.toInt());


	i = std::numeric_limits<int>::max();
	param = ssf::Parameter("a",i);
	EXPECT_EQ(std::numeric_limits<int>::max(), param.toInt());

	i = std::numeric_limits<int>::min();
	param = ssf::Parameter("a", i);
	EXPECT_EQ(std::numeric_limits<int>::min(), param.toInt());

	d = std::numeric_limits<double>::min();
	param = ssf::Parameter("a", d);
	EXPECT_EQ((int)std::numeric_limits<double>::min(), param.toInt());

}

TEST_F(TestParameter, toIntIrregular){
	
	double d = std::numeric_limits<double>::max();
	ssf::Parameter param = ssf::Parameter("a", d);
	EXPECT_ANY_THROW(param.toInt());

	param = ssf::Parameter("a", "nom_number");
	EXPECT_ANY_THROW(param.toInt());

	param = ssf::Parameter("a", ssf::FileHandle("file"));
	EXPECT_ANY_THROW(param.toInt());

	param = ssf::Parameter("a", ssf::DirectoryHandle("directory"));
	EXPECT_ANY_THROW(param.toInt());

}

TEST_F(TestParameter, toDoubleRegular){

	ssf::Parameter param("a", 10);
	EXPECT_EQ(10, param.toDouble());
	param = ssf::Parameter("a", 10.5);
	EXPECT_EQ(10.5, param.toDouble());
	param = ssf::Parameter("a", -10);
	EXPECT_EQ(-10, param.toDouble());
	param = ssf::Parameter("a", -10.5);
	EXPECT_EQ(-10.5, param.toDouble());

	int i = 10;
	param = ssf::Parameter("a", i);
	EXPECT_EQ(10, param.toDouble());
	double d = 10.5;
	param = ssf::Parameter("a", d);
	EXPECT_EQ(10.5, param.toDouble());

	param = ssf::Parameter("a", "10.55");
	EXPECT_EQ(10.55, param.toDouble());

	param = ssf::Parameter("a", true);
	EXPECT_EQ(1, param.toDouble());
	param = ssf::Parameter("a", false);
	EXPECT_EQ(0, param.toDouble());

	param = ssf::Parameter("a", "true");
	EXPECT_EQ(1, param.toDouble());
	param = ssf::Parameter("a", "false");
	EXPECT_EQ(0, param.toDouble());

	param = ssf::Parameter("a", std::vector < int > {10, 20, 30});
	EXPECT_EQ(10, param.toDouble());
	param = ssf::Parameter("a", std::vector < double > {10.1, 20.2, 30.3});
	EXPECT_EQ(10.1, param.toDouble());
	param = ssf::Parameter("a", std::vector < std::string > {"10.1", "20.2", "30.3"});
	EXPECT_EQ(10.1, param.toDouble());


	i = std::numeric_limits<int>::max();
	param = ssf::Parameter("a", i);
	EXPECT_EQ(std::numeric_limits<int>::max(), param.toDouble());

	i = std::numeric_limits<int>::min();
	param = ssf::Parameter("a", i);
	EXPECT_EQ(std::numeric_limits<int>::min(), param.toDouble());

	d = std::numeric_limits<float>::max();
	param = ssf::Parameter("a", d);
	EXPECT_EQ(std::numeric_limits<float>::max(), param.toDouble());

	double dtest = -312312312313141.1535635245245245;
	param = ssf::Parameter("a", dtest);
	EXPECT_EQ(-312312312313141.1535635245245245, param.toDouble());

}

TEST_F(TestParameter, toDoubleIrregular){

	ssf::Parameter param = ssf::Parameter("a", "nom_number");
	EXPECT_ANY_THROW(param.toDouble());

	param = ssf::Parameter("a", ssf::FileHandle("file"));
	EXPECT_ANY_THROW(param.toDouble());

	param = ssf::Parameter("a", ssf::DirectoryHandle("directory"));
	EXPECT_ANY_THROW(param.toDouble());

}

TEST_F(TestParameter, toBoolRegular){

	ssf::Parameter param("a", true);
	EXPECT_TRUE(param.toBool());
	param = ssf::Parameter("a", false);
	EXPECT_FALSE(param.toBool());

	param = ssf::Parameter("a", 10);
	EXPECT_TRUE(param.toBool());
	param = ssf::Parameter("a", -10);
	EXPECT_TRUE(param.toBool());
	param = ssf::Parameter("a", 10.1);
	EXPECT_TRUE(param.toBool());
	param = ssf::Parameter("a", -10.1);
	EXPECT_TRUE(param.toBool());

	param = ssf::Parameter("a", 0);
	EXPECT_FALSE(param.toBool());
	
	param = ssf::Parameter("a", "10");
	EXPECT_TRUE(param.toBool());
	param = ssf::Parameter("a", "-10");
	EXPECT_TRUE(param.toBool());
	param = ssf::Parameter("a", "0");
	EXPECT_FALSE(param.toBool());

	param = ssf::Parameter("a", "true");
	EXPECT_TRUE(param.toBool());
	param = ssf::Parameter("a", "false");
	EXPECT_FALSE(param.toBool());

	param = ssf::Parameter("a", std::vector < int > {10, 20, 30});
	EXPECT_TRUE(param.toBool());
	param = ssf::Parameter("a", std::vector < double > {10.1, 20.2, 30.3});
	EXPECT_TRUE(param.toBool());
	param = ssf::Parameter("a", std::vector < std::string > {"10", "20", "30"});
	EXPECT_TRUE(param.toBool());

}

TEST_F(TestParameter, toIntVectorRegular){

	ssf::Parameter param("a", 10);
	EXPECT_EQ(10, param.toIntVector()[0]);
	param = ssf::Parameter("a", 10.5);
	EXPECT_EQ(10, param.toIntVector()[0]);
	param = ssf::Parameter("a", -10);
	EXPECT_EQ(-10, param.toIntVector()[0]);
	param = ssf::Parameter("a", -10.5);
	EXPECT_EQ(-10, param.toIntVector()[0]);

	param = ssf::Parameter("a", "10");
	EXPECT_EQ(10, param.toIntVector()[0]);
	param = ssf::Parameter("a", "-10");
	EXPECT_EQ(-10, param.toIntVector()[0]);

	param = ssf::Parameter("a", true);
	EXPECT_EQ(1, param.toIntVector()[0]);
	param = ssf::Parameter("a", false);
	EXPECT_EQ(0, param.toIntVector()[0]);

	param = ssf::Parameter("a", "true");
	EXPECT_EQ(1, param.toIntVector()[0]);
	param = ssf::Parameter("a", "false");
	EXPECT_EQ(0, param.toIntVector()[0]);

	param = ssf::Parameter("a", std::vector < int > {10, 20, 30});
	EXPECT_EQ(10, param.toIntVector()[0]);
	EXPECT_EQ(20, param.toIntVector()[1]);
	EXPECT_EQ(30, param.toIntVector()[2]);
	
	param = ssf::Parameter("a", std::vector < double > {10.1, 20.2, 30.3});
	EXPECT_EQ(10, param.toIntVector()[0]);
	EXPECT_EQ(20, param.toIntVector()[1]);
	EXPECT_EQ(30, param.toIntVector()[2]);

	param = ssf::Parameter("a", std::vector < std::string > {"10", "20", "30"});
	EXPECT_EQ(10, param.toIntVector()[0]);
	EXPECT_EQ(20, param.toIntVector()[1]);
	EXPECT_EQ(30, param.toIntVector()[2]);

}

TEST_F(TestParameter, toIntVectorIrregular){
	
	ssf::Parameter param = ssf::Parameter("a", "nom_number");
	EXPECT_ANY_THROW(param.toIntVector());

	param = ssf::Parameter("a", std::vector < std::string > {"10", "20", "30"});

	param = ssf::Parameter("a", ssf::FileHandle("file"));
	EXPECT_ANY_THROW(param.toIntVector());

	param = ssf::Parameter("a", ssf::DirectoryHandle("directory"));
	EXPECT_ANY_THROW(param.toIntVector());

}

TEST_F(TestParameter, checkTypes){

	EXPECT_TRUE(ssf::Parameter::isInt("10"));
	EXPECT_TRUE(ssf::Parameter::isInt("-10"));
	EXPECT_TRUE(ssf::Parameter::isInt("0"));
	EXPECT_TRUE(ssf::Parameter::isInt("true"));
	EXPECT_TRUE(ssf::Parameter::isInt("false"));
	EXPECT_FALSE(ssf::Parameter::isInt("10 10"));
	EXPECT_FALSE(ssf::Parameter::isInt("word"));

	EXPECT_TRUE(ssf::Parameter::isDouble("10.1"));
	EXPECT_TRUE(ssf::Parameter::isDouble("-10.1"));
	EXPECT_TRUE(ssf::Parameter::isDouble("0"));
	EXPECT_TRUE(ssf::Parameter::isDouble("0.0"));
	EXPECT_TRUE(ssf::Parameter::isDouble("10"));
	EXPECT_TRUE(ssf::Parameter::isDouble("true"));
	EXPECT_TRUE(ssf::Parameter::isDouble("false"));
	EXPECT_FALSE(ssf::Parameter::isDouble("10.1 10"));
	EXPECT_FALSE(ssf::Parameter::isDouble("word"));

	EXPECT_TRUE(ssf::Parameter::isIntVector(std::vector < std::string > {"10", "20", "30"}));
	EXPECT_TRUE(ssf::Parameter::isIntVector(std::vector < std::string > {"10", "true", "30"}));
	EXPECT_FALSE(ssf::Parameter::isIntVector(std::vector < std::string > {"10", "word", "30"}));

	EXPECT_TRUE(ssf::Parameter::isDoubleVector(std::vector < std::string > {"10", "20", "30"}));
	EXPECT_TRUE(ssf::Parameter::isDoubleVector(std::vector < std::string > {"10.1", "20.2", "30.3"}));
	EXPECT_TRUE(ssf::Parameter::isDoubleVector(std::vector < std::string > {"10.1", "false", "30.3"}));
	EXPECT_FALSE(ssf::Parameter::isDoubleVector(std::vector < std::string > {"10.1", "word", "30.3"}));
	

}