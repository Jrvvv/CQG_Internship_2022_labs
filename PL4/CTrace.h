#pragma once
#include <iostream>

class CTrace {
public:
    CTrace(int i_a = 0);

    CTrace(const CTrace& obj);
    CTrace& operator=(const CTrace& obj);

    CTrace(CTrace&& obj) noexcept;
    CTrace& operator=(CTrace&& obj) noexcept;

    ~CTrace() = default;

    int m_a;
};
