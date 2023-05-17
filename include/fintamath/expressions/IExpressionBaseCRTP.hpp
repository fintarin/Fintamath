#ifndef FINTAMATH_I_EXPRESSION_BASE_CRTP

#include "fintamath/expressions/IExpression.hpp"

namespace fintamath {

template <typename Derived, bool isMultiFunction = false>
class IExpressionBaseCRTP_ : public IExpression {

#endif // FINTAMATH_I_EXPRESSION_BASE_CRTP

#define FINTAMATH_I_ARITHMETIC_CRTP FINTAMATH_I_EXPRESSION_BASE_CRTP
#include "fintamath/core/IArithmeticCRTP.hpp"
#undef FINTAMATH_I_ARITHMETIC_CRTP

private:
#ifndef FINTAMATH_I_EXPRESSION_BASE_CRTP
};
}

#endif // FINTAMATH_I_EXPRESSION_CRTP
