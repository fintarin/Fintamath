/*
  Длинное число хранится в виде вектора, где разряды идут от младших к старшим. База системы (INT_BASE) = 10^9.
*/
#include "single_entities/terms/numbers/Integer.hpp"

#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;
using IntVector = vector<int64_t>;

constexpr int8_t INT_BASE_SIZE = 9;
constexpr int64_t INT_BASE = 1000000000;
constexpr int64_t KARATSUBA_CUTOFF = 64;

static IntVector toIntVector(const string &strVal, int64_t baseSize);
static bool canConvert(const std::string &strVal);
static string toString(const IntVector &intVect, int64_t baseSize);

static int64_t firstZeroNum(const IntVector &rhs);

static void toSignificantDigits(IntVector &rhs);
static void toBasePositive(IntVector &rhs, size_t index, int64_t base);
static void toBaseNegative(IntVector &rhs, size_t index, int64_t base);

static bool equal(const IntVector &lhs, const IntVector &rhs);
static bool less(const IntVector &lhs, const IntVector &rhs);
static bool greater(const IntVector &lhs, const IntVector &rhs);
static bool lessEqual(const IntVector &lhs, const IntVector &rhs);
static bool greaterEqual(const IntVector &lhs, const IntVector &rhs);

static IntVector add(const IntVector &lhs, const IntVector &rhs, int64_t base);
static IntVector addToSignificantDigits(const IntVector &lhs, const IntVector &rhs, int64_t base);

static IntVector substract(const IntVector &lhs, const IntVector &rhs, int64_t base);

static IntVector shortMultiply(const IntVector &lhs, int64_t rhs, int64_t base);
static IntVector polynomialMultiply(const IntVector &lhs, const IntVector &rhs, int64_t base);
static IntVector karatsubaMultiply(const IntVector &lhs, const IntVector &rhs, int64_t base);
static size_t zerosMultiply(IntVector &lhs, IntVector &rhs);
static IntVector multiply(const IntVector &lhs, const IntVector &rhs, int64_t base);

static IntVector shortDivide(const IntVector &lhs, int64_t rhs, int64_t base);
static IntVector shortDivide(const IntVector &lhs, int64_t rhs, IntVector &modVal, int64_t base);
static void zerosDivide(IntVector &lhs, IntVector &rhs);
static IntVector binsearchDivide(const IntVector &lhs, const IntVector &rhs, IntVector &left, IntVector &right,
                                 int64_t base);
static IntVector divide(const IntVector &lhs, const IntVector &rhs, IntVector &modVal, int64_t base);

static IntVector sqrt(const IntVector &rhs);

Integer::Integer(const string &strVal) {
  if (strVal.empty()) {
    throw invalid_argument("Integer invalid input");
  }

  this->intVect.clear();
  this->sign = false;

  int64_t firstDigitNum = 0;
  if (strVal.front() == '-') {
    this->sign = true;
    ++firstDigitNum;
  }

  if (!canConvert(strVal.substr(firstDigitNum))) {
    throw invalid_argument("Integer invalid input");
  }

  this->intVect = toIntVector(strVal.substr(firstDigitNum), INT_BASE_SIZE);
}

Integer::Integer(int64_t val) : Integer(to_string(val)) {
}

Integer &Integer::operator=(int64_t rhs) {
  return *this = Integer(rhs);
}

Integer &Integer::operator+=(const Integer &rhs) {
  if ((!this->sign && !rhs.sign) || (this->sign && rhs.sign)) {
    this->intVect = addToSignificantDigits(this->intVect, rhs.intVect, INT_BASE);
  }

  else {
    if (::greater(this->intVect, rhs.intVect)) {
      this->intVect = substract(this->intVect, rhs.intVect, INT_BASE);
    } else {
      this->sign = !this->sign;
      this->intVect = substract(rhs.intVect, this->intVect, INT_BASE);
    }
  }

  this->fixZero();
  return *this;
}

