#include <gtest/gtest.h>

#include <configuration/configuration.hpp>
#include <configuration/module.hpp>

TEST(Configuration, constructor) {
    EXPECT_NO_THROW(ssf::Configuration test_configuration);
}

TEST(Configuration, addModule){
    ssf::Configuration test;
    test.addModule("moduleA", "typeA");
    EXPECT_ANY_THROW(test.addModule("moduleA", "type1"));
    EXPECT_NO_THROW(test.addModule("moduleB", "type1"));
    EXPECT_ANY_THROW(test.addModule("moduleA", "typeB"));
}


TEST(Configuration, setStream){
    ssf::Configuration test;
    test.addModule("ModuleA", "typeA");
    test.addModule("ModuleB", "typeA");
    
    EXPECT_NO_THROW(test.setStream("moduleA", "output1", "moduleB", "input1"));
    EXPECT_NO_THROW(test.setStream("moduleA", "output2", "moduleB", "input2"));
    EXPECT_NO_THROW(test.setStream("moduleA", "output3", "moduleB", "input3"));
    EXPECT_ANY_THROW(test.setStream("moduleA", "output1", "moduleB", "input1"));
    EXPECT_ANY_THROW(test.setStream("moduleA", "output2", "moduleB", "input2"));
    EXPECT_ANY_THROW(test.setStream("moduleA", "output3", "moduleB", "input3"));
    
}

TEST(Configuration, setParameter){
    ssf::Configuration test;
    test.addModule("ModuleA", "typeA");
    
	EXPECT_NO_THROW(test.getModule("ModuleA").addParameter("param1", 1));
	EXPECT_NO_THROW(test.getModule("ModuleA").addParameter("param2", 2));
	EXPECT_NO_THROW(test.getModule("ModuleA").addParameter("param3", 3));
	EXPECT_NO_THROW(test.getModule("ModuleA").addParameter("param4", 4));
	EXPECT_NO_THROW(test.getModule("ModuleA").addParameter("param5", 5));
    
}
