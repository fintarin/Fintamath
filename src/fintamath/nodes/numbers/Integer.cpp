#include "fintamath/nodes/numbers/Integer.hpp"

#include <algorithm>
#include <cmath>
#include <stdexcept>

namespace fintamath {
  using IntVector = std::vector<int64_t>;

  constexpr int8_t INT_BASE_SIZE = 9;
  constexpr int64_t INT_BASE = 1000000000;
  constexpr int64_t KARATSUBA_CUTOFF = 64;

  IntVector toIntVector(const std::string_view &str, int64_t baseSize);
  bool canConvert(const std::string_view &str);
  std::string toString(const IntVector &intVect, int64_t baseSize);

  int64_t firstZeroNum(const IntVector &rhs);

  void toSignificantDigits(IntVector &rhs);
  void toBasePositive(IntVector &rhs, size_t pos, int64_t base);
  void toBaseNegative(IntVector &rhs, size_t pos, int64_t base);

  bool equal(const IntVector &lhs, const IntVector &rhs);
  bool less(const IntVector &lhs, const IntVector &rhs);
  bool greater(const IntVector &lhs, const IntVector &rhs);
  bool lessEqual(const IntVector &lhs, const IntVector &rhs);
  bool greaterEqual(const IntVector &lhs, const IntVector &rhs);

  IntVector add(const IntVector &lhs, const IntVector &rhs, int64_t base);
  IntVector addToSignificantDigits(const IntVector &lhs, const IntVector &rhs, int64_t base);

  IntVector substract(const IntVector &lhs, const IntVector &rhs, int64_t base);

  IntVector shortMultiply(const IntVector &lhs, int64_t rhs, int64_t base);
  IntVector polynomialMultiply(const IntVector &lhs, const IntVector &rhs, int64_t base);
  IntVector karatsubaMultiply(const IntVector &lhs, const IntVector &rhs, int64_t base);
  size_t zerosMultiply(IntVector &lhs, IntVector &rhs);
  IntVector multiply(const IntVector &lhs, const IntVector &rhs, int64_t base);

  IntVector shortDivide(const IntVector &lhs, int64_t rhs, int64_t base);
  IntVector shortDivide(const IntVector &lhs, int64_t rhs, IntVector &modVal, int64_t base);
  void zerosDivide(IntVector &lhs, IntVector &rhs);
  IntVector binsearchDivide(const IntVector &lhs, const IntVector &rhs, IntVector &left, IntVector &right,
                            int64_t base);
  IntVector divide(const IntVector &lhs, const IntVector &rhs, IntVector &modVal, int64_t base);

  IntVector sqrt(const IntVector &rhs);
  void getSqrtDiff(const IntVector &rhs, const int64_t &base, IntVector &val, IntVector &diff);

  Integer::Integer(const std::string_view &str) {
    if (str.empty()) {
      throw std::invalid_argument("Integer invalid input");
    }

    intVect.clear();
    sign = false;

    int64_t firstDigitNum = 0;
    if (str.front() == '-') {
      sign = true;
      firstDigitNum++;
    }

    if (!canConvert(str.substr(firstDigitNum))) {
      throw std::invalid_argument("Integer invalid input");
    }

    intVect = toIntVector(str.substr(firstDigitNum), INT_BASE_SIZE);
  }

  Integer::Integer(int64_t val) : Integer(std::to_string(val)) {
  }

  Integer &Integer::operator=(int64_t rhs) {
    return *this = Integer(rhs);
  }

  Integer &Integer::operator+=(const Integer &rhs) {
    if ((!sign && !rhs.sign) || (sign && rhs.sign)) {
      intVect = addToSignificantDigits(intVect, rhs.intVect, INT_BASE);
    }

    else {
      if (greater(intVect, rhs.intVect)) {
        intVect = substract(intVect, rhs.intVect, INT_BASE);
      } else {
        sign = !sign;
        intVect = substract(rhs.intVect, intVect, INT_BASE);
      }
    }

    fixZero();
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
    intVect = multiply(intVect, rhs.intVect, INT_BASE);
    sign = !((sign && rhs.sign) || (!sign && !rhs.sign));
    fixZero();
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
      throw std::domain_error("Div by zero");
    }
    if (*this == 0) {
      return *this;
    }
    if (greater(rhs.intVect, intVect)) {
      *this = 0;
      return *this;
    }

