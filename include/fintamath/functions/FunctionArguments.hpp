#pragma once

#include "fintamath/core/IMathObject.hpp"

namespace fintamath {

using ArgumentsVector = std::vector<std::reference_wrapper<const class IMathObject>>;
using ArgumentsPtrVector = std::vector<std::unique_ptr<IMathObject>>;
using ArgumentsTypesVector = std::vector<std::reference_wrapper<const std::type_info>>;

template <typename... Args,
          typename = std::enable_if_t<(std::is_base_of_v<IMathObject, typename Args::element_type> && ...)>>
static ArgumentsPtrVector makeArgumentsPtrVector(Args &&...args) {
  ArgumentsPtrVector vect;
  makeArgumentsPtrVector<0>(vect, std::move(args)...);
  return vect;
}

inline ArgumentsPtrVector toArgumentsPtrVect(const ArgumentsVector &argsVect) {
  ArgumentsPtrVector argsPtrVector;

  for (const auto &arg : argsVect) {
    argsPtrVector.emplace_back(arg.get().clone());
  }

  return argsPtrVector;
}

template <size_t i, typename Head, typename... Tail>
void makeArgumentsPtrVector(ArgumentsPtrVector &vect, Head &&head, Tail &&...tail) {
  vect.emplace_back(std::forward<Head>(head));
  makeArgumentsPtrVector<i + 1>(vect, std::move(tail)...);
}

template <size_t i>
void makeArgumentsPtrVector(ArgumentsPtrVector &vect) {
}

}
