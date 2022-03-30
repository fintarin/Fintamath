#pragma once

#include <vector>
#include <memory>

#include "fintamath/nodes/Node.hpp"

namespace fintamath {
  class Integer : public Node {
  public:
    Integer() = default;
    explicit Integer(const std::string_view &str);
    Integer(int64_t val); // NOLINT

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
    Integer sqrt() const;
    std::string toString() const override;
    std::shared_ptr<Object> clone() const override;
  private:
    std::vector<int64_t> intVect;
    bool sign{};

    void fixZero();
  };
}
