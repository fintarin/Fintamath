#include "fintamath/functions/Function.hpp"

#include <functional>
#include <map>
#include <memory>
#include <string>

#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
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
  static const std::map<std::string, std::function<FunctionPtr()>> functionMap = {
      {"+", [] { return std::make_unique<Add>(); }},
      {"-", [] { return std::make_unique<Sub>(); }},
      {"*", [] { return std::make_unique<Mul>(); }},
      {"/", [] { return std::make_unique<Div>(); }},
      {"^", [] { return std::make_unique<Pow>(); }},
      {"pow", [] { return std::make_unique<Pow>(); }},
      {"%", [] { return std::make_unique<Percent>(); }},
      {"!", [] { return std::make_unique<Factorial>(); }},
      {"!!", [] { return std::make_unique<DoubleFactorial>(); }},
      {"sqrt", [] { return std::make_unique<Sqrt>(); }},
      {"exp", [] { return std::make_unique<Exp>(); }},
      {"log", [] { return std::make_unique<Log>(); }},
      {"ln", [] { return std::make_unique<Ln>(); }},
      {"lb", [] { return std::make_unique<Lb>(); }},
      {"lg", [] { return std::make_unique<Lg>(); }},
      {"sin", [] { return std::make_unique<Sin>(); }},
      {"cos", [] { return std::make_unique<Cos>(); }},
      {"tan", [] { return std::make_unique<Tan>(); }},
      {"cot", [] { return std::make_unique<Cot>(); }},
      {"asin", [] { return std::make_unique<Asin>(); }},
      {"acos", [] { return std::make_unique<Acos>(); }},
      {"atan", [] { return std::make_unique<Atan>(); }},
      {"acot", [] { return std::make_unique<Acot>(); }},
      {"abs", [] { return std::make_unique<Abs>(); }},
  };

  static const std::map<std::string, std::function<FunctionPtr()>> overloadedUnaryFunctionsMap = {
      {"+", [] { return std::make_unique<UnaryPlus>(); }},
      {"-", [] { return std::make_unique<Neg>(); }},
  };

  static FunctionPtr findFunction(const std::string &str,
                                  const std::map<std::string, std::function<FunctionPtr()>> &functionsMap);

  FunctionPtr fintamath::Function::parse(const std::string &str, bool unaryIfPossible) {
    if (unaryIfPossible) {
      if (FunctionPtr res = findFunction(str, overloadedUnaryFunctionsMap)) {
        return res;
      }
    }
    return findFunction(str, functionMap);
  }

  static FunctionPtr findFunction(const std::string &str,
                                  const std::map<std::string, std::function<FunctionPtr()>> &functionsMap) {
    if (const auto funcPair = functionsMap.find(str); funcPair != functionsMap.end()) {
      return funcPair->second();
    }
    return nullptr;
  }
}
