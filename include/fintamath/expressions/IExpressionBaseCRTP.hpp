#if !defined(I_EXPRESSION_BASE_CRTP) && !defined(NDEBUG)

#include "fintamath/expressions/IExpression.hpp"

namespace fintamath {

template <typename Derived>
class IExpressionBaseCRTP_ : public IExpression {

#endif // I_EXPRESSION_BASE_CRTP

#define I_MATH_OBJECT_CRTP I_EXPRESSION_BASE_CRTP
#include "fintamath/core/IMathObjectCRTP.hpp"
#undef I_MATH_OBJECT_CRTP

private:
#if !defined(I_EXPRESSION_BASE_CRTP) && !defined(NDEBUG)
};
}

#endif // I_EXPRESSION_CRTP