Integer &Integer::operator+=(int64_t rhs) {
  return *this += Integer(rhs);
}

Integer Integer::operator+(const Integer &rhs) const {
  Integer lhs = *this;
  return lhs += rhs;
}

Integer Integer::operator+(int64_t rhs) const {
  return *this + Integer(rhs);
}

Integer operator+(int64_t lhs, const Integer &rhs) {
  return Integer(lhs) + rhs;
}

Integer &Integer::operator-=(const Integer &rhs) {
  Integer tmpRhs = rhs;
  tmpRhs.sign = !tmpRhs.sign;
  return *this += tmpRhs;
}

Integer &Integer::operator-=(int64_t rhs) {
  return *this -= Integer(rhs);
}

Integer Integer::operator-(const Integer &rhs) const {
  Integer lhs = *this;
  return lhs -= rhs;
}

Integer Integer::operator-(int64_t rhs) const {
  return *this - Integer(rhs);
}

Integer operator-(int64_t lhs, const Integer &rhs) {
  return Integer(lhs) - rhs;
}

Integer &Integer::operator*=(const Integer &rhs) {
  this->intVect = multiply(this->intVect, rhs.intVect, INT_BASE);
  this->sign = !((this->sign && rhs.sign) || (!this->sign && !rhs.sign));
  this->fixZero();
  return *this;
}

Integer &Integer::operator*=(int64_t rhs) {
  return *this *= Integer(rhs);
}

Integer Integer::operator*(const Integer &rhs) const {
  Integer lhs = *this;
  return lhs *= rhs;
}

Integer Integer::operator*(int64_t rhs) const {
  return *this * Integer(rhs);
}

Integer operator*(int64_t lhs, const Integer &rhs) {
  return Integer(lhs) * rhs;
}

Integer &Integer::operator/=(const Integer &rhs) {
  if (rhs == 0) {
    throw domain_error("Div by zero");
  }
  if (*this == 0) {
    return *this;
  }
  if (::greater(rhs.intVect, this->intVect)) {
    *this = 0;
    return *this;
  }

  IntVector modVal;
  this->intVect = divide(this->intVect, rhs.intVect, modVal, INT_BASE);
  this->sign = !((this->sign && rhs.sign) || (!this->sign && !rhs.sign));

  this->fixZero();
  return *this;
}

Integer &Integer::operator/=(int64_t rhs) {
  return *this /= Integer(rhs);
}

Integer Integer::operator/(const Integer &rhs) const {
  Integer lhs = *this;
  return lhs /= rhs;
}

Integer Integer::operator/(int64_t rhs) const {
  return *this / Integer(rhs);
}

Integer operator/(int64_t lhs, const Integer &rhs) {
  return Integer(lhs) / rhs;
}

Integer &Integer::operator%=(const Integer &rhs) {
  if (rhs == 0) {
    throw domain_error("Div by zero");
  }
  if (*this == 0) {
    return *this;
  }
  if (::greater(rhs.intVect, this->intVect)) {
    return *this;
  }

  divide(this->intVect, rhs.intVect, this->intVect, INT_BASE);

  this->fixZero();
  return *this;
}

Integer &Integer::operator%=(int64_t rhs) {
  return *this %= Integer(rhs);
}

Integer Integer::operator%(const Integer &rhs) const {
  Integer lhs = *this;
  return lhs %= rhs;
}

Integer Integer::operator%(int64_t rhs) const {
  return *this % Integer(rhs);
}

Integer operator%(int64_t lhs, const Integer &rhs) {
  return Integer(lhs) % rhs;
}

Integer &Integer::operator++() {
  return *this += 1;
}

Integer Integer::operator++(int) {
  Integer val = *this;
  *this += 1;
  return val;
}

Integer &Integer::operator--() {
  *this -= 1;
  return *this;
}

Integer Integer::operator--(int) {
  Integer val = *this;
  *this -= 1;
  return val;
}

