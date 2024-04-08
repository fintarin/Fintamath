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
  IOperator::Priority getPriority() const noexcept final {
    return Derived::getPriorityStatic();
  }

  static constexpr bool isAssociativeStatic() noexcept {
    return false;
  }

  bool isAssociative() const noexcept final {
    return Derived::isAssociativeStatic();
  }

private:
#if !defined(I_OPERATOR_CRTP) && !defined(NDEBUG)
};
}

#endif // I_OPERATOR_CRTP
