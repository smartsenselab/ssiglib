#include <gtest/gtest.h>

#include <configuration/module.hpp>

TEST(Module, constructor) {
    EXPECT_NO_THROW(ssf::Module test_module("moduleName", "moduleType"));
}

TEST(Module, getName){
    ssf::Module test_module("moduleName", "moduleType");
    EXPECT_EQ("moduleName", test_module.getName());
}

TEST(Module, getType){
    ssf::Module test_module("moduleName", "moduleType");
    EXPECT_EQ("moduleType", test_module.getType());
}

TEST(Module, getID){
    ssf::Module test_module("moduleName", "moduleType");
    EXPECT_TRUE (test_module.getID());
    
    ssf::Module test_module2("moduleName", "moduleType");
    EXPECT_TRUE(test_module2.getID());
    
    ssf::Module test_module3("moduleName", "moduleType");
    EXPECT_TRUE(test_module3.getID());
}

TEST(Module, addSetParameter){
    ssf::Module test_module("moduleName", "moduleType");
    EXPECT_NO_THROW(test_module.addParameter("integer", 5));
    EXPECT_ANY_THROW(test_module.addParameter("integer", 5));	
}