Integer Integer::operator+() const {
  return *this;
}

Integer Integer::operator-() const {
  Integer val = *this;
  val.sign = !val.sign;
  return val;
}

bool Integer::operator==(const Integer &rhs) const {
  if (this->sign != rhs.sign) {
    return false;
  }
  return equal(this->intVect, rhs.intVect);
}

bool Integer::operator==(int64_t rhs) const {
  return *this == Integer(rhs);
}

bool operator==(int64_t lhs, const Integer &rhs) {
  return Integer(lhs) == rhs;
}

bool Integer::operator!=(const Integer &rhs) const {
  return !(*this == rhs);
}

bool Integer::operator!=(int64_t rhs) const {
  return !(*this == rhs);
}

bool operator!=(int64_t lhs, const Integer &rhs) {
  return !(lhs == rhs);
}

bool Integer::operator<(const Integer &rhs) const {
  if (!this->sign && rhs.sign) {
    return false;
  }
  if (this->sign && !rhs.sign) {
    return true;
  }

  if (this->sign && rhs.sign) {
    return ::less(rhs.intVect, this->intVect);
  }

  return ::less(this->intVect, rhs.intVect);
}

bool Integer::operator<(int64_t rhs) const {
  return *this < Integer(rhs);
}

bool operator<(int64_t lhs, const Integer &rhs) {
  return Integer(lhs) < rhs;
}

bool Integer::operator>(const Integer &rhs) const {
  if (!this->sign && rhs.sign) {
    return true;
  }
  if (this->sign && !rhs.sign) {
    return false;
  }

  if (this->sign && rhs.sign) {
    return ::greater(rhs.intVect, this->intVect);
  }

  return ::greater(this->intVect, rhs.intVect);
}

bool Integer::operator>(int64_t rhs) const {
  return *this > Integer(rhs);
}

bool operator>(int64_t lhs, const Integer &rhs) {
  return Integer(lhs) > rhs;
}

bool Integer::operator<=(const Integer &rhs) const {
  if (!this->sign && rhs.sign) {
    return false;
  }
  if (this->sign && !rhs.sign) {
    return true;
  }

  if (this->sign && rhs.sign) {
    return ::lessEqual(rhs.intVect, this->intVect);
  }

  return ::lessEqual(this->intVect, rhs.intVect);
}

bool Integer::operator<=(int64_t rhs) const {
  return *this <= Integer(rhs);
}

bool operator<=(int64_t lhs, const Integer &rhs) {
  return Integer(lhs) <= rhs;
}

bool Integer::operator>=(const Integer &rhs) const {
  if (!this->sign && rhs.sign) {
    return true;
  }
  if (this->sign && !rhs.sign) {
    return false;
  }

  if (this->sign && rhs.sign) {
    return ::greaterEqual(rhs.intVect, this->intVect);
  }

  return ::greaterEqual(this->intVect, rhs.intVect);
}

bool Integer::operator>=(int64_t rhs) const {
  return *this >= Integer(rhs);
}

bool operator>=(int64_t lhs, const Integer &rhs) {
  return Integer(lhs) >= rhs;
}

istream &operator>>(istream &in, Integer &rhs) {
  string strVal;
  in >> strVal;
  rhs = Integer(strVal);
  return in;
}

ostream &operator<<(ostream &out, const Integer &rhs) {
  return out << rhs.toString();
}

size_t Integer::size() const {
  return (this->intVect.size() - 1) * INT_BASE_SIZE + (to_string(this->intVect.back())).size();
}

string Integer::toString() const {
  string strVal = ::toString(this->intVect, INT_BASE_SIZE);
  if (strVal != "0" && this->sign) {
    strVal.insert(0, 1, '-');
  }
  return strVal;
}

// Обертка над квадратным корнем в столбик, изменяет базу системы, в соответстие с алгоритмом
Integer sqrt(const Integer &rhs) {
  if (rhs < 0) {
    throw domain_error("sqrt out of range");
  }
  auto intVect = toIntVector(rhs.toString(), 2);
  return Integer(toString(sqrt(intVect), 1));
}

