#pragma once

#include <string>
#include <iostream>

class TokenCounter {
public:
    TokenCounter() = default;
    TokenCounter(const std::string& i_substr);
    void operator()(char i_str);
    size_t GetTokenCount() const;
private:
    std::string m_find_str;
    size_t m_tokens = 0;
    std::string::iterator m_i_str = m_find_str.begin();
};