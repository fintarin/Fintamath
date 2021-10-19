/*
  Длинное число хранится в виде вектора, где разряды идут от младших к старшим. База системы (BASE) = 10^9.
*/
#include "numbers/BigInteger.hpp"

#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;
using NumVector = vector<int64_t>;

constexpr uint8_t PRIMARY_BASE_SIZE = 9;
constexpr uint64_t PRIMARY_BASE = 1000000000;
constexpr uint64_t KARATSUBA_CUTOFF = 64;

int64_t BigInteger::baseSize = PRIMARY_BASE_SIZE;
int64_t BigInteger::base = PRIMARY_BASE;

static void toSignificantDigits(NumVector &A);
static size_t numOfFirstZeros(const NumVector &A);
static void toBasePositive(NumVector &A, size_t i);
static void toBaseNegative(NumVector &A, size_t i);

static bool equal(const NumVector &A, const NumVector &B);
static bool greater(const NumVector &A, const NumVector &B);

static NumVector add(const NumVector &A, const NumVector &B);
static NumVector addCut(const NumVector &A, const NumVector &B);

static NumVector substract(const NumVector &A, const NumVector &B);

static NumVector shortMultiply(const NumVector &A, int64_t num);
static NumVector polynomialMultiply(const NumVector &A, const NumVector &B);
static NumVector karatsubaMultiply(const NumVector &A, const NumVector &B);
static size_t multiplyZeros(NumVector &A, NumVector &B);
static NumVector multiply(const NumVector &inA, const NumVector &inB);

static NumVector shortDivide(const NumVector &A, int64_t num);
static NumVector shortDivide(const NumVector &A, int64_t num, NumVector &mod);
static void divideZeros(NumVector &A, NumVector &B);
static NumVector binsearchDivide(const NumVector &A, const NumVector &B, NumVector &left, NumVector &right);
static NumVector divide(const NumVector &inA, const NumVector &inB, NumVector &mod);

NumVector sqrt(const NumVector &A);

BigInteger::BigInteger() {
  this->sign = false;
  this->vectNum.push_back(0);
}

BigInteger::BigInteger(const BigInteger &other) {
  *this = other;
}

BigInteger::BigInteger(int64_t inNum) {
  *this = inNum;
}

BigInteger::BigInteger(const string &inStr) {
  this->toLongNumber(inStr);
}

BigInteger &BigInteger::operator=(const BigInteger &other) {
  this->sign = other.sign;
  this->vectNum = other.vectNum;
  return *this;
}

BigInteger &BigInteger::operator=(int64_t inNum) {
  this->toLongNumber(inNum);
  return *this;
}

void BigInteger::changeZeroSign() {
  if (this->vectNum.size() == 1 && this->vectNum.front() == 0) {
    this->sign = false;
  }
}

BigInteger &BigInteger::operator+=(const BigInteger &other) {
  if ((!this->sign && !other.sign) || (this->sign && other.sign)) {
    this->vectNum = addCut(this->vectNum, other.vectNum);
  }

  else {
    if (::greater(this->vectNum, other.vectNum)) {
      this->vectNum = substract(this->vectNum, other.vectNum);
    } else {
      this->sign = !this->sign;
      this->vectNum = substract(other.vectNum, this->vectNum);
    }
  }

  this->changeZeroSign();
  return *this;
}

BigInteger &BigInteger::operator+=(int64_t inNum) {
  return *this += BigInteger(inNum);
}

BigInteger BigInteger::operator+(const BigInteger &other) const {
  BigInteger thisNum = *this;
  return thisNum += other;
}

BigInteger operator+(const BigInteger &other, int64_t inNum) {
  return BigInteger(inNum) + other;
}

BigInteger operator+(int64_t inNum, const BigInteger &other) {
  return BigInteger(inNum) + other;
}

BigInteger &BigInteger::operator-=(const BigInteger &other) {
  BigInteger otherNum = other;
  otherNum.sign = !otherNum.sign;
  return *this += otherNum;
}

BigInteger &BigInteger::operator-=(int64_t inNum) {
  return *this -= BigInteger(inNum);
}

