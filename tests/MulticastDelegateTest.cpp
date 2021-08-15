//
// Created by Nicola on 15.08.2021.
//
#include "gtest/gtest.h"
#include "MultiCastDelegate.h"

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

class TestClass
{
public:
    mutable bool success = false;

    void Function(int a, const std::string& b, TestFunctions* c)
    {
        success = true;
    }

    void FunctionConst(int a, const std::string& b, TestFunctions* c) const
    {
        success = true;
    }

    void FunctionMovable(int a, const std::string& b, TestFunctions* c) &&
    {
        success = true;
    }
};

TEST(Multicast, AddDelegateTest)
{
    MultiCastDelegate<int, const std::string&, TestFunctions*> delegate;
    delegate.AddFunction(Function);
}