void Integer::fixZero() {
  if (this->intVect.size() == 1 && this->intVect.front() == 0) {
    this->sign = false;
  }
}

static IntVector toIntVector(const string &strVal, int64_t baseSize) {
  IntVector intVect;
  auto iter = strVal.end();
  for (; distance(strVal.begin(), iter) > baseSize; iter -= baseSize) {
    intVect.push_back(stoll(string(iter - baseSize, iter)));
  }
  intVect.push_back(stoll(string(strVal.begin(), iter)));
  toSignificantDigits(intVect);
  return intVect;
}

static bool canConvert(const std::string &strVal) {
  const int64_t firstDigit = 0;
  const int64_t lastDigit = 9;
  return all_of(strVal.begin(), strVal.end(), [](auto ch) { return ch - '0' >= firstDigit && ch - '0' <= lastDigit; });
}

static string toString(const IntVector &intVect, int64_t baseSize) {
  string strVal;
  for (size_t i = intVect.size() - 1; i != SIZE_MAX; --i) {
    string tmp = to_string(intVect[i]);
    tmp.insert(0, baseSize - tmp.size(), '0');
    strVal.insert(strVal.size(), tmp);
  }
  return strVal;
}

// Нахождение разряда перед первым ненулевым, начиная с младших разрядов
static int64_t firstZeroNum(const IntVector &rhs) {
  int64_t num = 0;
  while (rhs[num] == 0) {
    ++num;
  }
  return num;
}

// Приведение к значимым цифрам
static void toSignificantDigits(IntVector &rhs) {
  size_t i = rhs.size() - 1;
  for (; i > 0; --i) {
    if (rhs[i] != 0) {
      break;
    }
  }
  rhs.resize(i + 1);
}

// Если число в данном разряде >= INT_BASE, излишек прибавляется к следующему разряду
static void toBasePositive(IntVector &rhs, size_t index, int64_t base) {
  if (rhs[index] >= base) {
    rhs[index + 1] += rhs[index] / base;
    rhs[index] %= base;
  }
}

// Если число в данном разряде < 0, недостаток вычитается из следующего разряда
static void toBaseNegative(IntVector &rhs, size_t index, int64_t base) {
  if (rhs[index] < 0) {
    --rhs[index + 1];
    rhs[index] += base;
  }
}

// Последовательное сравнение разрядов двух чисел (от старших к младшим)
static bool equal(const IntVector &lhs, const IntVector &rhs) {
  if (lhs.size() != rhs.size()) {
    return false;
  }

  for (size_t i = lhs.size() - 1; i != SIZE_MAX; --i) {
    if (lhs[i] != rhs[i]) {
      return false;
    }
  }

  return true;
}

static bool less(const IntVector &lhs, const IntVector &rhs) {
  if (lhs.size() > rhs.size()) {
    return false;
  }
  if (lhs.size() < rhs.size()) {
    return true;
  }

  for (size_t i = lhs.size() - 1; i != SIZE_MAX; --i) {
    if (lhs[i] > rhs[i]) {
      return false;
    }
    if (lhs[i] < rhs[i]) {
      return true;
    }
  }

  return false;
}

static bool greater(const IntVector &lhs, const IntVector &rhs) {
  if (lhs.size() > rhs.size()) {
    return true;
  }
  if (lhs.size() < rhs.size()) {
    return false;
  }

  for (size_t i = lhs.size() - 1; i != SIZE_MAX; --i) {
    if (lhs[i] > rhs[i]) {
      return true;
    }
    if (lhs[i] < rhs[i]) {
      return false;
    }
  }

  return false;
}