BigInteger BigInteger::operator-(const BigInteger &other) const {
  BigInteger thisNum = *this;
  return thisNum -= other;
}

BigInteger operator-(const BigInteger &other, int64_t inNum) {
  return other - BigInteger(inNum);
}

BigInteger operator-(int64_t inNum, const BigInteger &other) {
  return BigInteger(inNum) - other;
}

BigInteger &BigInteger::operator*=(const BigInteger &other) {
  this->vectNum = multiply(this->vectNum, other.vectNum);
  this->sign = !((this->sign && other.sign) || (!this->sign && !other.sign));
  this->changeZeroSign();
  return *this;
}

BigInteger &BigInteger::operator*=(int64_t inNum) {
  return *this *= BigInteger(inNum);
}

BigInteger BigInteger::operator*(const BigInteger &other) const {
  BigInteger thisNum = *this;
  return thisNum *= other;
}

BigInteger operator*(const BigInteger &other, int64_t inNum) {
  return BigInteger(inNum) * other;
}

BigInteger operator*(int64_t inNum, const BigInteger &other) {
  return BigInteger(inNum) * other;
}

BigInteger &BigInteger::operator/=(const BigInteger &other) {
  if (other == 0) {
    throw domain_error("Div by zero");
  }
  if (*this == 0) {
    return *this;
  }
  if (::greater(other.vectNum, this->vectNum)) {
    *this = 0;
    return *this;
  }

  NumVector mod;
  this->vectNum = divide(this->vectNum, other.vectNum, mod);
  this->sign = !((this->sign && other.sign) || (!this->sign && !other.sign));

  this->changeZeroSign();
  return *this;
}

BigInteger &BigInteger::operator/=(int64_t inNum) {
  return *this /= BigInteger(inNum);
}

BigInteger BigInteger::operator/(const BigInteger &other) const {
  BigInteger thisNum = *this;
  return thisNum /= other;
}

BigInteger operator/(const BigInteger &other, int64_t inNum) {
  return other / BigInteger(inNum);
}

BigInteger operator/(int64_t inNum, const BigInteger &other) {
  return BigInteger(inNum) / other;
}

BigInteger &BigInteger::operator%=(const BigInteger &other) {
  if (other == 0) {
    throw domain_error("Div by zero");
  }
  if (*this == 0) {
    return *this;
  }
  if (::greater(other.vectNum, this->vectNum)) {
    return *this;
  }

  divide(this->vectNum, other.vectNum, this->vectNum);

  this->changeZeroSign();
  return *this;
}

BigInteger &BigInteger::operator%=(int64_t inNum) {
  return *this %= BigInteger(inNum);
}

BigInteger BigInteger::operator%(const BigInteger &other) const {
  BigInteger thisNum = *this;
  return thisNum %= other;
}

BigInteger operator%(const BigInteger &other, int64_t inNum) {
  return other % BigInteger(inNum);
}

BigInteger operator%(int64_t inNum, const BigInteger &other) {
  return BigInteger(inNum) % other;
}

BigInteger &BigInteger::operator++() {
  return *this += 1;
}

BigInteger &BigInteger::operator++(int) {
  *this += 1;
  return *this;
}

BigInteger &BigInteger::operator--() {
  *this -= 1;
  return *this;
}

BigInteger &BigInteger::operator--(int) {
  *this -= 1;
  return *this;
}

bool BigInteger::operator==(const BigInteger &other) const {
  if (this->sign != other.sign) {
    return false;
  }

  return equal(this->vectNum, other.vectNum);
}

bool operator==(const BigInteger &other, int64_t inNum) {
  return (other == BigInteger(inNum));
}

bool operator==(int64_t inNum, const BigInteger &other) {
  return (other == BigInteger(inNum));
}

bool BigInteger::operator!=(const BigInteger &other) const {
  return !(*this == other);
}

bool operator!=(const BigInteger &other, int64_t inNum) {
  return (other != BigInteger(inNum));
}

bool operator!=(int64_t inNum, const BigInteger &other) {
  return (other != BigInteger(inNum));
}

