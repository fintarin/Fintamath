#pragma once

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/exceptions/FunctionCallException.hpp"
#include "fintamath/helpers/Caster.hpp"

namespace fintamath {
  class IModular;
  using ModularPtr = std::unique_ptr<IModular>;

  class IModular : virtual public IMathObject {
  public:
    friend ModularPtr operator%(const IModular &lhs, const IModular &rhs);

  protected:
    virtual ModularPtr modAbstract(const IModular &rhs) const = 0;
  };

  inline ModularPtr operator%(const IModular &lhs, const IModular &rhs) {
    return lhs.modAbstract(rhs);
  }

  template <typename Derived>
  class IModularCRTP : virtual public IModular, virtual public IMathObjectCRTP<Derived> {
  public:
    Derived &operator%=(const Derived &rhs) {
      return mod(rhs);
    }

    Derived operator%(const Derived &rhs) const {
      return Derived(static_cast<const Derived &>(*this)) %= rhs;
    }

  protected:
    virtual Derived &mod(const Derived &rhs) = 0;

    ModularPtr modAbstract(const IModular &rhs) const final {
      FINTAMATH_ARITHMETIC_OPERATOR(IModular, %);
    }
  };

  template <typename LhsType, typename RhsType,
            typename = std::enable_if_t<std::is_base_of_v<IModular, LhsType> &&
                                        std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
  LhsType &operator%=(LhsType &lhs, const RhsType &rhs) {
    return lhs %= LhsType(rhs);
  }

  template <typename LhsType, typename RhsType,
            typename = std::enable_if_t<std::is_base_of_v<IModular, LhsType> &&
                                        std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
  LhsType operator%(const LhsType &lhs, const RhsType &rhs) {
    return lhs % LhsType(rhs);
  }

  template <typename RhsType, typename LhsType,
            typename = std::enable_if_t<std::is_base_of_v<IModular, RhsType> &&
                                        std::is_convertible_v<LhsType, RhsType> && !std::is_same_v<LhsType, RhsType>>>
  RhsType operator%(const LhsType &lhs, const RhsType &rhs) {
    return RhsType(lhs) % rhs;
  }
}