static bool lessEqual(const IntVector &lhs, const IntVector &rhs) {
  if (lhs.size() > rhs.size()) {
    return false;
  }
  if (lhs.size() < rhs.size()) {
    return true;
  }

  for (size_t i = lhs.size() - 1; i != SIZE_MAX; --i) {
    if (lhs[i] > rhs[i]) {
      return false;
    }
    if (lhs[i] < rhs[i]) {
      return true;
    }
  }

  return true;
}

static bool greaterEqual(const IntVector &lhs, const IntVector &rhs) {
  if (lhs.size() > rhs.size()) {
    return true;
  }
  if (lhs.size() < rhs.size()) {
    return false;
  }

  for (size_t i = lhs.size() - 1; i != SIZE_MAX; --i) {
    if (lhs[i] > rhs[i]) {
      return true;
    }
    if (lhs[i] < rhs[i]) {
      return false;
    }
  }

  return true;
}

// Сложение в столбик, не приводит к значимым числам
static IntVector add(const IntVector &lhs, const IntVector &rhs, int64_t base) {
  IntVector val = lhs;
  if (rhs.size() > val.size()) {
    val.resize(rhs.size(), 0);
  }
  val.push_back(0);

  for (size_t i = 0; i < rhs.size(); ++i) {
    val[i] += rhs[i];
    toBasePositive(val, i, base);
  }
  for (size_t i = rhs.size(); i < val.size(); ++i) {
    toBasePositive(val, i, base);
  }

  return val;
}

// Сложение с приведением к значимым цифрам
static IntVector addToSignificantDigits(const IntVector &lhs, const IntVector &rhs, int64_t base) {
  IntVector val = add(lhs, rhs, base);
  toSignificantDigits(val);
  return val;
}

// Вычитание в столбик
static IntVector substract(const IntVector &lhs, const IntVector &rhs, int64_t base) {
  IntVector val = lhs;

  for (size_t i = 0; i < rhs.size(); ++i) {
    val[i] -= rhs[i];
    toBaseNegative(val, i, base);
  }
  for (size_t i = rhs.size(); i < val.size(); ++i) {
    toBaseNegative(val, i, base);
  }

  toSignificantDigits(val);
  return val;
}

// Умножение на короткое число
static IntVector shortMultiply(const IntVector &lhs, int64_t rhs, int64_t base) {
  IntVector val;
  val.resize(lhs.size() + 1, 0);

  for (size_t i = 0; i < lhs.size(); ++i) {
    val[i] += lhs[i] * rhs;
    toBasePositive(val, i, base);
  }

  toSignificantDigits(val);
  return val;
}

/*
  Умножение чисел в качестве многочленов.
  Каждый разряд первого числа умножается на каждый разряд второго числа.
  Не приводит к значимым числам.
*/
static IntVector polynomialMultiply(const IntVector &lhs, const IntVector &rhs, int64_t base) {
  IntVector res;
  res.resize(lhs.size() + rhs.size(), 0);

  for (size_t i = 0; i < lhs.size(); ++i) {
    for (size_t j = 0; j < rhs.size(); ++j) {
      res[i + j] += lhs[i] * rhs[j];
      toBasePositive(res, i + j, base);
    }
  }

  return res;
}

