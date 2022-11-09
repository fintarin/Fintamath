#include "fintamath/numbers/Integer.hpp"

#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <string>

#include "boost/multiprecision/cpp_int.hpp"

#include "fintamath/exceptions/UndefinedBinaryOpearatorException.hpp"
#include "fintamath/exceptions/UndefinedFunctionException.hpp"

using namespace boost::multiprecision;

namespace fintamath {
  struct IntegerImpl {
    cpp_int v;
  };

  Integer::Integer() {
    value = std::make_unique<IntegerImpl>();
  }

  Integer::Integer(const Integer &rhs) {
    value = std::make_unique<IntegerImpl>(*rhs.value);
  }

  Integer::~Integer() = default;

  Integer::Integer(Integer &&) noexcept = default;

  Integer &Integer::operator=(const Integer &rhs) {
    if (this != &rhs) {
      value = std::make_unique<IntegerImpl>(*rhs.value);
    }
  }

  Integer &Integer::operator=(Integer &&) noexcept = default;

  Integer::Integer(std::string str) : Integer() {
    if (str.empty()) {
      throw InvalidInputException(*this, str);
    }

    // Remove leading zeros
    {
      int8_t i = 0;
      if (str.front() == '-') {
        i++;
      }
      str.erase(i, str.find_first_not_of('0'));
    }

    try {
      value->v.assign(str);
    } catch (const std::runtime_error &) {
      throw InvalidInputException(*this, str);
    }
  }

  Integer::Integer(int64_t val) : Integer() {
    value->v.assign(val);
  }

  Integer &Integer::operator%=(const Integer &rhs) {
    return mod(rhs);
  }

  Integer Integer::operator%(const Integer &rhs) const {
    return Integer(*this).mod(rhs);
  }

  std::string Integer::toString() const {
    return value->v.str();
  }

  std::string Integer::getClassName() const {
    return "Integer";
  }

  bool Integer::equals(const Integer &rhs) const {
    return value->v == rhs.value->v;
  }

  bool Integer::less(const Integer &rhs) const {
    return value->v < rhs.value->v;
  }

  bool Integer::more(const Integer &rhs) const {
    return value->v > rhs.value->v;
  }

  Integer &Integer::add(const Integer &rhs) {
    value->v += rhs.value->v;
    return *this;
  }

  Integer &Integer::substract(const Integer &rhs) {
    value->v -= rhs.value->v;
    return *this;
  }

  Integer &Integer::multiply(const Integer &rhs) {
    value->v *= rhs.value->v;
    return *this;
  }

  Integer &Integer::divide(const Integer &rhs) {
    if (rhs == 0) {
      throw UndefinedBinaryOpearatorException("/", toString(), rhs.toString());
    }

    value->v /= rhs.value->v;
    return *this;
  }

  Integer &Integer::mod(const Integer &rhs) {
    if (rhs == 0) {
      throw UndefinedBinaryOpearatorException("mod", toString(), rhs.toString());
    }

    value->v %= rhs.value->v;
    return *this;
  }

  Integer &Integer::negate() {
    value->v = -value->v;
    return *this;
  }

  Integer &Integer::increase() {
    ++value->v;
    return *this;
  }

  Integer &Integer::decrease() {
    --value->v;
    return *this;
  }

  Integer sqrt(Integer rhs) {
    if (rhs < 0) {
      throw UndefinedFunctionException("sqrt", {rhs.toString()});
    }

    rhs.value->v = sqrt(rhs.value->v);

    return rhs;
  }
}
