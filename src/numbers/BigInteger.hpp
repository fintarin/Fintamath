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
 BigInteger(const long long);
    explicit BigInteger(const std::string &);

    BigInteger &operator=(const BigInteger &);
    BigInteger &operator=(const long long);

    BigInteger &operator+=(const BigInteger &);
    BigInteger &operator+=(const long long);

    BigInteger operator+(const BigInteger &) const;
    friend BigInteger operator+(const BigInteger &, const long long);
    friend BigInteger operator+(const long long, const BigInteger &);

    BigInteger &operator-=(const BigInteger &);
    BigInteger &operator-=(const long long);

    BigInteger operator-(const BigInteger &) const;
    friend BigInteger operator-(const BigInteger &, const long long);
    friend BigInteger operator-(const long long, const BigInteger &);

    BigInteger &operator*=(const BigInteger &);
    BigInteger &operator*=(const long long);

    BigInteger operator*(const BigInteger &) const;
    friend BigInteger operator*(const BigInteger &, const long long);
    friend BigInteger operator*(const long long, const BigInteger &);

    BigInteger &operator/=(const BigInteger &);
    BigInteger &operator/=(const long long);

    BigInteger operator/(const BigInteger &) const;
    friend BigInteger operator/(const BigInteger &, const long long);
    friend BigInteger operator/(const long long, const BigInteger &);

    BigInteger &operator%=(const BigInteger &);
    BigInteger &operator%=(const long long);

    BigInteger operator%(const BigInteger &) const;
    friend BigInteger operator%(const BigInteger &, const long long);
    friend BigInteger operator%(const long long, const BigInteger &);

    BigInteger &operator++();
    BigInteger &operator++(int);

    BigInteger &operator--();
    BigInteger &operator--(int);

    bool operator==(const BigInteger &) const;
    friend bool operator==(const BigInteger &, const long long);
    friend bool operator==(const long long, const BigInteger &);

    bool operator!=(const BigInteger &) const;
    friend bool operator!=(const BigInteger &, const long long);
    friend bool operator!=(const long long, const BigInteger &);

    bool operator>(const BigInteger &) const;
    friend bool operator>(const BigInteger &, const long long);
    friend bool operator>(const long long, const BigInteger &);

    bool operator>=(const BigInteger &) const;
    friend bool operator>=(const BigInteger &, const long long);
    friend bool operator>=(const long long, const BigInteger &);

    bool operator<(const BigInteger &) const;
    friend bool operator<(const BigInteger &, const long long);
    friend bool operator<(const long long, const BigInteger &);

    bool operator<=(const BigInteger &) const;
    friend bool operator<=(const BigInteger &, const long long);
    friend bool operator<=(const long long, const BigInteger &);

    BigInteger &toLongNumber(const std::string &);
    BigInteger &toLongNumber(const long long);

    size_t size() const;
    static long long getBaseSize();
    static long long getBase();

    friend std::istream &operator>>(std::istream &, BigInteger &);
    friend std::ostream &operator<<(std::ostream &, const BigInteger &);

    const std::string toString() const;

    friend BigInteger sqrt(const BigInteger &);

private:
    std::vector<long long> vectNum;
    bool sign;

    static long long baseSize;
    static long long base;
};

#endif // BIGINTEGER_HPP