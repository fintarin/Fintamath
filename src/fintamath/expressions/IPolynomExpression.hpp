#pragma once

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/IExpression.hpp"
#include "fintamath/expressions/PowExpression.hpp"
#include "fintamath/functions/powers/Pow.hpp" // TODO: remove this include
#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/meta/Converter.hpp"
#include "fintamath/numbers/NumberConstants.hpp"
#include <type_traits>

namespace fintamath {

class IPolynomExpression : virtual public IExpression {
public:
  using PolynomVector = std::vector<MathObjectPtr>;

  IPolynomExpression() = default;

  IPolynomExpression(const IPolynomExpression &rhs);

  explicit IPolynomExpression(IPolynomExpression &&rhs) = default;

  IPolynomExpression &operator=(const IPolynomExpression &rhs);

  IPolynomExpression &operator=(IPolynomExpression &&rhs) noexcept = default;

  explicit IPolynomExpression(PolynomVector inPolynomVect);

  static void pushPolynomToPolynom(const PolynomVector &from, PolynomVector &to);

  // TODO: implement iterator & remove this
  const PolynomVector &getPolynomVector() const;

  void simplifyValue(bool isPrecise, MathObjectPtr &obj) const;

  void setPrecision(uint8_t precision) final;

  std::vector<MathObjectPtr> getVariables() const final;

  PolynomVector clonePolynom() const;

  // TODO: remove this
  void validate() const final;

protected:
  PolynomVector polynomVect;
};

template <typename Derived>
class IPolynomExpressionCRTP : virtual public IExpressionCRTP<Derived>, virtual public IPolynomExpression {
public:
  void addElement(MathObjectPtr &&elem) {
    PolynomVector elemPolynom;

    if (auto *expr = cast<Derived>(elem.get())) {
      elemPolynom = std::move(expr->polynomVect);
    } else if (auto *expr = cast<Expression>(elem.get())) {
      if (expr->getChildren().empty()) {
        addElement(std::move(expr->getInfo()));
        return;
      }
    }

    if (elemPolynom.empty()) {
      polynomVect.emplace_back(std::move(elem));
      return;
    }

    for (auto &child : elemPolynom) {
      polynomVect.emplace_back(std::move(child));
    }
  }

  // TODO: refactor arguments
  static void sortPolynom(const PolynomVector &vect, PolynomVector &numVect, PolynomVector &exprVect,
                          PolynomVector &literalVect, PolynomVector &funcVect, PolynomVector &powVect) {
    for (const auto &child : vect) {
      if (is<Expression>(child)) {
        funcVect.emplace_back(child->clone());
        continue;
      }

      if (is<PowExpression>(child)) {
        powVect.emplace_back(child->clone());
        continue;
      }

      if (is<IExpression>(child) && !is<Derived>(child)) {
        exprVect.emplace_back(child->clone());
        continue;
      }

      if (is<INumber>(child)) {
        numVect.emplace_back(child->clone());
        continue;
      }

      if (is<ILiteral>(child)) {
        literalVect.emplace_back(child->clone());
        continue;
      }
    }
  }

protected:
  void compress() final {
    Derived compressedExpr(PolynomVector{});

    for (auto &child : polynomVect) {
      compressedExpr.addElement(std::move(child));
    }

    polynomVect = std::move(compressedExpr.polynomVect);
  }
};

}
