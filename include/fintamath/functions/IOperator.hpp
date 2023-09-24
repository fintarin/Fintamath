#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/parser/Parser.hpp"

namespace fintamath {

class IOperator : public IFunction {

public:
  enum class Priority : uint16_t {
    Exponentiation, // e.g.  a ^ b
    PostfixUnary,   // e.g.  a!
    PrefixUnary,    // e.g.  -a
    Multiplication, // e.g.  a * b
    Addition,       // e.g.  a + b
    Comparison,     // e.g.  a = b
    Conjunction,    // e.g.  a & b
    Disjunction,    // e.g.  a | b
    Implication,    // e.g.  a -> b
    Equivalence,    // e.g.  a <-> b
    Any,
  };

public:
  virtual IOperator::Priority getOperatorPriority() const = 0;

  virtual bool isAssociative() const = 0;

  template <std::derived_from<IOperator> T>
  static void registerType() {
    IFunction::registerType<T>();
    Parser::registerType<T>(getParser());
  }

  static std::unique_ptr<IOperator> parse(const std::string &parsedStr, IOperator::Priority priority = IOperator::Priority::Any) {
    Parser::Comparator<const std::unique_ptr<IOperator> &> comp = [priority](const std::unique_ptr<IOperator> &oper) {
      return priority == IOperator::Priority::Any || oper->getOperatorPriority() == priority;
    };
    return Parser::parse<std::unique_ptr<IOperator>>(getParser(), comp, parsedStr);
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::IOperator;
  }

private:
  static Parser::Map<std::unique_ptr<IOperator>> &getParser();
};

template <typename Return, typename Derived, typename... Args>
class IOperatorCRTP : public IOperator {
#define I_OPERATOR_CRTP IOperatorCRTP<Return, Derived, Args...>
#include "fintamath/functions/IOperatorCRTP.hpp"
#undef I_OPERATOR_CRTP

public:
  explicit IOperatorCRTP(IOperator::Priority inPriority = IOperator::Priority::Any,
                         bool isAssociative = false,
                         bool isNonExressionEvaluatable = true)
      : isNonExressionEvaluatableFunc(isNonExressionEvaluatable),
        priority(inPriority),
        isAssociativeOper(isAssociative) {

    if constexpr (IsFunctionTypeAny<Derived>::value) {
      type = Type::Any;
    }
    else {
      type = Type(sizeof...(Args));
    }
  }
};

}
