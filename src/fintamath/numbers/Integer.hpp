#pragma once

#include <memory>
#include <vector>

#include "fintamath/numbers/Number.hpp"

namespace fintamath {
  class Integer : public Number<Integer> {
  public:
    Integer() = default;

    explicit Integer(const std::string_view &str);

    Integer(int64_t val);

    std::string toString() const override;

    size_t getSize() const;

    Integer sqrt() const;

    Integer &operator%=(const Integer &rhs);

    Integer operator%(const Integer &rhs) const;

  protected:
    bool equals(const Integer &rhs) const override;

    bool less(const Integer &rhs) const override;

    bool more(const Integer &rhs) const override;

    Integer &add(const Integer &rhs) override;

    Integer &sub(const Integer &rhs) override;

    Integer &mul(const Integer &rhs) override;

    Integer &div(const Integer &rhs) override;

    Integer &inc() override;

    Integer &dec() override;

    Integer &mod(const Integer &rhs);

  private:
    void fixZero();

    std::vector<int64_t> intVect;
    bool sign{};
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
