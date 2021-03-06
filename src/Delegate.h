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
    void StoreObject(const std::shared_ptr<Object>& inObj, ObjectFunction& inFunction)
    {
        if (inObj && inFunction)
        {
            m_Object = inObj;
            m_Function = inFunction;
        }
    }

    virtual void Invoke(Args... args) override
    {
        if (!m_Object.expired())
        {
            m_Function(*m_Object.lock(), args...);
        }
    }

    virtual ~MemberFunctionHolder() = default;

private:
    std::weak_ptr<Object> m_Object;
    ObjectFunction m_Function;
};

template<typename ...Args>
class Delegate
{
    typedef typename std::function<void(Args...)> Function;

public:
    template<typename Object>
    void AddMemberFunction(const std::shared_ptr<Object>& obj, std::function<void(Object&, Args...)> inFunction)
    {
        typedef typename std::function<void(Object&, Args...)> MemberFunction;
        if (obj)
        {
            auto* member_function = new MemberFunctionHolder<Object, Args...>;
            member_function->StoreObject(obj, inFunction);

            m_MemberFunction.reset(member_function);
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

    void Invoke(Args... args) const
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
        m_MemberFunction.release();
    }

    Delegate() = default;
    Delegate(Delegate&& delegate) noexcept = default;
    Delegate(const Delegate& delegate) = delete;

    virtual ~Delegate()
    = default;

protected:

private:
    Function m_Internal = nullptr;
    std::unique_ptr<MemberFunctionHolderBase<Args...>> m_MemberFunction;
};
