#include <gtest/gtest.h>
#include <configuration/setup.hpp>
#include <configuration/module_setup.hpp>

TEST(Setup, constructor) {
    EXPECT_NO_THROW(ssf::Setup test_configuration);
}

TEST(Setup, addModule){
    ssf::Setup test;
    test.addModule("moduleA", "typeA");
    EXPECT_ANY_THROW(test.addModule("moduleA", "type1"));
    EXPECT_NO_THROW(test.addModule("moduleB", "type1"));
    EXPECT_ANY_THROW(test.addModule("moduleA", "typeB"));
}

TEST(Setup, setStream){
    ssf::Setup test;
    test.addModule("ModuleA", "typeA");
    test.addModule("ModuleB", "typeA");

    EXPECT_NO_THROW(test.setStream("moduleA", "output1", "moduleB", "input1"));
    EXPECT_NO_THROW(test.setStream("moduleA", "output2", "moduleB", "input2"));
    EXPECT_NO_THROW(test.setStream("moduleA", "output3", "moduleB", "input3"));
    EXPECT_ANY_THROW(test.setStream("moduleA", "output1", "moduleB", "input1"));
    EXPECT_ANY_THROW(test.setStream("moduleA", "output2", "moduleB", "input2"));
    EXPECT_ANY_THROW(test.setStream("moduleA", "output3", "moduleB", "input3"));
}

TEST(Setup, writeToFile){
    ssf::Setup test;
    test.addModule("ModuleA", "TypeA");
    test.addModule("ModuleB", "TypeB");
    
    test.writeToFile("test");
}

