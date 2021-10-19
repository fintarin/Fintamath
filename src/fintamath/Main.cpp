#include <iostream>
#include <string>

#include "calculator/Calculator.hpp"
#include "calculator/ExceptionClasses.hpp"

int main() {
  Calculator calc;

  while (true) {
    std::string str;
    std::string res;
    std::cout << ">> ";
    std::getline(std::cin, str);
    std::cout << "<< ";

    try {
      res = calc.calculate(str);
    } catch (IncorrectInput &exception) {
      res = exception.getError();
    } catch (DividedByZero &exception) {
      res = exception.getError();
    } catch (ZeroPowZero &exception) {
      res = exception.getError();
    } catch (OutOfRange &exception) {
      res = exception.getError();
    } catch (Undefined &exception) {
      res = exception.getError();
    }

    std::cout << res << "\n\n";
  }
}
