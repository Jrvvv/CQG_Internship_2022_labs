#pragma once
#include <iostream>

template <class T> class copy_ptr {
public:
	copy_ptr<T>(T* p = nullptr) : m_ptr(p) {
		std::cout << "ctor ptr " << std::endl;		// default constructor
	}

	~copy_ptr<T>() { 
		delete m_ptr;
		std::cout << "dtor ptr " << std::endl;		// default destructor
	}
	// COPY
	copy_ptr<T>(const copy_ptr<T>& p) { 				// copy contrs and assig
		m_ptr = new T;
		*m_ptr = *p.m_ptr;
		std::cout << "copy ctor ptr " << std::endl;
	}

	copy_ptr<T>& operator=(const copy_ptr<T>& p) {
		if (&p == this) {
			std::cout << "copy assig ptr " << std::endl;
			return *this;
		}
		delete m_ptr;
		m_ptr = new T;
		*m_ptr = *p.m_ptr;
		std::cout << "copy assig ptr " << std::endl;
		return *this;
	}

	// MOVE
	copy_ptr<T>(copy_ptr<T>&& p) noexcept : m_ptr(p.m_ptr) {	// move constr and assig
		p.m_ptr = nullptr; 
		std::cout << "move ctor ptr " << std::endl;
	}

	copy_ptr<T>& operator=(copy_ptr<T>&& p) noexcept {
		if (&p == this) {
			std::cout << "move assig ptr " << std::endl;
			return *this;
		}
		delete m_ptr;
		std::cout << "dtor ptr " << std::endl;
		m_ptr = p.m_ptr;
		p.m_ptr = nullptr;
		std::cout << "move assig ptr " << std::endl;
		return *this;
	}

	// GET, RESET, TO BOOL
	T* get() { 
		std::cout << "getter ptr " << std::endl;
		return m_ptr;
	}

	void reset(T* p = nullptr) {
		if (m_ptr != p) {
			delete m_ptr;
			std::cout << "dtor ptr " << std::endl;
			m_ptr = p;
		}
		std::cout << "reseter ptr " << std::endl;
	}

	bool toBool() const {
		std::cout << "bool oper ptr " << std::endl;
		return m_ptr == nullptr;
	}

	T& operator*() const { 
		std::cout << "* called " << std::endl;
		return *m_ptr; 

	}

	T* operator->() const {
		std::cout << "-> called " << std::endl;
		return m_ptr;
	}

	T& operator[](int a) {
		std::cout << "[" << a << "] called " << std::endl;
		return m_ptr[a];
	}

private:
	T* m_ptr;
};

template<typename T, typename... Args>
copy_ptr<T> make_copy(Args &&... args) {
	return copy_ptr<T>(new T(std::forward<Args>(args)...));
}