    IntVector modVal;
    intVect = divide(intVect, rhs.intVect, modVal, INT_BASE);
    sign = !((sign && rhs.sign) || (!sign && !rhs.sign));

    fixZero();
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
      throw std::domain_error("Div by zero");
    }
    if (*this == 0) {
      return *this;
    }
    if (greater(rhs.intVect, intVect)) {
      return *this;
    }

    divide(intVect, rhs.intVect, intVect, INT_BASE);

    fixZero();
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
    return *this -= 1;
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
    if (sign != rhs.sign) {
      return false;
    }
    return equal(intVect, rhs.intVect);
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
    if (!sign && rhs.sign) {
      return false;
    }
    if (sign && !rhs.sign) {
      return true;
    }

    if (sign) {
      return less(rhs.intVect, intVect);
    }

    return less(intVect, rhs.intVect);
  }

  bool Integer::operator<(int64_t rhs) const {
    return *this < Integer(rhs);
  }

  bool operator<(int64_t lhs, const Integer &rhs) {
    return Integer(lhs) < rhs;
  }

  bool Integer::operator>(const Integer &rhs) const {
    if (!sign && rhs.sign) {
      return true;
    }
    if (sign && !rhs.sign) {
      return false;
    }
    if (sign) {
      return greater(rhs.intVect, intVect);
    }
    return greater(intVect, rhs.intVect);
  }

  bool Integer::operator>(int64_t rhs) const {
    return *this > Integer(rhs);
  }

  bool operator>(int64_t lhs, const Integer &rhs) {
    return Integer(lhs) > rhs;
  }

  bool Integer::operator<=(const Integer &rhs) const {
    if (!sign && rhs.sign) {
      return false;
    }
    if (sign && !rhs.sign) {
      return true;
    }
    if (sign) {
      return lessEqual(rhs.intVect, intVect);
    }
    return lessEqual(intVect, rhs.intVect);
  }

  bool Integer::operator<=(int64_t rhs) const {
    return *this <= Integer(rhs);
  }

  bool operator<=(int64_t lhs, const Integer &rhs) {
    return Integer(lhs) <= rhs;
  }

  bool Integer::operator>=(const Integer &rhs) const {
    if (!sign && rhs.sign) {
      return true;
    }
    if (sign && !rhs.sign) {
      return false;
    }
    if (sign) {
      return greaterEqual(rhs.intVect, intVect);
    }
    return greaterEqual(intVect, rhs.intVect);
  }

  bool Integer::operator>=(int64_t rhs) const {
    return *this >= Integer(rhs);
  }

  bool operator>=(int64_t lhs, const Integer &rhs) {
    return Integer(lhs) >= rhs;
  }

  size_t Integer::size() const {
    return (intVect.size() - 1) * INT_BASE_SIZE + (std::to_string(intVect.back())).size();
  }

  // Changing the number base to solve sqrt
  Integer Integer::sqrt() const {
    if (*this < 0) {
      throw std::domain_error("sqrt out of range");
    }
    auto vect = toIntVector(this->toString(), 2);
    return Integer(fintamath::toString(fintamath::sqrt(vect), 1));
  }

  std::string Integer::toString() const {
    std::string str = fintamath::toString(intVect, INT_BASE_SIZE);
    if (str != "0" && sign) {
      str.insert(0, 1, '-');
    }
    return str;
  }

  void Integer::fixZero() {
    if (intVect.size() == 1 && intVect.front() == 0) {
      sign = false;
    }
  }

  std::shared_ptr<Object> Integer::clone() const {
    return std::make_shared<Integer>(*this);
  }

  IntVector toIntVector(const std::string_view &str, int64_t baseSize) {
    IntVector intVect;
    std::basic_string_view<char>::const_iterator iter = str.end();
    for (; std::distance(str.begin(), iter) > baseSize; iter -= baseSize) {
      intVect.push_back(stoll(std::string(iter - baseSize, iter)));
    }
    intVect.push_back(stoll(std::string(str.begin(), iter)));
    toSignificantDigits(intVect);
    return intVect;
  }

  bool canConvert(const std::string_view &str) {
    const int64_t firstDigit = 0;
    const int64_t lastDigit = 9;
    return std::all_of(str.begin(), str.end(),
                       [&](auto ch) { return ch - '0' >= firstDigit && ch - '0' <= lastDigit; });
  }

  std::string toString(const IntVector &intVect, int64_t baseSize) {
    std::string str = std::to_string(intVect.back());
    if (intVect.size() == 1) {
      return str;
    }
    for (size_t i = intVect.size() - 2; i != SIZE_MAX; i--) {
      std::string tmp = std::to_string(intVect[i]);
      tmp.insert(0, baseSize - tmp.size(), '0');
      str.insert(str.size(), tmp);
    }
    return str;
  }

  // Finding a digit before the first non-zero digit, starting with the lowest digits
  int64_t firstZeroNum(const IntVector &rhs) {
    int64_t num = 0;
    while (num < rhs.size() && rhs[num] == 0) {
      num++;
    }
    return num;
  }

  void toSignificantDigits(IntVector &rhs) {
    size_t i = rhs.size() - 1;
    for (; i > 0; i--) {
      if (rhs[i] != 0) {
        break;
      }
    }
    rhs.resize(i + 1);
  }

  // If the value in the given digit >= INT_BASE, the surplus is added to the next digit
  void toBasePositive(IntVector &rhs, size_t pos, int64_t base) {
    if (rhs[pos] >= base) {
      rhs[pos + 1] += rhs[pos] / base;
      rhs[pos] %= base;
    }
  }

  // If the value in the given digit < 0, then the deficiency is subtracted from the next digit
  void toBaseNegative(IntVector &rhs, size_t pos, int64_t base) {
    if (rhs[pos] < 0) {
      rhs[pos + 1]--;
      rhs[pos] += base;
    }
  }

  bool equal(const IntVector &lhs, const IntVector &rhs) {
    if (lhs.size() != rhs.size()) {
      return false;
    }

    for (size_t i = lhs.size() - 1; i != SIZE_MAX; i--) {
      if (lhs[i] != rhs[i]) {
        return false;
      }
    }

    return true;
  }

  bool less(const IntVector &lhs, const IntVector &rhs) {
    if (lhs.size() > rhs.size()) {
      return false;
    }
    if (lhs.size() < rhs.size()) {
      return true;
    }

    for (size_t i = lhs.size() - 1; i != SIZE_MAX; i--) {
      if (lhs[i] > rhs[i]) {
        return false;
      }
      if (lhs[i] < rhs[i]) {
        return true;
      }
    }

    return false;
  }

  bool greater(const IntVector &lhs, const IntVector &rhs) {
    if (lhs.size() > rhs.size()) {
      return true;
    }
    if (lhs.size() < rhs.size()) {
      return false;
    }

    for (size_t i = lhs.size() - 1; i != SIZE_MAX; i--) {
      if (lhs[i] > rhs[i]) {
        return true;
      }
      if (lhs[i] < rhs[i]) {
        return false;
      }
    }

    return false;
  }

  bool lessEqual(const IntVector &lhs, const IntVector &rhs) {
    if (lhs.size() > rhs.size()) {
      return false;
    }
    if (lhs.size() < rhs.size()) {
      return true;
    }

    for (size_t i = lhs.size() - 1; i != SIZE_MAX; i--) {
      if (lhs[i] > rhs[i]) {
        return false;
      }
      if (lhs[i] < rhs[i]) {
        return true;
      }
    }

    return true;
  }

  bool greaterEqual(const IntVector &lhs, const IntVector &rhs) {
    if (lhs.size() > rhs.size()) {
      return true;
    }
    if (lhs.size() < rhs.size()) {
      return false;
    }

    for (size_t i = lhs.size() - 1; i != SIZE_MAX; i--) {
      if (lhs[i] > rhs[i]) {
        return true;
      }
      if (lhs[i] < rhs[i]) {
        return false;
      }
    }

    return true;
  }

  // Column addition without reduction to significant digits
  IntVector add(const IntVector &lhs, const IntVector &rhs, int64_t base) {
    IntVector val = lhs;
    if (rhs.size() > val.size()) {
      val.resize(rhs.size(), 0);
    }
    val.push_back(0);

    for (size_t i = 0; i < rhs.size(); i++) {
      val[i] += rhs[i];
      toBasePositive(val, i, base);
    }
    for (size_t i = rhs.size(); i < val.size(); i++) {
      toBasePositive(val, i, base);
    }

    return val;
  }

  // Column addition with reduction to significant digits
  IntVector addToSignificantDigits(const IntVector &lhs, const IntVector &rhs, int64_t base) {
    IntVector val = add(lhs, rhs, base);
    toSignificantDigits(val);
    return val;
  }

  // Column substraction
  IntVector substract(const IntVector &lhs, const IntVector &rhs, int64_t base) {
    IntVector val = lhs;

    for (size_t i = 0; i < rhs.size(); i++) {
      val[i] -= rhs[i];
      toBaseNegative(val, i, base);
    }
    for (size_t i = rhs.size(); i < val.size(); i++) {
      toBaseNegative(val, i, base);
    }

    toSignificantDigits(val);
    return val;
  }

  // Multiplication by a short number
  IntVector shortMultiply(const IntVector &lhs, int64_t rhs, int64_t base) {
    IntVector val;
    val.resize(lhs.size() + 1, 0);

    for (size_t i = 0; i < lhs.size(); i++) {
      val[i] += lhs[i] * rhs;
      toBasePositive(val, i, base);
    }

    toSignificantDigits(val);
    return val;
  }

  /*
    Multiplication of numbers in the form of polynomials without reduction to significant digits
  */
  IntVector polynomialMultiply(const IntVector &lhs, const IntVector &rhs, int64_t base) {
    IntVector res;
    res.resize(lhs.size() + rhs.size(), 0);

    for (size_t i = 0; i < lhs.size(); i++) {
      for (size_t j = 0; j < rhs.size(); j++) {
        res[i + j] += lhs[i] * rhs[j];
        toBasePositive(res, i + j, base);
      }
    }

    return res;
  }

  /*
    Multiplication of numbers A by B by Karatsuba's method. Recursively applied until the size of of one of the numbers
    is equal to KARATSUBA_CUTOFF

    A * B = p0 + p1 * INT_BASE^m + p2 * INT_BASE^2m

    p0 = A0 * B0
    p1 = (A0 + A1)(B0 + B1) - (p1 + p2)
    p2 = A1 * B1

    A0 and B0 - the first halves of numbers
    A1 and B1 - the second halves of numbers
  */
  IntVector karatsubaMultiply(const IntVector &lhs, const IntVector &rhs, int64_t base) {
    if (lhs.size() < KARATSUBA_CUTOFF) {
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

  // Multiplication of zero digits
  size_t zerosMultiply(IntVector &lhs, IntVector &rhs) {
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

  // Adding leading zeros to bring the numbers to the required form
  IntVector multiply(const IntVector &lhs, const IntVector &rhs, int64_t base) {
    IntVector tmpLhs = lhs;
    IntVector tmpRhs = rhs;
    IntVector res;
    size_t zerosNum = zerosMultiply(tmpLhs, tmpRhs);

    if (tmpLhs.size() < KARATSUBA_CUTOFF || tmpRhs.size() < KARATSUBA_CUTOFF) {
      res = polynomialMultiply(tmpLhs, tmpRhs, base);
    } else {
      size_t maxSize = std::max(tmpLhs.size(), tmpRhs.size());
      if (maxSize % 2 == 1) {
        maxSize++;
      }
      tmpLhs.resize(maxSize, 0);
      tmpRhs.resize(maxSize, 0);

      res = karatsubaMultiply(tmpLhs, tmpRhs, base);
    }

    res.insert(res.begin(), zerosNum, 0);
    toSignificantDigits(res);
    return res;
  }

  // Dividing by a short number
  IntVector shortDivide(const IntVector &lhs, int64_t rhs, int64_t base) {
    IntVector val = lhs;

    for (size_t i = val.size() - 1; i > 0; i--) {
      val[i - 1] += (val[i] % rhs) * base;
      val[i] /= rhs;
    }
    val.front() /= rhs;

    toSignificantDigits(val);
    return val;
  }

  // Dividing by short number with a remainder
  IntVector shortDivide(const IntVector &lhs, int64_t rhs, IntVector &modVal, int64_t base) {
    IntVector val = lhs;

    for (size_t i = val.size() - 1; i > 0; i--) {
      val[i - 1] += (val[i] % rhs) * base;
      val[i] /= rhs;
    }
    modVal = IntVector{val.front() % rhs};
    val.front() /= rhs;

    toSignificantDigits(val);
    return val;
  }

  // Reduction of zero digits of numbers
  void zerosDivide(IntVector &lhs, IntVector &rhs) {
    int64_t zerosNum = std::min(firstZeroNum(lhs), firstZeroNum(rhs));
    if (zerosNum != 0) {
      lhs.erase(lhs.begin(), lhs.begin() + zerosNum);
      rhs.erase(rhs.begin(), rhs.begin() + zerosNum);
    }
  }

  IntVector binsearchDivide(const IntVector &lhs, const IntVector &rhs, IntVector &left, IntVector &right,
                            int64_t base) {
    IntVector mid;
    while (greater(substract(right, left, base), IntVector{1})) {
      mid = shortDivide(addToSignificantDigits(left, right, base), 2, base);
      IntVector multVal = multiply(rhs, mid, base);
      if (greater(multVal, lhs)) {
        right = mid;
      } else {
        left = mid;
      }
    }

    if (IntVector mult = multiply(rhs, right, base); greater(lhs, mult) || equal(lhs, mult)) {
      return right;
    }
    return left;
  }

  /*
    The lower and upper bounds for binsearch division are defined as follows: N = A/(B.back() +- 1). N is the
    corresponding bound of B.back() - the most significant digit of B. Then (N.size() + B.size()) of the first digits
    are discarded.
  */
  IntVector divide(const IntVector &lhs, const IntVector &rhs, IntVector &modVal, int64_t base) {
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
    Calculating the square root of A in a column.

    1. Divide number A into faces, two digits in each face from right to left (from lowest to highest digits).

    Extraction starts from left to right. Choose a number, the square of which does not exceed the number in the first
    facet. This number is squared and written under the number in the first face. 3.

    Find the difference between the number in the first face and the square of the first selected number.

    4. To the resulting difference, add the next face, and the resulting number will be divisible. Form the divisor. The
    first answer choice should be multiplied by 2, we get the number of tens of the divisor, and the number of units
    should be such that its product of the whole divisor does not exceed the divisor. Write the selected digit in the
    answer. Use binary search for selection.

    5.To the resulting difference carry the next facet and follow the algorithm.
  */
  IntVector sqrt(const IntVector &rhs) {
    const int64_t base = 10;

    IntVector val;
    IntVector diff;
    val.push_back((int64_t)std::sqrt((double)rhs.back()));

    getSqrtDiff(rhs, base, val, diff);

    for (size_t i = rhs.size() - 2; i != SIZE_MAX; i--) {
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

        if (greater(doubledRes, modVal)) {
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

  void getSqrtDiff(const IntVector &rhs, const int64_t &base, IntVector &val, IntVector &diff) {
    int64_t tmpVal = rhs.back() - val.front() * val.front();
    diff.push_back(tmpVal % base);
    if (tmpVal >= base) {
      diff.push_back(tmpVal / base);
    }
  }
}