bool BigInteger::operator>(const BigInteger &other) const {
  if (!this->sign && other.sign) {
    return true;
  }
  if (this->sign && !other.sign) {
    return false;
  }

  if (this->sign && other.sign) {
    return ::greater(other.vectNum, this->vectNum);
  }

  return ::greater(this->vectNum, other.vectNum);
}

bool operator>(const BigInteger &other, int64_t inNum) {
  return (other > BigInteger(inNum));
}

bool operator>(int64_t inNum, const BigInteger &other) {
  return (BigInteger(inNum) > other);
}

bool BigInteger::operator>=(const BigInteger &other) const {
  return (*this == other || *this > other);
}

bool operator>=(const BigInteger &other, int64_t inNum) {
  return (other >= BigInteger(inNum));
}

bool operator>=(int64_t inNum, const BigInteger &other) {
  return (BigInteger(inNum) >= other);
}

bool BigInteger::operator<(const BigInteger &other) const {
  return !(*this >= other);
}

bool operator<(const BigInteger &other, int64_t inNum) {
  return !(other >= BigInteger(inNum));
}

bool operator<(int64_t inNum, const BigInteger &other) {
  return !(BigInteger(inNum) >= other);
}

bool BigInteger::operator<=(const BigInteger &other) const {
  return !(*this > other);
}

bool operator<=(const BigInteger &other, int64_t inNum) {
  return !(other > BigInteger(inNum));
}

bool operator<=(int64_t inNum, const BigInteger &other) {
  return !(BigInteger(inNum) > other);
}

size_t BigInteger::size() const {
  return (this->vectNum.size() - 1) * 9 + (to_string(this->vectNum.back())).size();
}

int64_t BigInteger::getBaseSize() {
  return BigInteger::baseSize;
}

int64_t BigInteger::getBase() {
  return BigInteger::base;
}

BigInteger &BigInteger::toLongNumber(const string &inStr) {
  if (inStr == "") {
    throw invalid_argument("BigInteger invalid input");
  }

  this->vectNum.clear();
  this->sign = false;

  size_t first = 0;
  if (inStr.front() == '-') {
    this->sign = true;
    ++first;
  }

  {
    auto iter = find_if(inStr.begin() + first, inStr.end(), [](char ch) { return !(ch - '0' >= 0 && ch - '0' <= 9); });
    if (iter != inStr.end()) {
      throw invalid_argument("BigInteger invalid input");
    }
  }

  auto iter = inStr.end();
  for (; distance(inStr.begin(), iter) > baseSize; iter -= baseSize) {
    this->vectNum.push_back(stoll(string(iter - baseSize, iter)));
  }
  this->vectNum.push_back(stoll(string(inStr.begin() + first, iter)));

  toSignificantDigits(this->vectNum);
  return *this;
}

BigInteger &BigInteger::toLongNumber(int64_t inNum) {
  return this->toLongNumber(to_string(inNum));
}

istream &operator>>(istream &in, BigInteger &other) {
  string str;
  in >> str;
  other = BigInteger(str);
  return in;
}

ostream &operator<<(ostream &out, const BigInteger &other) {
  out << other.toString();
  return out;
}

string BigInteger::toString() const {
  string str;

  for (size_t i = this->vectNum.size() - 1; i != SIZE_MAX; --i) {
    string tmp = to_string(this->vectNum[i]);
    tmp.insert(0, baseSize - tmp.size(), '0');
    str.insert(str.size(), tmp);
  }

  while (str.front() == '0') {
    str.erase(0, 1);
  }

  if (str.empty()) {
    str = "0";
  } else if (this->sign) {
    str.insert(0, 1, '-');
  }

  return str;
}

// Обертка над квадратным корнем в столбик, изменяет базу системы, в соответстие с алгоритмом
BigInteger sqrt(const BigInteger &inLnum) {
  if (inLnum < 0) {
    throw domain_error("sqrt out of range");
  }

  string str = inLnum.toString();
  BigInteger::baseSize = 2;
  BigInteger::base = 100;
  BigInteger lnum = BigInteger(str);

  BigInteger::baseSize = 1;
  BigInteger::base = 10;
  BigInteger res;
  res.vectNum = sqrt(lnum.vectNum);

  str = res.toString();
  BigInteger::baseSize = PRIMARY_BASE_SIZE;
  BigInteger::base = PRIMARY_BASE;

  return BigInteger(str);
}

