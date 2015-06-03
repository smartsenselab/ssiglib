#include <gtest/gtest.h>
#include <configuration/setup_exception.hpp>

TEST(SetupException, constructor) {
    EXPECT_NO_THROW(ssf::SetupException test_exception("moduleName", "error"));
}

TEST(SetupException, getModuleName){
    ssf::SetupException test_exception("moduleName", "error");
    EXPECT_EQ("moduleName", test_exception.getModuleName());

}