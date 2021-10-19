#include <iostream>
#include <string>

#include "calculator/Calculator.hpp"
#include "calculator/ExceptionClasses.hpp"

using namespace std;

int main() {
  Calculator calc;

  while (true) {
    string str;
    string res;
    cout << ">> ";
    getline(cin, str);
    cout << "<< ";

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

    cout << res << "\n\n";
  }
}