// Приведение к значимым цифрам
inline void toSignificantDigits(NumVector &A) {
  size_t i = A.size() - 1;
  for (; i > 0; --i) {
    if (A[i] != 0) {
      break;
    }
  }
  A.resize(i + 1);
}

// Нахождение разряда перед первым ненулевым, начиная с младших разрядов
inline size_t numOfFirstZeros(const NumVector &A) {
  size_t i = 0;
  while (A[i] == 0) {
    ++i;
  }
  return i;
}

// Если число в данном разряде >= BASE, излишек прибавляется к следующему разряду
inline void toBasePositive(NumVector &A, size_t i) {
  if (A[i] >= BigInteger::getBase()) {
    A[i + 1] += A[i] / BigInteger::getBase();
    A[i] %= BigInteger::getBase();
  }
}

// Если число в данном разряде < 0, недостаток вычитается из следующего разряда
inline void toBaseNegative(NumVector &A, size_t i) {
  if (A[i] < 0) {
    --A[i + 1];
    A[i] += BigInteger::getBase();
  }
}

// Последовательное сравнение разрядов двух чисел (от старших к младшим)
inline bool equal(const NumVector &A, const NumVector &B) {
  if (A.size() != B.size()) {
    return false;
  }

  for (size_t i = A.size() - 1; i != SIZE_MAX; --i) {
    if (A[i] != B[i]) {
      return false;
    }
  }

  return true;
}

// Последовательное сравнение разрядов двух чисел (от старших к младшим)
inline bool greater(const NumVector &A, const NumVector &B) {
  if (A.size() > B.size()) {
    return true;
  }
  if (A.size() < B.size()) {
    return false;
  }

  for (size_t i = A.size() - 1; i != SIZE_MAX; --i) {
    if (A[i] > B[i]) {
      return true;
    }
    if (A[i] < B[i]) {
      return false;
    }
  }

  return false;
}

// Сложение в столбик, не приводит к значимым числам
inline NumVector add(const NumVector &A, const NumVector &B) {
  NumVector res = A;
  if (B.size() > res.size()) {
    res.resize(B.size(), 0);
  }
  res.push_back(0);

  for (size_t i = 0; i < B.size(); ++i) {
    res[i] += B[i];
    toBasePositive(res, i);
  }
  for (size_t i = B.size(); i < res.size(); ++i) {
    toBasePositive(res, i);
  }

  return res;
}

// Сложение с приведением к значимым цифрам
inline NumVector addCut(const NumVector &A, const NumVector &B) {
  NumVector res = add(A, B);
  toSignificantDigits(res);
  return res;
}

// Вычитание в столбик
inline NumVector substract(const NumVector &A, const NumVector &B) {
  NumVector res = A;

  for (size_t i = 0; i < B.size(); ++i) {
    res[i] -= B[i];
    toBaseNegative(res, i);
  }
  for (size_t i = B.size(); i < res.size(); ++i) {
    toBaseNegative(res, i);
  }

  toSignificantDigits(res);
  return res;
}

// Умножение на короткое число
inline NumVector shortMultiply(const NumVector &A, int64_t num) {
  NumVector res;
  res.resize(A.size() + 1, 0);

  for (size_t i = 0; i < A.size(); ++i) {
    res[i] += A[i] * num;
    toBasePositive(res, i);
  }

  toSignificantDigits(res);
  return res;
}

/*
  Умножение чисел в качестве многочленов.
  Каждый разряд первого числа умножается на каждый разряд второго числа.
  Не приводит к значимым числам.
*/
inline NumVector polynomialMultiply(const NumVector &A, const NumVector &B) {
  NumVector res;
  res.resize(A.size() + B.size(), 0);

  for (size_t i = 0; i < A.size(); ++i) {
    for (size_t j = 0; j < B.size(); ++j) {
      res[i + j] += A[i] * B[j];
      toBasePositive(res, i + j);
    }
  }

  return res;
}

