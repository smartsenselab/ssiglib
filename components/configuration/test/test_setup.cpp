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
    test.addModule("ModuleC", "TypeA");
    test.addModule("ModuleD", "TypeB");
    test.addModule("ModuleE", "TypeA");
    test.addModule("ModuleF", "TypeC");
    
    test.setStream("ModuleA", "any1", "ModuleB", "any2");
    test.setStream("ModuleA", "any3", "ModuleB", "any4");
    test.setStream("ModuleB", "any5", "ModuleC", "any6");
    test.setStream("ModuleB", "any7", "ModuleC", "any8");
    test.setStream("ModuleC", "any9", "ModuleD", "any10");
    test.setStream("ModuleC", "any11", "ModuleD", "any12");
    test.setStream("ModuleD", "any13", "ModuleF", "any14");
    test.setStream("ModuleD", "any15", "ModuleF", "any16");


    
    
    //test.writeToFile("test");
}

