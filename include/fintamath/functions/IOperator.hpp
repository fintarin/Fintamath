#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/parser/Parser.hpp"

namespace fintamath {

class IOperator : public IFunction {

public:
  enum class Priority : uint16_t {
    Exponentiation, // exponentiation operators
    PostfixUnary,   // postfix unary operators
    PrefixUnary,    // prefix unary operators
    Multiplication, // multiplication operators
    Addition,       // addition operators
    Comparison,     // comparison operators
    Conjunction,    // conjunction operators
    Disjunction,    // disjunction operators
    Implication,    // implication operators
    Equivalence,    // equivalence operators
    Any,            // any priority operators
  };

public:
  virtual IOperator::Priority getOperatorPriority() const = 0;

  virtual bool isAssociative() const = 0;

  template <typename T, typename = std::enable_if_t<std::is_base_of_v<IOperator, T>>>
  static void registerType() {
    IFunction::registerType<T>();
    Parser::registerType<T>(getParser());
  }

  static std::unique_ptr<IOperator> parse(const std::string &parsedStr, IOperator::Priority priority = IOperator::Priority::Any) {
    Parser::Comparator<const std::unique_ptr<IOperator> &> comp = [priority](const std::unique_ptr<IOperator> &oper) {
      return size_t(priority == IOperator::Priority::Any || oper->getOperatorPriority() == priority);
    };
    return Parser::parse<std::unique_ptr<IOperator>>(getParser(), comp, parsedStr);
  }

  static MathObjectTypeId getTypeIdStatic() {
    return MathObjectTypeId(MathObjectType::IOperator);
  }

private:
  static Parser::Map<std::unique_ptr<IOperator>> &getParser();
};

template <typename Return, typename Derived, typename... Args>
class IOperatorCRTP : public IOperator {
#define FINTAMATH_I_OPERATOR_CRTP IOperatorCRTP<Return, Derived, Args...>
#include "fintamath/functions/IOperatorCRTP.hpp"
#undef FINTAMATH_I_OPERATOR_CRTP

public:
  IOperatorCRTP(IOperator::Priority inPriority = IOperator::Priority::Any,
                bool isAssociative = true,
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
