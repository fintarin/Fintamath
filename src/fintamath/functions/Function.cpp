#include "fintamath/functions/Function.hpp"

#include <memory>

#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/factorials/DoubleFactorial.hpp"
#include "fintamath/functions/factorials/Factorial.hpp"
#include "fintamath/functions/logarithms/Lb.hpp"
#include "fintamath/functions/logarithms/Lg.hpp"
#include "fintamath/functions/logarithms/Ln.hpp"
#include "fintamath/functions/logarithms/Log.hpp"
#include "fintamath/functions/other/Abs.hpp"
#include "fintamath/functions/other/Percent.hpp"
#include "fintamath/functions/powers/Exp.hpp"
#include "fintamath/functions/powers/Pow.hpp"
#include "fintamath/functions/powers/Sqrt.hpp"
#include "fintamath/functions/trigonometry/Acos.hpp"
#include "fintamath/functions/trigonometry/Acot.hpp"
#include "fintamath/functions/trigonometry/Asin.hpp"
#include "fintamath/functions/trigonometry/Atan.hpp"
#include "fintamath/functions/trigonometry/Cos.hpp"
#include "fintamath/functions/trigonometry/Cot.hpp"
#include "fintamath/functions/trigonometry/Sin.hpp"
#include "fintamath/functions/trigonometry/Tan.hpp"

namespace fintamath {
  FunctionPtr fintamath::Function::parse(const std::string &str, bool unaryIfPossible) {
    if (str == "+") {
      return std::make_unique<Add>();
    }
    if (str == "-") {
      if (unaryIfPossible) {
        return std::make_unique<Neg>();
      }
      return std::make_unique<Sub>();
    }
    if (str == "*") {
      return std::make_unique<Mul>();
    }
    if (str == "/") {
      return std::make_unique<Div>();
    }
    if (str == "^" || str == "pow") {
      return std::make_unique<Pow>();
    }
    if (str == "%") {
      return std::make_unique<Percent>();
    }
    if (str == "!") {
      return std::make_unique<Factorial>();
    }
    if (str == "!!") {
      return std::make_unique<DoubleFactorial>();
    }
    if (str == "sqrt") {
      return std::make_unique<Sqrt>();
    }
    if (str == "exp") {
      return std::make_unique<Exp>();
    }
    if (str == "log") {
      return std::make_unique<Log>();
    }
    if (str == "ln") {
      return std::make_unique<Ln>();
    }
    if (str == "lb") {
      return std::make_unique<Lb>();
    }
    if (str == "lg") {
      return std::make_unique<Lg>();
    }
    if (str == "sin") {
      return std::make_unique<Sin>();
    }
    if (str == "cos") {
      return std::make_unique<Cos>();
    }
    if (str == "tan") {
      return std::make_unique<Tan>();
    }
    if (str == "cot") {
      return std::make_unique<Cot>();
    }
    if (str == "asin") {
      return std::make_unique<Asin>();
    }
    if (str == "acos") {
      return std::make_unique<Acos>();
    }
    if (str == "atan") {
      return std::make_unique<Atan>();
    }
    if (str == "acot") {
      return std::make_unique<Acot>();
    }
    if (str == "abs") {
      return std::make_unique<Abs>();
    }
    return nullptr;
  }
}
