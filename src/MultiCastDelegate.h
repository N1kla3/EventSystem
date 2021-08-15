//
// Created by Nicola on 15.08.2021.
//
#pragma once

#include "Delegate.h"
#include "DelegateHandle.h"
#include <map>

template<typename ...Args>
class MultiCastDelegate
{
public:
    template<typename Object>
    DelegateHandle AddMemberFunction(Object* obj, std::function<void(Object &, Args...)> inFunction)
    {

    }

    DelegateHandle AddFunction(std::function<void(Args...)> inFunction);

    void RemoveAll();

    void RemoveFunction(const DelegateHandle& inHandle);

    void Broadcast() const;

private:
    std::unordered_map<DelegateHandle, Delegate<Args...>> m_Delegates;
};