/*
  Умножение чисел A на B методом Карацубы. Рекурсивно применяется, пока размер
  одного из чисел не станет равен KARATSUBA_CONST.

  A * B = p0 + p1 * INT_BASE^m + p2 * INT_BASE^2m,

  p0 = A0 * B0,
  p1 = (A0 + A1)(B0 + B1) - (p1 + p2),
  p2 = A1 * B1.

  A0 и B0 - первые половины соответсвующих чисел (разряды 0 — m),
  A1 и B1 - вторые половины соответсвующих чисел (разряды m — 2m).
*/
static IntVector karatsubaMultiply(const IntVector &lhs, const IntVector &rhs, int64_t base) {
  if (lhs.size() < KARATSUBA_CUTOFF || rhs.size() < KARATSUBA_CUTOFF) {
    return polynomialMultiply(lhs, rhs, base);
  }

  int64_t mid = (int64_t)lhs.size() / 2;

  IntVector lhsHalf1(lhs.begin(), lhs.begin() + mid);
  IntVector lhsHalf2(lhs.begin() + mid, lhs.end());

  IntVector rhsHalf1(rhs.begin(), rhs.begin() + mid);
  IntVector rhsHalf2(rhs.begin() + mid, rhs.end());

  IntVector coeff1 = karatsubaMultiply(lhsHalf1, rhsHalf1, base);
  IntVector coeff2 = karatsubaMultiply(add(lhsHalf1, lhsHalf2, base), add(rhsHalf1, rhsHalf2, base), base);
  IntVector coeff3 = karatsubaMultiply(lhsHalf2, rhsHalf2, base);

  coeff2 = substract(coeff2, add(coeff3, coeff1, base), base);

  coeff2.insert(coeff2.begin(), mid, 0);
  coeff3.insert(coeff3.begin(), mid * 2, 0);

  return add(add(coeff3, coeff2, base), coeff1, base);
}

// Умножение нулевый разрядов чисел
static size_t zerosMultiply(IntVector &lhs, IntVector &rhs) {
  int64_t lhsZerosNum = firstZeroNum(lhs);
  int64_t rhsZerosNum = firstZeroNum(rhs);

  if (lhs.size() != 1) {
    lhs.erase(lhs.begin(), lhs.begin() + lhsZerosNum);
  }
  if (rhs.size() != 1) {
    rhs.erase(rhs.begin(), rhs.begin() + rhsZerosNum);
  }

  return lhsZerosNum + rhsZerosNum;
}

// Обертка над умножением Карацубы, добавление лидирующих нулей для приведения чисел к виду, требуемому алгоритмом
static IntVector multiply(const IntVector &lhs, const IntVector &rhs, int64_t base) {
  IntVector tmpLhs = lhs;
  IntVector tmpRhs = rhs;
  size_t zerosNum = zerosMultiply(tmpLhs, tmpRhs);

  if (tmpLhs.size() < KARATSUBA_CUTOFF || tmpRhs.size() < KARATSUBA_CUTOFF) {
    IntVector val = polynomialMultiply(tmpLhs, tmpRhs, base);
    val.insert(val.begin(), zerosNum, 0);
    toSignificantDigits(val);
    return val;
  }

  size_t maxSize = max(tmpLhs.size(), tmpRhs.size());
  if (maxSize % 2 == 1) {
    ++maxSize;
  }
  tmpLhs.resize(maxSize, 0);
  tmpRhs.resize(maxSize, 0);
  maxSize /= 2;

  IntVector val = karatsubaMultiply(tmpLhs, tmpRhs, base);
  val.insert(val.begin(), zerosNum, 0);

  toSignificantDigits(val);
  return val;
}

// Деление на короткое
static IntVector shortDivide(const IntVector &lhs, int64_t rhs, int64_t base) {
  IntVector val = lhs;

  for (size_t i = val.size() - 1; i > 0; --i) {
    val[i - 1] += (val[i] % rhs) * base;
    val[i] /= rhs;
  }
  val.front() /= rhs;

  toSignificantDigits(val);
  return val;
}

// Деление на короткое с получением остатка
static IntVector shortDivide(const IntVector &lhs, int64_t rhs, IntVector &modVal, int64_t base) {
  IntVector val = lhs;

  for (size_t i = val.size() - 1; i > 0; --i) {
    val[i - 1] += (val[i] % rhs) * base;
    val[i] /= rhs;
  }
  modVal = IntVector{val.front() % rhs};
  val.front() /= rhs;

  toSignificantDigits(val);
  return val;
}

// Сокращение нулевые разрядов чисел
static void zerosDivide(IntVector &lhs, IntVector &rhs) {
  int64_t zerosNum = min(firstZeroNum(lhs), firstZeroNum(rhs));
  if (lhs.size() != 1 && rhs.size() != 1 && zerosNum != 0) {
    lhs.erase(lhs.begin(), lhs.begin() + zerosNum);
    rhs.erase(rhs.begin(), rhs.begin() + zerosNum);
  }
}

