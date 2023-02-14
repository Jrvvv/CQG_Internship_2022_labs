#include <iostream>
#include <cassert>
#include <string>
#include <algorithm>
#include "TokenCounter.h"

std::string InputStr() {
    std::string str;
    std::cin >> str;
    return str;
}   

int main() {
    std::cout << "input string:" << std::endl;
    std::string input_str = InputStr();

    std::cout << "input string to find:" << std::endl;
    std::string find_str = InputStr();
    
    TokenCounter Cntr = std::for_each(input_str.begin(), input_str.end(), TokenCounter(find_str));
    
    std::cout << "Non-crossing occurrences: " << Cntr.GetTokenCount() << std::endl;

    return 0;
}
