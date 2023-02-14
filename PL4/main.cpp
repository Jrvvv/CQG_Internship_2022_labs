#include <iostream>
#include "copy_ptr.h"
#include "CTrace.h"

int main() {
	int n;
	// ________________CTOR______->________*_______TEST_____________
	std::cout << "Expected:\nCTrace ctor\nctor ptr\n-> called\n1\n"
		"* called\n1\ndtor ptr\n\n" << std::endl;
	{
	std::cout << "Got:" << std::endl;
	copy_ptr<CTrace> sp(new CTrace(1)); 
	std::cout << sp->m_a << std::endl;
		CTrace& traceObj = *sp;

		std::cout << traceObj.m_a << std::endl;
	}
	std::cout << std::endl;

	// _______________RESET____BOOL______TEST_____________
	std::cout << "Enter \"0\" to test reset and bool" << std::endl;
	std::cin >> n;
	std::cout << "Expected:\nCTrace ctor\nctor ptr\nCTrace ctor\ndtor ptr\n"
		"reseter ptr\n-> called\n2\ndtor ptr\nreseter ptr\nbool oper ptr\n"
		"nothing\ndtor ptr\n\n" << std::endl;
	{
		std::cout << "Got:" << std::endl;
		copy_ptr<CTrace> sp(new CTrace(1));
		sp.reset(new CTrace(2));
		std::cout << sp->m_a << std::endl;
		sp.reset();
		if (sp.toBool()) {
			std::cout << "nothing" << std::endl;
		}
		else {
			std::cout << "nothing to get with ->" << std::endl;
		}
	}
	std::cout << std::endl;
	

	// _______________MOVE______TEST_____________
	std::cout << "Enter \"0\" to test move assig and ctor" << std::endl;
	std::cin >> n;
	std::cout << "Expected:\nCTrace ctor\nctor ptr\nctor ptr\n"
		"dtor ptr\nmove assig ptr\nmove ctor ptr\ndtor ptr\ndtor ptr\n"
		"dtor ptr\n\n" << std::endl;
	{
		std::cout << "Got:" << std::endl;
		copy_ptr<CTrace> sp1(new CTrace(1));
		copy_ptr<CTrace> sp2;
		
		sp2 = std::move(sp1);

		copy_ptr<CTrace> sp3(std::move(sp2));
	}
	std::cout << std::endl;


	// _______________COPY______TEST_____________
	std::cout << "Enter \"0\" to test copy assig and ctor" << std::endl;
	std::cin >> n;
	std::cout << "Expected:\nCTrace ctor\nctor ptr\nctor ptr\n"
		"CTrace ctor\nCTrace cpy assig\ncopy assig ptr\nCTrace ctor\n"
		"CTrace cpy assig\ncopy ctor ptr\ndtor ptr\ndtor ptr\n"
		"dtor ptr\n\n" << std::endl;
	{
		std::cout << "Got:" << std::endl;
		copy_ptr<CTrace> sp1(new CTrace(1));
		copy_ptr<CTrace> sp2;

		sp2 = sp1;

		copy_ptr<CTrace> sp3(sp2);
	}
	std::cout << std::endl;

	// _______________ARR______GETTER________TEST_____________
	std::cout << "Enter \"0\" to test arr, get and [] oper" << std::endl;
	std::cin >> n;
	std::cout << "Expected:\nCTrace ctor\nCTrace ctor\nCTrace ctor\n"
		"ctor ptr\n[0] called\n[2] called\n[2] called\n3\ngetter ptr\n1\n"
		"dtor ptr\n\n" << std::endl;
	{
		std::cout << "Got:" << std::endl;

		CTrace* arr = new CTrace[3];
		copy_ptr<CTrace> sp(arr);

		sp[0].m_a = 1;
		sp[2].m_a = 3;

		std::cout << sp[2].m_a << std::endl;
		std::cout << sp.get()->m_a << std::endl;

	}
	std::cout << std::endl;

	// _______________MAKE______COPY________TEST_____________
	std::cout << "Enter \"0\" to test make_copy" << std::endl;
	std::cin >> n;
	std::cout << "Expected:\nCTrace ctor\nctor ptr\n-> called\n"
		"3\ndtor ptr\n\n" << std::endl;
	{
		std::cout << "Got:" << std::endl;

		copy_ptr<CTrace> sp1 = make_copy<CTrace>(3);
		
		std::cout << sp1->m_a << std::endl;

	}
	std::cout << std::endl;

	return 0;
}