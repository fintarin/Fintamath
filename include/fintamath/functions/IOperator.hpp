#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/parser/Parser.hpp"

namespace fintamath {

class IOperator;
using OperatorPtr = std::unique_ptr<IOperator>;

class IOperator : virtual public IFunction {

public:
  enum class Priority : uint16_t {
    PostfixUnary,   // postfix unary operators
    PrefixUnary,    // prefix unary operators
    Index,          // index operators
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
  static void registerParser() {
    IFunction::registerParser<T>();
    Parser::registerParser<T>(parserMap);
  }

  static OperatorPtr parse(const std::string &parsedStr, IOperator::Priority priority = IOperator::Priority::Any) {
    return Parser::parse<OperatorPtr>(parserMap, parsedStr, [priority](const OperatorPtr &oper) {
      return priority == IOperator::Priority::Any || oper->getOperatorPriority() == priority;
    });
  }

private:
  static Parser::ParserMap<OperatorPtr> parserMap;
};

template <typename Derived, typename... Args>
class IOperatorCRTP : virtual public IOperator, virtual public IFunctionCRTP<Derived, Args...> {
public:
  IOperatorCRTP(IOperator::Priority inPriority = IOperator::Priority::Any) : priority(inPriority) {
  }

  IOperatorCRTP(IOperator::Priority priority, bool isAssociative)
      : priority(priority), isAssociativeOper(isAssociative) {
  }

  IOperator::Priority getOperatorPriority() const final {
    return priority;
  }

  bool isAssociative() const override {
    return isAssociativeOper;
  }

private:
  const IOperator::Priority priority = IOperator::Priority::Any;

  const bool isAssociativeOper = true;
};

}
