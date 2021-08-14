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

    virtual ~MemberFunctionHolderBase() = default;
};

template<typename Object, typename ...Args>
class MemberFunctionHolder : public MemberFunctionHolderBase<Args...>
{
    typedef typename std::function<void(Object&, Args...)> ObjectFunction;

public:
    void StoreObject(Object* inObj, ObjectFunction& inFunction)
    {
        m_Object = inObj;
        m_Function = inFunction;
    }

    virtual void Invoke(Args... args) override
    {
        if (m_Object)
        {
            m_Function(*m_Object, args...);
        }
    }

    virtual ~MemberFunctionHolder() = default;

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
            auto* member_function = new MemberFunctionHolder<Object, Args...>;
            member_function->StoreObject(obj, inFunction);

            delete m_MemberFunction;
            m_MemberFunction = member_function;

        }
        else
        {
            RemoveAll();
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

    void RemoveAll()
    {
        m_Internal = nullptr;
        delete m_MemberFunction;
        m_MemberFunction = nullptr;
    }

    Delegate() = default;

    virtual ~Delegate()
    {
        delete m_MemberFunction;
    }

protected:

private:
    Function m_Internal = nullptr;
    MemberFunctionHolderBase<Args...>* m_MemberFunction = nullptr;
};
