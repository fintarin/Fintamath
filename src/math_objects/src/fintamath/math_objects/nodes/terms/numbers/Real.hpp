#pragma once

#include "fintamath/math_objects/nodes/terms/numbers/Rational.hpp"

namespace fintamath {
  class Real : public Number {
  public:
    Real() = default;
    explicit Real(const std::string_view &str, uint64_t precision = DEFAULT_PRECISION);
    Real(Rational rhs, uint64_t precision = DEFAULT_PRECISION); // NOLINT
    Real(Integer rhs, uint64_t precision = DEFAULT_PRECISION);  // NOLINT

    Real &operator=(const Integer &rhs);

    Real &operator+=(const Real &rhs);
    Real &operator+=(const Integer &rhs);
    Real operator+(const Real &rhs) const;
    Real operator+(const Integer &rhs) const;
    friend Real operator+(const Integer &lhs, const Real &rhs);

    Real &operator-=(const Real &rhs);
    Real &operator-=(const Integer &rhs);
    Real operator-(const Real &rhs) const;
    Real operator-(const Integer &rhs) const;
    friend Real operator-(const Integer &lhs, const Real &rhs);

    Real &operator*=(const Real &rhs);
    Real &operator*=(const Integer &rhs);
    Real operator*(const Real &rhs) const;
    Real operator*(const Integer &rhs) const;
    friend Real operator*(const Integer &lhs, const Real &rhs);

    Real &operator/=(const Real &rhs);
    Real &operator/=(const Integer &rhs);
    Real operator/(const Real &rhs) const;
    Real operator/(const Integer &rhs) const;
    friend Real operator/(const Integer &lhs, const Real &rhs);

    Real &operator++();
    Real operator++(int);

    Real &operator--();
    Real operator--(int);

    Real operator+() const;
    Real operator-() const;

    bool operator==(const Real &rhs) const;
    bool operator==(const Integer &rhs) const;
    friend bool operator==(const Integer &lhs, const Real &rhs);

    bool operator!=(const Real &rhs) const;
    bool operator!=(const Integer &rhs) const;
    friend bool operator!=(const Integer &lhs, const Real &rhs);

    bool operator<(const Real &rhs) const;
    bool operator<(const Integer &rhs) const;
    friend bool operator<(const Integer &lhs, const Real &rhs);

    bool operator>(const Real &rhs) const;
    bool operator>(const Integer &rhs) const;
    friend bool operator>(const Integer &lhs, const Real &rhs);

    bool operator<=(const Real &rhs) const;
    bool operator<=(const Integer &rhs) const;
    friend bool operator<=(const Integer &lhs, const Real &rhs);

    bool operator>=(const Real &rhs) const;
    bool operator>=(const Integer &rhs) const;
    friend bool operator>=(const Integer &lhs, const Real &rhs);

    Real sqrt() const;
    Real round(const uint64_t &scale) const;

    std::string toString() const override;
    std::unique_ptr<Number> minimize() const override;

  private:
    Integer intVal;
    int64_t scale{};
    int64_t precision{};

    static constexpr uint64_t DEFAULT_PRECISION = 9;
  };
}
