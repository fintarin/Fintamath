#ifndef BIGINTEGER_HPP
#define BIGINTEGER_HPP

#include <string>
#include <vector>

class BigInteger {
private:
  void changeZeroSign();

public:
  BigInteger();
  BigInteger(const BigInteger &);
  BigInteger(const int64_t);
  explicit BigInteger(const std::string &);

  BigInteger &operator=(const BigInteger &);
  BigInteger &operator=(const int64_t);

  BigInteger &operator+=(const BigInteger &);
  BigInteger &operator+=(const int64_t);

  BigInteger operator+(const BigInteger &) const;
  friend BigInteger operator+(const BigInteger &, const int64_t);
  friend BigInteger operator+(const int64_t, const BigInteger &);

  BigInteger &operator-=(const BigInteger &);
  BigInteger &operator-=(const int64_t);

  BigInteger operator-(const BigInteger &) const;
  friend BigInteger operator-(const BigInteger &, const int64_t);
  friend BigInteger operator-(const int64_t, const BigInteger &);

  BigInteger &operator*=(const BigInteger &);
  BigInteger &operator*=(const int64_t);

  BigInteger operator*(const BigInteger &) const;
  friend BigInteger operator*(const BigInteger &, const int64_t);
  friend BigInteger operator*(const int64_t, const BigInteger &);

  BigInteger &operator/=(const BigInteger &);
  BigInteger &operator/=(const int64_t);

  BigInteger operator/(const BigInteger &) const;
  friend BigInteger operator/(const BigInteger &, const int64_t);
  friend BigInteger operator/(const int64_t, const BigInteger &);

  BigInteger &operator%=(const BigInteger &);
  BigInteger &operator%=(const int64_t);

  BigInteger operator%(const BigInteger &) const;
  friend BigInteger operator%(const BigInteger &, const int64_t);
  friend BigInteger operator%(const int64_t, const BigInteger &);

  BigInteger &operator++();
  BigInteger &operator++(int);

  BigInteger &operator--();
  BigInteger &operator--(int);

  bool operator==(const BigInteger &) const;
  friend bool operator==(const BigInteger &, const int64_t);
  friend bool operator==(const int64_t, const BigInteger &);

  bool operator!=(const BigInteger &) const;
  friend bool operator!=(const BigInteger &, const int64_t);
  friend bool operator!=(const int64_t, const BigInteger &);

  bool operator>(const BigInteger &) const;
  friend bool operator>(const BigInteger &, const int64_t);
  friend bool operator>(const int64_t, const BigInteger &);

  bool operator>=(const BigInteger &) const;
  friend bool operator>=(const BigInteger &, const int64_t);
  friend bool operator>=(const int64_t, const BigInteger &);

  bool operator<(const BigInteger &) const;
  friend bool operator<(const BigInteger &, const int64_t);
  friend bool operator<(const int64_t, const BigInteger &);

  bool operator<=(const BigInteger &) const;
  friend bool operator<=(const BigInteger &, const int64_t);
  friend bool operator<=(const int64_t, const BigInteger &);

  BigInteger &toLongNumber(const std::string &);
  BigInteger &toLongNumber(const int64_t);

  size_t size() const;
  static int64_t getBaseSize();
  static int64_t getBase();

  friend std::istream &operator>>(std::istream &, BigInteger &);
  friend std::ostream &operator<<(std::ostream &, const BigInteger &);

  const std::string toString() const;

  friend BigInteger sqrt(const BigInteger &);

private:
  std::vector<int64_t> vectNum;
  bool sign;

  static int64_t baseSize;
  static int64_t base;
};

#endif // BIGINTEGER_HPP