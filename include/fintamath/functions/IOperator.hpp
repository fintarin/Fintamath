#pragma once

#include <concepts>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>

#include "fintamath/core/MathObjectTypes.hpp"
#include "fintamath/core/Parser.hpp"
#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class IOperator : public IFunction {
  using OperatorParser = detail::Parser<std::unique_ptr<IOperator>()>;

public:
  enum class Priority : uint8_t {
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
  };

public:
  virtual Priority getPriority() const = 0;

  virtual bool isAssociative() const = 0;

  static std::unique_ptr<IFunction> parse(const std::string &parsedStr, size_t argSize) {
    const auto validator = [argSize](const std::unique_ptr<IOperator> &oper) {
      return argSize == oper->getArgumentTypes().size();
    };
    return getParser().parse(validator, parsedStr);
  }

  static std::unique_ptr<IOperator> parse(const std::string &parsedStr) {
    return getParser().parse(parsedStr);
  }

  static std::unique_ptr<IOperator> parse(const std::string &parsedStr, Priority priority) {
    const auto validator = [priority](const std::unique_ptr<IOperator> &oper) {
      return oper->getPriority() == priority;
    };
    return getParser().parse(validator, parsedStr);
  }

  template <std::derived_from<IOperator> T>
  static void registerType() {
    IFunction::registerType<T>();
    getParser().registerType<T>();
  }

  static constexpr MathObjectType getTypeStatic() {
    return {MathObjectType::IOperator, "IOperator"};
  }

private:
  static OperatorParser &getParser();
};

template <typename Return, typename Derived, typename... Args>
  requires(sizeof...(Args) > 0 && sizeof...(Args) < 3)
class IOperatorCRTP : public IOperator {
#define I_OPERATOR_CRTP IOperatorCRTP<Return, Derived, Args...>
#include "fintamath/functions/IOperatorCRTP.hpp"
#undef I_OPERATOR_CRTP
};

}
