#ifndef INTEGER_HPP
#define INTEGER_HPP

#include <string>
#include <vector>

class Integer {
public:
  Integer();
  Integer(const Integer &);
  Integer(int64_t);
  explicit Integer(const std::string &);

  Integer &operator=(const Integer &);
  Integer &operator=(int64_t);

  Integer &operator+=(const Integer &);
  Integer &operator+=(int64_t);

  Integer operator+(const Integer &) const;
  friend Integer operator+(const Integer &, int64_t);
  friend Integer operator+(int64_t, const Integer &);

  Integer &operator-=(const Integer &);
  Integer &operator-=(int64_t);

  Integer operator-(const Integer &) const;
  friend Integer operator-(const Integer &, int64_t);
  friend Integer operator-(int64_t, const Integer &);

  Integer &operator*=(const Integer &);
  Integer &operator*=(int64_t);

  Integer operator*(const Integer &) const;
  friend Integer operator*(const Integer &, int64_t);
  friend Integer operator*(int64_t, const Integer &);

  Integer &operator/=(const Integer &);
  Integer &operator/=(int64_t);

  Integer operator/(const Integer &) const;
  friend Integer operator/(const Integer &, int64_t);
  friend Integer operator/(int64_t, const Integer &);

  Integer &operator%=(const Integer &);
  Integer &operator%=(int64_t);

  Integer operator%(const Integer &) const;
  friend Integer operator%(const Integer &, int64_t);
  friend Integer operator%(int64_t, const Integer &);

  Integer &operator++();
  Integer &operator++(int);

  Integer &operator--();
  Integer &operator--(int);

  bool operator==(const Integer &) const;
  friend bool operator==(const Integer &, int64_t);
  friend bool operator==(int64_t, const Integer &);

  bool operator!=(const Integer &) const;
  friend bool operator!=(const Integer &, int64_t);
  friend bool operator!=(int64_t, const Integer &);

  bool operator>(const Integer &) const;
  friend bool operator>(const Integer &, int64_t);
  friend bool operator>(int64_t, const Integer &);

  bool operator>=(const Integer &) const;
  friend bool operator>=(const Integer &, int64_t);
  friend bool operator>=(int64_t, const Integer &);

  bool operator<(const Integer &) const;
  friend bool operator<(const Integer &, int64_t);
  friend bool operator<(int64_t, const Integer &);

  bool operator<=(const Integer &) const;
  friend bool operator<=(const Integer &, int64_t);
  friend bool operator<=(int64_t, const Integer &);

  Integer &toLongNumber(const std::string &);
  Integer &toLongNumber(int64_t);

  size_t size() const;

  friend std::istream &operator>>(std::istream &, Integer &);
  friend std::ostream &operator<<(std::ostream &, const Integer &);

  std::string toString() const;

  friend Integer sqrt(const Integer &);

private:
  std::vector<int64_t> vectNum;
  bool sign{};

  void changeZeroSign();
};

#endif // INTEGER_HPP
