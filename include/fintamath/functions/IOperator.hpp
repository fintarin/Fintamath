#pragma once

#include <concepts>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>

#include "fintamath/core/MathObjectClass.hpp"
#include "fintamath/core/Parser.hpp"
#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class IOperator : public IFunction {
  FINTAMATH_PARENT_CLASS_BODY(IOperator, IFunction)

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
  virtual Priority getPriority() const noexcept = 0;

  virtual bool isAssociative() const noexcept = 0;
};

template <typename Return, typename Derived, typename... Args>
  requires(sizeof...(Args) > 0 && sizeof...(Args) < 3)
class IOperatorCRTP : public IOperator {
#define I_OPERATOR_CRTP IOperatorCRTP<Return, Derived, Args...>
#include "fintamath/functions/IOperatorCRTP.hpp"
#undef I_OPERATOR_CRTP
};

}
