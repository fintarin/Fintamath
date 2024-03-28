#if !defined(I_EXPRESSION_CRTP) && !defined(NDEBUG)

#include "fintamath/expressions/IExpression.hpp"

namespace fintamath {

template <typename Derived>
class IExpressionCRTP_ : public IExpressionBaseCRTP<Derived> {

#endif // I_EXPRESSION_CRTP

public:
  bool equals(const Derived &rhs) const override {
    if (static_cast<bool>(this->getFunction()) != static_cast<bool>(rhs.getFunction()) ||
        (this->getFunction() && rhs.getFunction() && *this->getFunction() != *rhs.getFunction())) {

      return false;
    }

    const ArgumentPtrVector &lhsChildren = this->getChildren();
    const ArgumentPtrVector &rhsChildren = rhs.getChildren();

    if (lhsChildren.size() != rhsChildren.size()) {
      return false;
    }

    for (const auto i : stdv::iota(0U, lhsChildren.size())) {
      if (lhsChildren[i] != rhsChildren[i] && *lhsChildren[i] != *rhsChildren[i]) {
        return false;
      }
    }

    return true;
  }

private:
#if !defined(I_EXPRESSION_CRTP) && !defined(NDEBUG)
};
}

#endif // I_EXPRESSION_CRTP
