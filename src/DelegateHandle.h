//
// Created by Nicola on 15.08.2021.
//
#pragma once

#include <cstdint>

template<typename ...Args>
class MultiCastDelegate;

class DelegateHandle
{
public:

    DelegateHandle& operator=(const DelegateHandle& rhs) = default;
    bool operator==(const DelegateHandle& rhs) const;
    bool operator!=(const DelegateHandle& rhs) const;
    bool operator<(const DelegateHandle& rhs) const;
    bool operator>(const DelegateHandle& rhs) const;
    bool operator<=(const DelegateHandle& rhs) const;
    bool operator>=(const DelegateHandle& rhs) const;

private:
    DelegateHandle();

    uint32_t m_Id;

    static uint16_t GenerateID(DelegateHandle* inHandle);

    template<typename ...Args>
    friend class MultiCastDelegate;
};

