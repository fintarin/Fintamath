#if !defined(I_OPERATOR_CRTP) && !defined(NDEBUG)

#include "fintamath/functions/IOperator.hpp"

namespace fintamath {

template <typename Return, typename Derived, typename... Args>
class IOperatorCRTP_ : public IOperator {

#endif // I_OPERATOR_CRTP

#define I_FUNCTION_CRTP I_OPERATOR_CRTP
#include "fintamath/functions/IFunctionCRTP.hpp"
#undef I_FUNCTION_CRTP

public:
  IOperator::Priority getOperatorPriority() const final {
    return priority;
  }

  bool isAssociative() const final {
    return isAssociativeOper;
  }

private:
  IOperator::Priority priority;

  bool isAssociativeOper;

private:
#if !defined(I_OPERATOR_CRTP) && !defined(NDEBUG)
};
}

#endif // I_OPERATOR_CRTP
