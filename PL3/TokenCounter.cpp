#include "TokenCounter.h"

TokenCounter::TokenCounter(const std::string& str) {
	m_find_str = str;
	m_i_str = m_find_str.begin();
}

void TokenCounter::operator()(char i_str) {
	if (*m_i_str == i_str) {
		if (m_i_str == m_find_str.end() - 1) {
			m_tokens++;
			m_i_str = m_find_str.begin();
		} else {
			m_i_str++;
		}
	} else {
		m_i_str = m_find_str.begin();
	}
}

size_t TokenCounter::GetTokenCount() const {
	return m_tokens;
}