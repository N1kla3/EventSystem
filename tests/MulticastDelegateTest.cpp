//
// Created by Nicola on 15.08.2021.
//
#include "gtest/gtest.h"
#include "MultiCastDelegate.h"

namespace
{
    bool success = false;
}

class TestFunctionss
{
public:
    void function(int a)
    {
        success = true;
    }
};

void Functionn(int a, const std::string& b, TestFunctionss* c)
{
    success = true;
}

class TestClasss
{
public:
    mutable bool success = false;

    void Function(int a, const std::string& b, TestFunctionss* c)
    {
        success = true;
    }

    void FunctionConst(int a, const std::string& b, TestFunctionss* c) const
    {
        success = true;
    }

    void FunctionMovable(int a, const std::string& b, TestFunctionss* c) &&
    {
        success = true;
    }
};

TEST(Multicast, AddDelegateTest)
{
    MultiCastDelegate<int, const std::string&, TestFunctionss*> delegate;
    delegate.AddFunction(Functionn);
    ASSERT_NO_THROW(delegate.Broadcast(2, "dd", new TestFunctionss));
}