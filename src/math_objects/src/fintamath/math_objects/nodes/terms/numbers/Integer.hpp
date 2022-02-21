#ifndef INTEGER_HPP
#define INTEGER_HPP

#include <vector>

#include "fintamath/math_objects/nodes/terms/numbers/Number.hpp"

class Integer : public Number {
public:
  Integer() = default;
  explicit Integer(const std::string_view &strVal);
  // cppcheck-suppress noExplicitConstructor // NOLINTNEXTLINE
  Integer(int64_t val);

  Integer &operator=(int64_t rhs);

  Integer &operator+=(const Integer &rhs);
  Integer &operator+=(int64_t rhs);
  Integer operator+(const Integer &rhs) const;
  Integer operator+(int64_t rhs) const;
  friend Integer operator+(int64_t lhs, const Integer &rhs);

  Integer &operator-=(const Integer &rhs);
  Integer &operator-=(int64_t rhs);
  Integer operator-(const Integer &rhs) const;
  Integer operator-(int64_t rhs) const;
  friend Integer operator-(int64_t lhs, const Integer &rhs);

  Integer &operator*=(const Integer &rhs);
  Integer &operator*=(int64_t rhs);
  Integer operator*(const Integer &rhs) const;
  Integer operator*(int64_t rhs) const;
  friend Integer operator*(int64_t lhs, const Integer &rhs);

  Integer &operator/=(const Integer &rhs);
  Integer &operator/=(int64_t rhs);
  Integer operator/(const Integer &rhs) const;
  Integer operator/(int64_t rhs) const;
  friend Integer operator/(int64_t lhs, const Integer &rhs);

  Integer &operator%=(const Integer &rhs);
  Integer &operator%=(int64_t rhs);
  Integer operator%(const Integer &rhs) const;
  Integer operator%(int64_t rhs) const;
  friend Integer operator%(int64_t lhs, const Integer &rhs);

  Integer &operator++();
  Integer operator++(int);

  Integer &operator--();
  Integer operator--(int);

  Integer operator+() const;
  Integer operator-() const;

  bool operator==(const Integer &rhs) const;
  bool operator==(int64_t rhs) const;
  friend bool operator==(int64_t lhs, const Integer &rhs);

  bool operator!=(const Integer &rhs) const;
  bool operator!=(int64_t rhs) const;
  friend bool operator!=(int64_t lhs, const Integer &rhs);

  bool operator<(const Integer &rhs) const;
  bool operator<(int64_t rhs) const;
  friend bool operator<(int64_t lhs, const Integer &rhs);

  bool operator>(const Integer &rhs) const;
  bool operator>(int64_t rhs) const;
  friend bool operator>(int64_t lhs, const Integer &rhs);

  bool operator<=(const Integer &rhs) const;
  bool operator<=(int64_t rhs) const;
  friend bool operator<=(int64_t lhs, const Integer &rhs);

  bool operator>=(const Integer &rhs) const;
  bool operator>=(int64_t rhs) const;
  friend bool operator>=(int64_t lhs, const Integer &rhs);

  size_t size() const;
  std::string toString() const override;

  friend Integer sqrt(const Integer &);

private:
  std::vector<int64_t> intVect;
  bool sign{};

  void fixZero();
};

#endif // INTEGER_HPP
