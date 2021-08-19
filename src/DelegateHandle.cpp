//
// Created by Nicola on 15.08.2021.
//

#include "DelegateHandle.h"

bool DelegateHandle::operator==(const DelegateHandle& rhs) const { return m_Id == rhs.m_Id; }
bool DelegateHandle::operator!=(const DelegateHandle& rhs) const { return !(rhs == *this); }
bool DelegateHandle::operator<(const DelegateHandle& rhs) const { return m_Id < rhs.m_Id; }
bool DelegateHandle::operator>(const DelegateHandle& rhs) const { return rhs < *this; }
bool DelegateHandle::operator<=(const DelegateHandle& rhs) const { return !(rhs < *this); }
bool DelegateHandle::operator>=(const DelegateHandle& rhs) const { return !(*this < rhs); }

DelegateHandle::DelegateHandle()
{
    m_Id = GenerateID();
}

uint64_t DelegateHandle::GenerateID()
{
    return STATIC_ID++;
}
