#include <gtest/gtest.h>

#include <configuration/stream_setup.hpp>

TEST(StreamSetup, constructor){
    EXPECT_NO_THROW(ssf::StreamSetup stream_test("moduleA", "outputA", "moduleB", "outputB"));
}

TEST(StreamSetup, getModuleIDProvider){
    ssf::StreamSetup stream_test("moduleA", "outputA", "moduleB", "outputB");
    EXPECT_STREQ("moduleA", stream_test.getModuleIDProvider().c_str());
}

TEST(StreamSetup, getModuleIDReceiver){
    ssf::StreamSetup stream_test("moduleA", "outputA", "moduleB", "outputB");
    EXPECT_STREQ("moduleB", stream_test.getModuleIDReceiver().c_str());
}

TEST(StreamSetup, getOutputProvider){
    ssf::StreamSetup stream_test("moduleA", "outputA", "moduleB", "outputB");
    EXPECT_STREQ("outputA", stream_test.getOutputProvider().c_str());
}

TEST(StreamSetup, getInputReceiver){
    ssf::StreamSetup stream_test("moduleA", "outputA", "moduleB", "outputB");
    EXPECT_STREQ("outputB", stream_test.getInputReceiver().c_str());
    
}