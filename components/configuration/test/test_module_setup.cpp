#include <gtest/gtest.h>

#include <configuration/module_setup.hpp>

TEST(ModuleSetup, constructor) {
    EXPECT_NO_THROW(ssf::ModuleSetup test_module("moduleName", "moduleType"));
}

TEST(ModuleSetup, getName){
    ssf::ModuleSetup test_module("moduleName", "moduleType");
    EXPECT_EQ("moduleName", test_module.getName());
}

TEST(ModuleSetup, getType){
    ssf::ModuleSetup test_module("moduleName", "moduleType");
    EXPECT_EQ("moduleType", test_module.getType());
}

TEST(ModuleSetup, getID){
    ssf::ModuleSetup test_module("moduleName", "moduleType");
    EXPECT_TRUE (test_module.getID() != 0);
    
    ssf::ModuleSetup test_module2("moduleName", "moduleType");
    EXPECT_TRUE(test_module2.getID() != 0);
    
    ssf::ModuleSetup test_module3("moduleName", "moduleType");
    EXPECT_TRUE(test_module3.getID() != 0);
}

TEST(ModuleSetup, setGetParameterId){
    ssf::ModuleSetup test_module("moduleName", "moduleType");
    EXPECT_EQ("", test_module.getParametersID());
    
    test_module.setParametersID("parameterID");
    EXPECT_EQ("parameterID", test_module.getParametersID());
}