// Деление A на B с помощью бинарного поиска
static IntVector binsearchDivide(const IntVector &lhs, const IntVector &rhs, IntVector &left, IntVector &right,
                                 int64_t base) {
  IntVector mid;
  while (::greater(substract(right, left, base), IntVector{1})) {
    mid = shortDivide(addToSignificantDigits(left, right, base), 2, base);
    IntVector multVal = multiply(rhs, mid, base);
    if (::greater(multVal, lhs)) {
      right = mid;
    } else {
      left = mid;
    }
  }

  if (::greater(left, right)) {
    swap(left, right);
  }

  IntVector val;

  IntVector multVal = multiply(rhs, right, base);
  if (::greater(lhs, multVal) || equal(lhs, multVal)) {
    val = right;
  } else {
    val = left;
  }

  return val;
}

/*
  Обертка над делением бинарным поиском.
  Нижняя и верхняя границы определяются следующим образом: N = A/(B.back() +- 1). N - соответсвующая граница B.back() —
  старший разряд числа B. Затем отбрасываются (N.size() + B.size()) первых разрядов.
*/
static IntVector divide(const IntVector &lhs, const IntVector &rhs, IntVector &modVal, int64_t base) {
  if (rhs.size() == 1) {
    return shortDivide(lhs, rhs.front(), modVal, base);
  }

  IntVector tmpLhs = lhs;
  IntVector tmpRhs = rhs;
  zerosDivide(tmpLhs, tmpRhs);

  IntVector left;
  IntVector right;
  left = shortDivide(tmpLhs, tmpRhs.back() + 1, base);

  if (tmpRhs.back() != 1) {
    right = shortDivide(tmpLhs, tmpRhs.back() - 1, base);
  } else {
    right = tmpLhs;
    right.back() = INT_BASE - 1;
  }

  left.erase(left.begin(), left.begin() + (int64_t)tmpRhs.size() - 1);
  right.erase(right.begin(), right.begin() + (int64_t)tmpRhs.size() - 1);

  if (equal(right, left)) {
    modVal = substract(lhs, multiply(rhs, left, base), base);
    return left;
  }

  IntVector val = binsearchDivide(tmpLhs, tmpRhs, left, right, base);
  modVal = substract(lhs, multiply(rhs, val, base), base);
  return val;
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
static IntVector sqrt(const IntVector &rhs) {
  const int64_t base = 10;

  IntVector val;
  IntVector diff;
  val.push_back((int64_t)sqrt(rhs.back()));

  {
    int64_t tmpVal = rhs.back() - val.front() * val.front();
    diff.push_back(tmpVal % base);
    if (tmpVal >= base) {
      diff.push_back(tmpVal / base);
    }
  }

  for (size_t i = rhs.size() - 2; i != SIZE_MAX; --i) {
    IntVector modVal;
    modVal.push_back(rhs[i] % base);
    modVal.push_back(rhs[i] / base);
    modVal.insert(modVal.end(), diff.begin(), diff.end());
    toSignificantDigits(modVal);

    IntVector intVect{0};
    IntVector doubledRes = shortMultiply(val, 2, base);
    intVect.insert(intVect.end(), doubledRes.begin(), doubledRes.end());

    int64_t left = 0;
    int64_t right = base;

    while (left < right) {
      intVect.front() = (left + right) / 2;
      doubledRes = shortMultiply(intVect, intVect.front(), base);

      if (::greater(doubledRes, modVal)) {
        right = intVect.front();
      }

      else {
        left = intVect.front() + 1;
      }
    }

    intVect.front() = right - 1;

    diff = substract(modVal, shortMultiply(intVect, intVect.front(), base), base);
    val.insert(val.begin(), intVect.front());
  }

  return val;
}
