//
// Created by kolya on 8/1/2021.
//
#pragma once

#include <any>
#include <functional>
#include <iostream>

template<typename ...Args>
class MemberFunctionHolderBase
{
public:
    virtual void Invoke(Args...) = 0;
};

template<typename Object, typename ...Args>
class MemberFunctionHolder : public MemberFunctionHolderBase<Args...>
{
    typedef typename std::function<void(Object&, Args...)> ObjectFunction;

public:
    void StoreObject(Object* inObj, ObjectFunction& inFunction)
    {

    }

    virtual void Invoke(Args... args) override
    {
        m_Function(m_Object, args...);
    }

private:
    Object* m_Object = nullptr;
    ObjectFunction m_Function;
};

template<typename ...Args>
class Delegate
{
    typedef typename std::function<void(Args...)> Function;

public:
    template<typename Object>
    void AddMemberFunction(Object* obj, std::function<void(Object&, Args...)> inFunction)
    {
        typedef typename std::function<void(Object&, Args...)> MemberFunction;
        if (obj)
        {
            auto member_function = new MemberFunctionHolder<Object, Args...>;
            member_function->StoreObject(obj, inFunction);
            m_MemberFunction = member_function;

        }
    }

    void Add(const Function& Func)
    {
        m_Internal = Func;
    }

    void Invoke(Args... args)
    {
        if (m_Internal)
        {
            m_Internal(args...);
        }
        else if (m_MemberFunction)
        {
            m_MemberFunction->Invoke(args...);
        }
    }

protected:

private:
    Function m_Internal;
    MemberFunctionHolderBase<Args...>* m_MemberFunction;
};

// TODO: add a lot of checks and tests