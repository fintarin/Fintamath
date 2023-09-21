#if !defined(I_EXPRESSION_BASE_CRTP) && !defined(NDEBUG)

#include "fintamath/expressions/IExpression.hpp"

namespace fintamath {

template <typename Derived, bool isMultiFunction = false>
class IExpressionBaseCRTP_ : public IExpression {

#endif // I_EXPRESSION_BASE_CRTP

#define I_ARITHMETIC_CRTP I_EXPRESSION_BASE_CRTP
#include "fintamath/core/IArithmeticCRTP.hpp"
#undef I_ARITHMETIC_CRTP

private:
#if !defined(I_EXPRESSION_BASE_CRTP) && !defined(NDEBUG)
};
}

#endif // I_EXPRESSION_CRTP
