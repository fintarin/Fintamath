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
    Exponentiation, // operators with priority like exponentiation
    Multiplication, // operators with priority like multiplication
    Addition,       // operators with priority like addition
    Comparison,     // comparison operators
    And,            // operators with priority like logical AND
    Or,             // operators with priority like logical OR
    Any,            // operators with any priority
  };

public:
  virtual IOperator::Priority getOperatorPriority() const = 0;

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

  IOperator::Priority getOperatorPriority() const final {
    return priority;
  }

private:
  const IOperator::Priority priority;
};

}