#pragma once

#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "fintamath/numbers/INumber.hpp"

namespace fintamath {
  class IntegerImpl;

  class Integer : public INumberCRTP<Integer> {
  public:
    Integer();

    Integer(const Integer &rhs);

    Integer &operator=(const Integer &rhs);

    ~Integer() override;

    Integer(Integer &&rhs) noexcept;

    Integer &operator=(Integer &&rhs) noexcept;

    explicit Integer(std::string str);

    Integer(int64_t val);

    std::string toString() const override;

    std::string getClassName() const override;

    Integer &operator%=(const Integer &rhs);

    Integer operator%(const Integer &rhs) const;

    friend Integer sqrt(Integer rhs);

  protected:
    bool equals(const Integer &rhs) const override;

    bool less(const Integer &rhs) const override;

    bool more(const Integer &rhs) const override;

    Integer &add(const Integer &rhs) override;

    Integer &substract(const Integer &rhs) override;

    Integer &multiply(const Integer &rhs) override;

    Integer &divide(const Integer &rhs) override;

    Integer &mod(const Integer &rhs);

    Integer &negate() override;

    Integer &increase() override;

    Integer &decrease() override;

  private:
    std::unique_ptr<IntegerImpl> value;
  };

  template <typename RhsType,
            typename = std::enable_if_t<std::is_convertible_v<RhsType, Integer> && !std::is_same_v<Integer, RhsType>>>
  Integer &operator%=(Integer &lhs, const RhsType &rhs) {
    return lhs %= LhsType(rhs);
  }

  template <typename RhsType,
            typename = std::enable_if_t<std::is_convertible_v<RhsType, Integer> && !std::is_same_v<Integer, RhsType>>>
  Integer operator%(const Integer &lhs, const RhsType &rhs) {
    return lhs % Integer(rhs);
  }

  template <typename LhsType,
            typename = std::enable_if_t<std::is_convertible_v<LhsType, Integer> && !std::is_same_v<LhsType, Integer>>>
  Integer operator%(const LhsType &lhs, const Integer &rhs) {
    return Integer(lhs) % rhs;
  }
}
