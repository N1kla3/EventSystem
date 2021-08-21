//
// Created by nicola on 10/02/2021.
//
#include "gtest/gtest.h"
#include "Delegate.h"

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

TEST(Delegate, FunctionOne)
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

TEST(Delegate, MemberFunctionOne)
{
    auto* test = new TestFunctions;
    auto a = std::make_shared<TestClass>();
    Delegate<int, const std::string&, TestFunctions*> delegate;
    delegate.AddMemberFunction<TestClass>(a, &TestClass::Function);
    ASSERT_NO_THROW(delegate.Invoke(1, "sdf", test));
    delegate.RemoveAll();
    ASSERT_NO_THROW(delegate.Invoke(1, "sdf", test));
    ASSERT_TRUE(a->success);
}

TEST(Delegate, MemberFunctionConstOne)
{
    auto* test = new TestFunctions;
    auto a = std::make_shared<TestClass>();
    Delegate<int, const std::string&, TestFunctions*> delegate;
    delegate.AddMemberFunction<const TestClass>(a, &TestClass::FunctionConst);
    ASSERT_NO_THROW(delegate.Invoke(1, "sdf", test));
    delegate.RemoveAll();
    ASSERT_NO_THROW(delegate.Invoke(1, "sdf", test));
    ASSERT_TRUE(a->success);
}

TEST(Delegate, MemberFunctionCallEmpty)
{
    auto* test = new TestFunctions;
    auto a = std::make_shared<TestClass>();
    Delegate<int, const std::string&, TestFunctions*> delegate;
    delegate.AddMemberFunction<TestClass>(a, &TestClass::Function);
    ASSERT_NO_THROW(delegate.Invoke(1, "sdf", test));
    delegate.RemoveAll();
    ASSERT_TRUE(a->success);
    a = nullptr;
    delegate.AddMemberFunction<TestClass>(a, &TestClass::Function);
    ASSERT_NO_THROW(delegate.Invoke(1, "sdf", test));
}
