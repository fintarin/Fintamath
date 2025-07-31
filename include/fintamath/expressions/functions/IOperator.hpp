#pragma once

#include "fintamath/expressions/functions/IFunction.hpp"

namespace fintamath {

class IOperator : public IFunction {
  FINTAMATH_INTERFACE_BODY(IOperator, IFunction)

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

  struct OperatorDeclaration {
    FunctionDeclaration functionDeclarion;
    Priority operatorPriority = Priority::Addition;
  };

protected:
  IOperator() = default;

  explicit IOperator(Children inChildren);

public:
  const FunctionDeclaration &getFunctionDeclaration() const noexcept final;

  virtual const OperatorDeclaration &getOperatorDeclaration() const noexcept = 0;
};

}
