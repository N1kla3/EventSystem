//
// Created by Nicola on 15.08.2021.
//
#include "gtest/gtest.h"
#include "MultiCastDelegate.h"

namespace
{
    bool success = false;

    int count = 0;
}

class TestFunctionss
{
public:
    void function(int a)
    {
        count++;
    }
};

void Functionn(int a, const std::string& b, TestFunctionss* c)
{
    count++;
}

class TestClasss
{
public:
    mutable bool success = false;

    void Function(int a, const std::string& b, TestFunctionss* c)
    {
        count++;
    }

    void FunctionConst(int a, const std::string& b, TestFunctionss* c) const
    {
        count++;
    }

    void FunctionMovable(int a, const std::string& b, TestFunctionss* c) &&
    {
        count++;
    }
};

TEST(Multicast, AddDelegateTest)
{
    auto a = std::make_shared<TestClasss>();
    MultiCastDelegate<int, const std::string&, TestFunctionss*> delegate;
    delegate.AddFunction(Functionn);
    delegate.AddMemberFunction<TestClasss>(a, &TestClasss::Function);
    delegate.AddFunction(Functionn);
    delegate.AddMemberFunction<TestClasss>(a, &TestClasss::Function);
    ASSERT_NO_THROW(delegate.Broadcast(2, "dd", new TestFunctionss));
    ASSERT_EQ(count, 4);
    count = 0;
}

TEST(Multicast, RemoveAll)
{
    auto a = std::make_shared<TestClasss>();
    MultiCastDelegate<int, const std::string&, TestFunctionss*> delegate;
    delegate.AddFunction(Functionn);
    delegate.AddMemberFunction<TestClasss>(a, &TestClasss::Function);
    delegate.AddFunction(Functionn);
    delegate.AddMemberFunction<TestClasss>(a, &TestClasss::Function);

    ASSERT_NO_THROW(delegate.Broadcast(2, "dd", new TestFunctionss));
    delegate.RemoveAll();
    ::count = 0;
    ASSERT_NO_THROW(delegate.Broadcast(2, "dd", new TestFunctionss));
    ASSERT_EQ(::count, 0);
    count = 0;
}

TEST(Multicast, RemoveOne)
{
    auto a = std::make_shared<TestClasss>();
    MultiCastDelegate<int, const std::string&, TestFunctionss*> delegate;
    delegate.AddFunction(Functionn);
    DelegateHandle handle = delegate.AddMemberFunction<TestClasss>(a, &TestClasss::Function);
    delegate.AddFunction(Functionn);
    delegate.AddMemberFunction<TestClasss>(a, &TestClasss::Function);
    ASSERT_TRUE(delegate.RemoveFunction(handle));

    ASSERT_NO_THROW(delegate.Broadcast(2, "dd", new TestFunctionss));
    ASSERT_EQ(::count, 3);
    count = 0;
}

TEST(Multicast, moveConstructible)
{
    auto a = std::make_shared<TestClasss>();
    MultiCastDelegate<int, const std::string&, TestFunctionss*> delegate;
    delegate.AddFunction(Functionn);
    DelegateHandle handle = delegate.AddMemberFunction<TestClasss>(a, &TestClasss::Function);
    delegate.AddFunction(Functionn);
    delegate.AddMemberFunction<TestClasss>(a, &TestClasss::Function);
    ASSERT_TRUE(delegate.RemoveFunction(handle));

    MultiCastDelegate<int, const std::string&, TestFunctionss*> _delegate(std::move(delegate));

    ASSERT_NO_THROW(_delegate.Broadcast(2, "dd", new TestFunctionss));
    ASSERT_EQ(::count, 3);
    count = 0;
}
