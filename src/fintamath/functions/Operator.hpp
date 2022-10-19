#pragma once

#include "fintamath/functions/Function.hpp"

namespace fintamath {
  class Operator;
  using OperatorPtr = std::unique_ptr<Operator>;

  class Operator : virtual public Function {
  public:
    enum Priority : uint16_t {
      PostfixUnary,   // postfix unary operators
      PrefixUnary,    // prefix unary operators
      Exponentiation, // operators with priority like exponentiation
      Multiplication, // operators with priority like multiplication
      Addition,       // operators with priority like addition
      Comparison,     // comparison operators
      Any,            // operators with any priority
    };

  public:
    ~Operator() override = default;

    virtual Operator::Priority getOperatorPriority() const = 0;

    template <typename T, typename = std::enable_if_t<std::is_base_of_v<Operator, T>>>
    static bool addParser() {
      Function::addParser<T>();
      return meta::addParser<T>(parserMap);
    }

    static OperatorPtr parse(const std::string &parsedStr, Operator::Priority priority = Operator::Priority::Any) {
      return meta::parse<OperatorPtr>(parserMap, parsedStr, [priority](const OperatorPtr &oper) {
        return priority == Operator::Priority::Any || oper->getOperatorPriority() == priority;
      });
    }

  private:
    static meta::ParserMap<OperatorPtr> parserMap;
  };

  template <typename Derived, typename... Args>
  class OperatorCRTP : virtual public Operator, virtual public FunctionCRTP<Derived, Args...> {
  public:
    OperatorCRTP(Operator::Priority inPriority = Operator::Priority::Any) : priority(inPriority) {
    }

    ~OperatorCRTP() override = default;

    Operator::Priority getOperatorPriority() const final {
      return priority;
    }

  private:
    const Operator::Priority priority;
  };
}
