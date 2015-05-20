#include <gtest/gtest.h>

#include <configuration/stream.hpp>

TEST(Stream, constructor){
    EXPECT_NO_THROW(ssf::Stream stream_test("moduleA", "outputA", "moduleB", "outputB"));
}

TEST(Stream, getModuleIDProvider){
    ssf::Stream stream_test("moduleA", "outputA", "moduleB", "outputB");
    EXPECT_STREQ("moduleA", stream_test.getModuleIDProvider().c_str());
}

TEST(Stream, getModuleIDReceiver){
    ssf::Stream stream_test("moduleA", "outputA", "moduleB", "outputB");
    EXPECT_STREQ("moduleB", stream_test.getModuleIDReceiver().c_str());
}

TEST(Stream, getOutputProvider){
    ssf::Stream stream_test("moduleA", "outputA", "moduleB", "outputB");
    EXPECT_STREQ("outputA", stream_test.getOutputProvider().c_str());
}

TEST(Stream, getInputReceiver){
    ssf::Stream stream_test("moduleA", "outputA", "moduleB", "outputB");
    EXPECT_STREQ("outputB", stream_test.getInputReceiver().c_str());
    
}