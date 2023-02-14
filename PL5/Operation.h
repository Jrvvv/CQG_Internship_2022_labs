#pragma once
#include <string>
#include <vector>
#include <functional>
#include <exception>

template <class F>
class Operation
{
public:
	Operation(const std::string& name = "",
			  const F& func = nullptr,
			  int argsCounter = 0) : m_operationName(name),
									 m_function(func),
									 m_isBinary(argsCounter) {}

	const F& getFunction() {
		return m_function;
	}

	const std::string& getName() {
		return m_operationName;
	}

	const int isBinary() {
		return m_isBinary;
	}

private:
	F m_function;
	std::string m_operationName;
	int m_isBinary;
};


