#include "CTrace.h"

CTrace::CTrace(int i_a) : m_a(i_a) {
    std::cout << "CTrace ctor" << std::endl;
}

CTrace::CTrace(const CTrace& obj) { 
    m_a = obj.m_a; 
    std::cout << "CTrace cpy ctor" << std::endl;
}

CTrace& CTrace::operator=(const CTrace& obj) {
    if (m_a == obj.m_a) {
        std::cout << "CTrace cpy assig" << std::endl;
        return *this;
    }
    m_a = obj.m_a;
    std::cout << "CTrace cpy assig" << std::endl;
    return *this;
}

CTrace::CTrace(CTrace&& obj) noexcept {
    m_a = obj.m_a;
    obj.m_a = 0;
    std::cout << "CTrace move ctor" << std::endl;
}

CTrace& CTrace::operator=(CTrace&& obj) noexcept {
    if (m_a == obj.m_a) {
        std::cout << "CTrace move assig" << std::endl;
        return *this;
    }
    m_a = obj.m_a;
    obj.m_a = 0;
    std::cout << "CTrace move assig" << std::endl;
    return *this;
}
