#pragma once

#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class IOperator : public IFunction {
  using OperatorParser = Parser<std::unique_ptr<IOperator>>;

public:
  enum class Priority : uint8_t {
    Highest,
    Exponentiation, // e.g.  a ^ b
    PostfixUnary,   // e.g.  a!
    PrefixUnary,    // e.g.  -a
    Multiplication, // e.g.  a * b
    Addition,       // e.g.  a + b
    Modulo,         // e.g.  a mod b
    Comparison,     // e.g.  a = b
    Conjunction,    // e.g.  a & b
    Disjunction,    // e.g.  a | b
    Implication,    // e.g.  a -> b
    Equivalence,    // e.g.  a <-> b
    Comma,          // e.g.  a , b
    Lowest,
  };

public:
  virtual Priority getOperatorPriority() const = 0;

  virtual bool isAssociative() const = 0;

  static std::unique_ptr<IOperator> parse(const std::string &parsedStr, Priority priority = Priority::Lowest) {
    const auto validator = [priority](const std::unique_ptr<IOperator> &oper) {
      return priority == Priority::Lowest || oper->getOperatorPriority() == priority;
    };
    return getParser().parse(validator, parsedStr);
  }

  template <std::derived_from<IOperator> T>
  static void registerType() {
    IFunction::registerType<T>();
    getParser().registerType<T>();
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::IOperator;
  }

private:
  static OperatorParser &getParser();
};

template <typename Return, typename Derived, typename... Args>
class IOperatorCRTP : public IOperator {
#define I_OPERATOR_CRTP IOperatorCRTP<Return, Derived, Args...>
#include "fintamath/functions/IOperatorCRTP.hpp"
#undef I_OPERATOR_CRTP

public:
  explicit IOperatorCRTP(const Priority inPriority = Priority::Lowest,
                         const bool isAssociative = false,
                         const bool isEvaluatable = true)
      : isEvaluatableFunc(isEvaluatable),
        priority(inPriority),
        isAssociativeOper(isAssociative) {

    if constexpr (IsFunctionTypeAny<Derived>::value) {
      type = Type::Any;
    }
    else {
      type = static_cast<Type>(sizeof...(Args));
    }
  }
};

}
