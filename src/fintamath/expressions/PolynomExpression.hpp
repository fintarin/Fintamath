#pragma once

#include "fintamath/expressions/IExpression.hpp"

namespace fintamath {

template <typename Derived, typename Element>
class PolynomExpressionCRTP : public IExpressionCRTP<Derived> {
public:
  using PolynomVector = std::vector<Element>;

public:
  void pushPolynomToPolynom(const PolynomVector &from, PolynomVector &to) {
    for (const auto &elem : from) {
      to.emplace_back(elem);
    }
  }

  // TODO: implement iterator & remove this
  const PolynomVector &getPolynomVector() const {
    return polynomVect;
  }

protected:
  PolynomVector polynomVect;
};

}
