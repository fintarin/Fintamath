#pragma once

#include <vector>

#include "fintamath/exceptions/FunctionCallException.hpp"
#include "fintamath/helpers/Caster.hpp"
#include "fintamath/helpers/Converter.hpp"

#define FINTAMATH_EQUAL_OPERATOR(OPER)

#define FINTAMATH_COMPARISON_OPERATOR(CLASS, OPER)                                                                     \
  if (rhs.is<Derived>()) {                                                                                             \
    return *this OPER rhs.to<Derived>();                                                                               \
  }                                                                                                                    \
  if (auto tmp = helpers::Converter::convert(rhs, *this); tmp != nullptr) {                                             \
    return *this OPER tmp->template to<CLASS>();                                                                       \
  }                                                                                                                    \
  if (auto tmp = helpers::Converter::convert(*this, rhs); tmp != nullptr) {                                             \
    return tmp->template to<CLASS>() OPER rhs;                                                                         \
  }                                                                                                                    \
  throw FunctionCallException(#OPER, {toString(), rhs.toString()})

#define FINTAMATH_ARITHMETIC_OPERATOR(CLASS, OPER)                                                                     \
  if (rhs.is<Derived>()) {                                                                                             \
    auto res = (*this OPER rhs.to<Derived>()).simplify();                                                              \
    return helpers::cast<CLASS>(res);                                                                                  \
  }                                                                                                                    \
  if (auto tmp = helpers::Converter::convert(rhs, *this); tmp != nullptr) {                                             \
    auto res = (*this OPER tmp->template to<CLASS>())->simplify();                                                     \
    return helpers::cast<CLASS>(res);                                                                                  \
  }                                                                                                                    \
  if (auto tmp = helpers::Converter::convert(*this, rhs); tmp != nullptr) {                                             \
    auto res = (tmp->template to<CLASS>() OPER rhs)->simplify();                                                       \
    return helpers::cast<CLASS>(res);                                                                                  \
  }                                                                                                                    \
  throw FunctionCallException(#OPER, {toString(), rhs.toString()})

namespace fintamath {
  using ArgumentsVector = std::vector<std::reference_wrapper<const IMathObject>>;
}
