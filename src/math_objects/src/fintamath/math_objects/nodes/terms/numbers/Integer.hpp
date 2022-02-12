#pragma once

#include <vector>

#include "fintamath/math_objects/nodes/terms/numbers/Number.hpp"

namespace fintamath {
  class Integer : public Number {
  public:
    Integer() = default;
    explicit Integer(const std::string_view &str);
    explicit Integer(int64_t rhs);

    Integer &operator+=(const Integer &rhs);
    Integer operator+(const Integer &rhs) const;
    Integer &operator-=(const Integer &rhs);
    Integer operator-(const Integer &rhs) const;
    Integer &operator*=(const Integer &rhs);
    Integer operator*(const Integer &rhs) const;
    Integer &operator/=(const Integer &rhs);
    Integer operator/(const Integer &rhs) const;
    Integer &operator%=(const Integer &rhs);
    Integer operator%(const Integer &rhs) const;

    Integer &operator++();
    Integer operator++(int);
    Integer &operator--();
    Integer operator--(int);

    Integer operator+() const;
    Integer operator-() const;

    bool operator==(const Integer &rhs) const;
    bool operator!=(const Integer &rhs) const;
    bool operator<(const Integer &rhs) const;
    bool operator>(const Integer &rhs) const;
    bool operator<=(const Integer &rhs) const;
    bool operator>=(const Integer &rhs) const;

    Integer sqrt() const;

    std::string toString() const override;

  private:
    std::vector<int64_t> intVect;
    bool sign{};

    void fixZero();
  };
}
