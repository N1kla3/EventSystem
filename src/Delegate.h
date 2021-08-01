//
// Created by kolya on 8/1/2021.
//
#pragma once

#include<functional>

template<typename ...Args>
class Delegate
{
    typedef std::function<void(Args...)> Function;

public:
    template<typename Object>
    void Add(Object* Obj, std::function<void(const Object&, Args...)> function)
    {

    }

    void Add(const Function& Func)
    {
        m_Internal = Func;
    }

    void Invoke(Args... args)
    {
        std::invoke(m_Internal, args...);
    }
protected:

private:
   Function m_Internal;
};