/*
  Умножение чисел A на B методом Карацубы. Рекурсивно применяется, пока размер
  одного из чисел не станет равен KARATSUBA_CONST.

  A * B = p0 + p1 * BASE^m + p2 * BASE^2m,

  p0 = A0 * B0,
  p1 = (A0 + A1)(B0 + B1) - (p1 + p2),
  p2 = A1 * B1.

  A0 и B0 - первые половины соответсвующих чисел (разряды 0 — m),
  A1 и B1 - вторые половины соответсвующих чисел (разряды m — 2m).
*/
inline NumVector karatsubaMultiply(const NumVector &A, const NumVector &B) {
  if (A.size() < KARATSUBA_CUTOFF || B.size() < KARATSUBA_CUTOFF) {
    return polynomialMultiply(A, B);
  }

  size_t len = A.size() >> 1;

  NumVector A0(A.begin(), A.begin() + len);
  NumVector A1(A.begin() + len, A.end());

  NumVector B0(B.begin(), B.begin() + len);
  NumVector B1(B.begin() + len, B.end());

  NumVector p0 = karatsubaMultiply(A0, B0);
  NumVector p1 = karatsubaMultiply(add(A0, A1), add(B0, B1));
  NumVector p2 = karatsubaMultiply(A1, B1);

  p1 = substract(p1, add(p2, p0));

  p1.insert(p1.begin(), len, 0);
  p2.insert(p2.begin(), len << 1, 0);

  return add(add(p2, p1), p0);
}

// Умножение нулевый разрядов чисел
inline size_t multiplyZeros(NumVector &A, NumVector &B) {
  size_t numOfZerosA = numOfFirstZeros(A);
  size_t numOfZerosB = numOfFirstZeros(B);

  if (A.size() != 1) {
    A.erase(A.begin(), A.begin() + numOfZerosA);
  }
  if (B.size() != 1) {
    B.erase(B.begin(), B.begin() + numOfZerosB);
  }

  return numOfZerosA + numOfZerosB;
}

// Обертка над умножением Карацубы, добавление лидирующих нулей для приведения чисел к виду, требуемому алгоритмом
inline NumVector multiply(const NumVector &inA, const NumVector &inB) {
  NumVector A = inA, B = inB;
  size_t numOfZeros = multiplyZeros(A, B);

  if (A.size() < KARATSUBA_CUTOFF || B.size() < KARATSUBA_CUTOFF) {
    NumVector res = polynomialMultiply(A, B);
    res.insert(res.begin(), numOfZeros, 0);
    toSignificantDigits(res);
    return res;
  }

  size_t len = max(A.size(), B.size());
  if (len % 2 == 1) {
    ++len;
  }
  A.resize(len, 0);
  B.resize(len, 0);
  len >>= 1;

  NumVector res = karatsubaMultiply(A, B);
  res.insert(res.begin(), numOfZeros, 0);

  toSignificantDigits(res);
  return res;
}

// Деление на короткое
inline NumVector shortDivide(const NumVector &A, int64_t num) {
  NumVector res = A;

  for (size_t i = res.size() - 1; i > 0; --i) {
    res[i - 1] += (res[i] % num) * BigInteger::getBase();
    res[i] /= num;
  }

  res.front() /= num;

  toSignificantDigits(res);
  return res;
}

// Деление на короткое с получением остатка
inline NumVector shortDivide(const NumVector &A, int64_t num, NumVector &mod) {
  NumVector res = A;

  for (size_t i = res.size() - 1; i > 0; --i) {
    res[i - 1] += (res[i] % num) * BigInteger::getBase();
    res[i] /= num;
  }

  mod = NumVector{res.front() % num};
  res.front() /= num;

  toSignificantDigits(res);
  return res;
}

// Сокращение нулевые разрядов чисел
inline void divideZeros(NumVector &A, NumVector &B) {
  size_t numOfZeros = min(numOfFirstZeros(A), numOfFirstZeros(B));
  if (A.size() != 1 && B.size() != 1 && numOfZeros != 0) {
    A.erase(A.begin(), A.begin() + numOfZeros);
    B.erase(B.begin(), B.begin() + numOfZeros);
  }
}

