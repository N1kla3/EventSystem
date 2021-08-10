//
// Created by nicola on 10/02/2021.
//
#include "gtest/gtest.h"
#include "../src/Delegate.h"

namespace
{
    bool success = false;
}

class TestFunctions
{
public:
    void function(int a)
    {
        success = true;
    }
};

void Function(int a, const std::string& b, TestFunctions* c)
{
    success = true;
}

TEST(suite, test)
{
    ASSERT_EQ(1, 1);
}

TEST(Delegate, one)
{
    auto* test = new TestFunctions;
    success = false;
    Delegate<int, const std::string&, TestFunctions*> delegate;
    delegate.Add(Function);
    ASSERT_NO_THROW(delegate.Invoke(1, "dd", test));
    ASSERT_TRUE(success);
    success = false;
    delegate.Add([](int a, const std::string& b, TestFunctions* c){
        success = true;
    });
    ASSERT_NO_THROW(delegate.Invoke(1, "sdf", test));
    ASSERT_TRUE(success);
    delete test;
}