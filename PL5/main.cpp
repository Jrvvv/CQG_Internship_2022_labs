#include <iostream>
#include <string>

#include "Operation.h"
#include "ReversePolishSolver.h"


class FooBinarMinus {
public:
    int operator()(int x, int y) { return x - y; }
};

int divide(int x, int y) {
    if (y == 0) throw std::logic_error("Division by null");
    return x / y;
}

int main() {
    ReversePolishSolver solver;

    // ___________________________________TEST_1_LAMBDA______________________OK
    // ___________________________adding_square______________________
    std::cout << "press any key to try solver.RegisterOperator<1>"
                 "(\"square\", [](int x) {return x * x; });" << std::endl;
    try {
        solver.RegisterOperator<1>("square", [](int x) {return x * x; });
        std::cout << "OK" << std::endl;
        std::cout << std::endl;
    }
    catch (std::exception& ex) {
        std::cout << ex.what() << std::endl;
        std::cout << std::endl;
    }

    // ___________________________________TEST_2_FUNCTOR______________________OK
    // ___________________________adding_minus______________________
    std::cout << "press any key to try solver.RegisterOperator<2>"
                 "(\"-\", FooBinarMinus());" << std::endl;
    try {
        solver.RegisterOperator<2>("-", FooBinarMinus());
        std::cout << "OK" << std::endl;
        std::cout << std::endl;
    }
    catch (std::exception& ex) {
        std::cout << ex.what() << std::endl;
        std::cout << std::endl;
    }

    // ___________________________________TEST_3_BINARY_________________________OK
    // ___________________________adding_plus_____________________
    std::cout << "press any key to try solver.RegisterOperator<2>"
                 "(\"+\", std::plus<>());" << std::endl;
    try {
        solver.RegisterOperator<2>("+", std::plus<>());
        std::cout << "OK" << std::endl;
        std::cout << std::endl;
    }
    catch (std::exception& ex) {
        std::cout << ex.what() << std::endl;
        std::cout << std::endl;
    }

    // ___________________________________TEST_4_BIND_________________________OK
    // ___________________________adding_+ten_____________________
    std::cout << "press any key to try solver.RegisterOperator<1>"
                 "(\" + ten\", std::bind(std::plus<>(), std::placeholders::_1, 10));" << std::endl;
    try {
        solver.RegisterOperator<1>("+ten", std::bind(std::plus<>(), std::placeholders::_1, 10));
        std::cout << "OK" << std::endl;
        std::cout << std::endl;
    }
    catch (std::exception& ex) {
        std::cout << ex.what() << std::endl;
        std::cout << std::endl;
    }

    // ___________________________________TEST_5_FUNCTION_________________________OK
    // ___________________________adding_division_____________________
    std::cout << "press any key to try solver.RegisterOperator<1>(\" / \", divide);" << std::endl;
    try {
        solver.RegisterOperator<2>("/", divide);
        std::cout << "OK" << std::endl;
        std::cout << std::endl;
    }
    catch (std::exception& ex) {
        std::cout << ex.what() << std::endl;
        std::cout << std::endl;
    }


    // ___________________________________TEST_6__________________________EXCEPTION
    std::cout << "press any key to try solver.RegisterOperator<3>"
                 "(\")\", FooBinarMinus());" << std::endl;
    try {
        solver.RegisterOperator<3>(")", FooBinarMinus());
        std::cout << "OK" << std::endl;
        std::cout << std::endl;
    }
    catch (std::exception& ex) {
        std::cout << ex.what() << std::endl;
        std::cout << std::endl;
    }

    // ___________________________________TEST_7__________________________EXCEPTION
    std::cout << "press any key to try solver.RegisterOperator<3>"
                 "(\"tripple_mult\", [](int x, int y, int z) {return x * y * z; });"<< std::endl;
    try {
        solver.RegisterOperator<3>("tripple_mult", [](int x, int y, int z) {return x * y * z; });
        std::cout << "OK" << std::endl;
        std::cout << std::endl;
    }
    catch (std::exception& ex) {
        std::cout << ex.what() << std::endl;
        std::cout << std::endl;
    }

    // ___________________________________TEST_8__________________________EXCEPTION
    std::cout << "press any key to try solver.RegisterOperator<2>"
                 "(\"-\", FooBinarMinus());" << std::endl;
    try {
        solver.RegisterOperator<2>("-", FooBinarMinus());
        std::cout << "OK" << std::endl;
        std::cout << std::endl;
    }
    catch (std::exception& ex) {
        std::cout << ex.what() << std::endl;
        std::cout << std::endl;
    }

    // ___________________________________TEST_9__________________________EXCEPTION
    std::cout << "press any key to try solver.RegisterOperator<2>"
        "(\"2\", FooBinarMinus());" << std::endl;
    try {
        solver.RegisterOperator<2>("2", FooBinarMinus());
        std::cout << "OK" << std::endl;
        std::cout << std::endl;
    }
    catch (std::exception& ex) {
        std::cout << ex.what() << std::endl;
        std::cout << std::endl;
    }

    // ___________________________________TEST_10__________________________EXCEPTION
    std::cout << "press any key to try solver.RegisterOperator<2>"
        "(\"3.2\", FooBinarMinus());" << std::endl;
    try {
        solver.RegisterOperator<2>("3.2", FooBinarMinus());
        std::cout << "OK" << std::endl;
        std::cout << std::endl;
    }
    catch (std::exception& ex) {
        std::cout << ex.what() << std::endl;
        std::cout << std::endl;
    }
    
    // ___________________________________TEST_11__________________________OK
    // ___________________________adding_double____________________________
    std::cout << "press any key to try solver.RegisterOperator<1>"
        "(\"double\", [](int x) { return x * 2; });" << std::endl;
    try {
        solver.RegisterOperator<1>("double", [](int x) { return x * 2; });
        std::cout << "OK" << std::endl;
        std::cout << std::endl;
    }
    catch (std::exception& ex) {
        std::cout << ex.what() << std::endl;
        std::cout << std::endl;
    }


   
    // ------------------------------------------------------------------------
    // ---------------------------TESTING SOLVE--------------------------------
    // ------------------------------------------------------------------------

    // ___________________________________TEST_12__________________________EXCEPTION
    std::cout << "solver.Solve(\"square 5\")" << std::endl;
    try {
        std::cout << solver.Solve("square 5") << std::endl;
        std::cout << "OK" << std::endl;
        std::cout << std::endl;
    }
    catch (std::exception& ex) {
        std::cout << ex.what() << std::endl;
        std::cout << std::endl;

    }

    // ___________________________________TEST_13__________________________OK
    // ___________________________________5^2______________________________
    std::cout << "solver.Solve(\"5 square\")" << std::endl;
    try {
        std::cout << solver.Solve("5 square") << std::endl;
        std::cout << "OK" << std::endl;
        std::cout << std::endl;
    }
    catch (std::exception& ex) {
        std::cout << ex.what() << std::endl;
        std::cout << std::endl;
    }

    // ___________________________________TEST_14__________________________OK
    // ___________________________________2*2+3+4=11_______________________
    std::cout << "solver.Solve(\"2 double 3 4 + +\")" << std::endl;
    try {
        std::cout << solver.Solve("2 double 3 4 + +") << std::endl;
        std::cout << "OK" << std::endl;
        std::cout << std::endl;
    }
    catch (std::exception& ex) {
        std::cout << ex.what() << std::endl;
        std::cout << std::endl;
    }

    // ___________________________________TEST_15__________________________OK
    // ___________________________________2*2-(3+4)=3______________________
    std::cout << "solver.Solve(\"2 double 3 4 + -\")" << std::endl;
    try {
        std::cout << solver.Solve("2 double 3 4 + -") << std::endl;
        std::cout << "OK" << std::endl;
        std::cout << std::endl;
    }
    catch (std::exception& ex) {
        std::cout << ex.what() << std::endl;
        std::cout << std::endl;
    }

    // ___________________________________TEST_16__________________________OK
    // ___________________________________(3*3+67)/38=2______________________
    std::cout << "solver.Solve(\"3 square 67 + 38 /\")" << std::endl;
    try {
        std::cout << solver.Solve("3 square 67 + 38 /") << std::endl;
        std::cout << "OK" << std::endl;
        std::cout << std::endl;
    }
    catch (std::exception& ex) {
        std::cout << ex.what() << std::endl;
        std::cout << std::endl;
    }

    // ___________________________________TEST_17__________________________EXCEPTION FROM CALLED FUNCTION
    // ___________________________________(3*3+67)/0=error_________________
    std::cout << "solver.Solve(\"3 square 67 + 0 /\")" << std::endl;
    try {
        std::cout << solver.Solve("3 square 67 + 0 /") << std::endl;
        std::cout << "OK" << std::endl;
        std::cout << std::endl;
    }
    catch (std::exception& ex) {
        std::cout << ex.what() << std::endl;
        std::cout << std::endl;
    }

    // ___________________________________TEST_18__________________________EXCEPTION
    std::cout << "solver.Solve(\"3 square 67 + 38\")" << std::endl;
    try {
        std::cout << solver.Solve("3 square 67 + 38") << std::endl;
        std::cout << "OK" << std::endl;
        std::cout << std::endl;
    }
    catch (std::exception& ex) {
        std::cout << ex.what() << std::endl;
        std::cout << std::endl;
    }

    // ___________________________________TEST_19__________________________OK
    // ___________________________________1=1______________________________
    std::cout << "solver.Solve(\"1\")" << std::endl;
    try {
        std::cout << solver.Solve("1") << std::endl;
        std::cout << "OK" << std::endl;
        std::cout << std::endl;
    }
    catch (std::exception& ex) {
        std::cout << ex.what() << std::endl;
        std::cout << std::endl;
    }

    // ___________________________________TEST_20__________________________OK
    // _____________________________________(5^2+5-5+10)*2/10=7____________
    std::cout << "solver.Solve(\"5 square 5 + 5 - +ten double 10 /\")" << std::endl;
    try {
        std::cout << solver.Solve("5 square 5 + 5 - +ten double 10 /") << std::endl;
        std::cout << "OK" << std::endl;
        std::cout << std::endl;
    }
    catch (std::exception& ex) {
        std::cout << ex.what() << std::endl;
        std::cout << std::endl;
    }

    // ___________________________________TEST_21__________________________EXCEPTION
    std::cout << "solver.Solve(\"+\")" << std::endl;
    try {
        std::cout << solver.Solve("+") << std::endl;
        std::cout << "OK" << std::endl;
        std::cout << std::endl;
    }
    catch (std::exception& ex) {
        std::cout << ex.what() << std::endl;
        std::cout << std::endl;
    }

    return 0;
}
