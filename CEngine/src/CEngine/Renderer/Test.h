#pragma once
#include <iostream>
namespace CEngine {
	class Test {
	public:
		Test() {
			std::cout << "cc Test()" << std::endl;
		}
		~Test() {
			std::cout << "cc ~Test()" << std::endl;
		}
		inline void Print() {
			std::cout << "test" << std::endl;
		}
	};
}