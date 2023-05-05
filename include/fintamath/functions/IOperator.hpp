#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/parser/Parser.hpp"

namespace fintamath {

class IOperator : virtual public IFunction {

public:
  enum class Priority : uint16_t {
    PostfixUnary,   // postfix unary operators
    PrefixUnary,    // prefix unary operators
    Exponentiation, // exponentiation operators
    Multiplication, // multiplication operators
    Addition,       // addition operators
    Comparison,     // comparison operators
    And,            // conjunction operators
    Or,             // disjunction operators
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

  static std::unique_ptr<IOperator> parse(const std::string &parsedStr,
                                          IOperator::Priority priority = IOperator::Priority::Any) {
    Parser::Comparator<const std::unique_ptr<IOperator> &> comp = [priority](const std::unique_ptr<IOperator> &oper) {
      return priority == IOperator::Priority::Any || oper->getOperatorPriority() == priority;
    };
    return Parser::parse<std::unique_ptr<IOperator>>(getParser(), comp, parsedStr);
  }

private:
  static Parser::Map<std::unique_ptr<IOperator>> &getParser() {
    static Parser::Map<std::unique_ptr<IOperator>> parser;
    return parser;
  }
};

template <typename Return, typename Derived, typename... Args>
class IOperatorCRTP : public IFunctionCRTP<Return, Derived, Args...>, virtual public IOperator {
public:
  IOperatorCRTP(IOperator::Priority inPriority = IOperator::Priority::Any, bool isAssociative = true)
      : IFunctionCRTP<Return, Derived, Args...>(false),
        priority(inPriority),
        isAssociativeOper(isAssociative) {
  }

  IOperator::Priority getOperatorPriority() const final {
    return priority;
  }

  bool isAssociative() const final {
    return isAssociativeOper;
  }

private:
  const IOperator::Priority priority;

  const bool isAssociativeOper;
};

}