// Деление A на B с помощью бинарного поиска
inline NumVector binsearchDivide(const NumVector &A, const NumVector &B, NumVector &left, NumVector &right) {
  NumVector mid, one = NumVector{1};
  while (::greater(substract(right, left), one)) {
    mid = shortDivide(addCut(left, right), 2);
    NumVector mult = multiply(B, mid);
    if (::greater(mult, A)) {
      right = mid;
    } else {
      left = mid;
    }
  }

  if (::greater(left, right)) {
    swap(left, right);
  }

  NumVector res, mult = multiply(B, right);
  if (::greater(A, mult) || equal(A, mult)) {
    res = right;
  } else {
    res = left;
  }

  return res;
}

/*
  Обертка над делением бинарным поиском.
  Нижняя и верхняя границы определяются следующим образом: N = A/(B.back() +- 1). N - соответсвующая граница B.back() —
  старший разряд числа B. Затем отбрасываются (N.size() + B.size()) первых разрядов.
*/
inline NumVector divide(const NumVector &inA, const NumVector &inB, NumVector &mod) {
  if (inB.size() == 1) {
    return shortDivide(inA, inB.front(), mod);
  }

  NumVector A = inA;
  NumVector B = inB;
  divideZeros(A, B);

  NumVector left, right;
  left = shortDivide(A, B.back() + 1);

  if (B.back() != 1) {
    right = shortDivide(A, B.back() - 1);
  } else {
    right = A;
    right.back() = BigInteger::getBase() - 1;
  }

  left.erase(left.begin(), left.begin() + B.size() - 1);
  right.erase(right.begin(), right.begin() + B.size() - 1);

  if (equal(right, left)) {
    mod = substract(inA, multiply(inB, left));
    return left;
  }

  NumVector res = binsearchDivide(A, B, left, right);
  mod = substract(inA, multiply(inB, res));

  return res;
}

/*
  Вычисление квадратного корня A в столбик.

  1. Делим число A на грани по две цифры в каждой грани справа налево (от младших разрядов к старшим).

  2. Извлечение начинается слева направо. Подбираем число, квадрат которого не превосходит числа, стоящего в первой
  грани. Это число возводим в квадрат и записывает под числом, стоящим в первой грани.

  3. Находим разность между числом, стоящим в первой грани, и квадратом подобранного первого числа.

  4. К получившейся разности сносим следующую грань, полученное число будет делимым. Образовываем делитель. Первую
  подобранную цифру ответа умножаем на 2, получаем число десятков делителя, а число единиц должно быть таким, чтобы его
  произведение на весь делитель не превосходило делимого. Подобранную цифру записываем в ответ. Подбор осуществляется с
  помощью бинарного поиска.

  5.К получившейся разности сносим следующую грань и выполняем действия по алгоритму.
*/
inline NumVector sqrt(const NumVector &A) {
  NumVector res, diff;
  res.push_back((int64_t)sqrt(A.back()));

  {
    int64_t num = A.back() - res.front() * res.front();
    diff.push_back(num % 10);
    if (num >= 10) {
      diff.push_back(num / 10);
    }
  }

  for (size_t i = A.size() - 2; i != SIZE_MAX; --i) {
    NumVector mod;
    mod.push_back(A[i] % 10);
    mod.push_back(A[i] / 10);
    mod.insert(mod.end(), diff.begin(), diff.end());
    toSignificantDigits(mod);

    NumVector resI{0};
    NumVector doubledRes = shortMultiply(res, 2);
    resI.insert(resI.end(), doubledRes.begin(), doubledRes.end());

    int64_t left = 0, right = 10;

    while (left < right) {
      resI.front() = (left + right) >> 1;
      doubledRes = shortMultiply(resI, resI.front());

      if (::greater(doubledRes, mod)) {
        right = resI.front();
      }

      else {
        left = resI.front() + 1;
      }
    }

    resI.front() = right - 1;

    diff = substract(mod, shortMultiply(resI, resI.front()));
    res.insert(res.begin(), resI.front());
  }

  return res;
}
