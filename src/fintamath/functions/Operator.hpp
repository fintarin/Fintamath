#pragma once

#include "fintamath/functions/Function.hpp"

namespace fintamath {
  class Operator;
  using OperatorPtr = std::unique_ptr<Operator>;

  class Operator : virtual public Function {
  public:
    enum class Priority : int32_t {
      PostfixUnary,   // postfix unary operators
      PrefixUnary,    // prefix unary operators
      Exponentiation, // operators with priority like exponentiation
      Multiplication, // operators with priority like multiplication
      Addition,       // operators with priority like addition
      Comparison,     // comparison operators
      None,           // operators with undefined priority
    };

  public:
    ~Operator() override = default;

    virtual Operator::Priority getOperatorPriority() const = 0;

    template <typename T, typename = std::enable_if_t<std::is_base_of_v<Operator, T>>>
    static bool addParser() {
      Function::addParser<T>();
      return meta::addParser<T>(parserMap);
    }

    static OperatorPtr parse(const std::string &parsedStr, Function::Type type,
                             Operator::Priority priority = Operator::Priority::None) {
      return meta::parse<OperatorPtr>(parserMap, parsedStr, [type, priority](const OperatorPtr &oper) {
        return oper->getFunctionType() == type &&
               (priority == Operator::Priority::None || oper->getOperatorPriority() == priority);
      });
    }

  private:
    static meta::ParserMap<OperatorPtr> parserMap;
  };

  template <typename Derived, typename... Args>
  class OperatorCRTP : virtual public Operator, virtual public FunctionCRTP<Derived, Args...> {
  public:
    OperatorCRTP(Operator::Priority inPriority = Operator::Priority::None) : priority(inPriority) {
    }

    ~OperatorCRTP() override = default;

    Operator::Priority getOperatorPriority() const final {
      return priority;
    }

  private:
    const Operator::Priority priority;
  };
}
