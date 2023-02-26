#pragma once

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/IExpression.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/meta/Converter.hpp"
#include "fintamath/numbers/NumberConstants.hpp"
#include <type_traits>

namespace fintamath {

class IPolynomExpression : virtual public IExpression {
public:
  IPolynomExpression() = default;

  IPolynomExpression(const IPolynomExpression &rhs);

  explicit IPolynomExpression(IPolynomExpression &&rhs) = default;

  IPolynomExpression &operator=(const IPolynomExpression &rhs);

  IPolynomExpression &operator=(IPolynomExpression &&rhs) noexcept = default;

  explicit IPolynomExpression(ArgumentsPtrVector inPolynomVect);

  // TODO: implement iterator & remove this
  const ArgumentsPtrVector &getArgumentsPtrVector() const;

  void setPrecision(uint8_t precision) final;

  std::vector<MathObjectPtr> getVariables() const final;

  ArgumentsPtrVector clonePolynom() const;

  // TODO: remove this
  void validate() const final;

protected:
  ArgumentsPtrVector polynomVect;

  static void pushPolynomToPolynom(const ArgumentsPtrVector &from, ArgumentsPtrVector &to);
};

template <typename Derived>
class IPolynomExpressionCRTP : virtual public IExpressionCRTP<Derived>, virtual public IPolynomExpression {
public:
  void addElement(MathObjectPtr &&elem) {
    ArgumentsPtrVector elemPolynom;

    if (auto *expr = cast<Derived>(elem.get())) {
      elemPolynom = std::move(expr->polynomVect);
    } else if (auto *expr = cast<Expression>(elem.get())) {
      addElement(std::move(expr->getInfo()));
      return;
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
  /*static void sortPolynom(const ArgumentsPtrVector &vect, ArgumentsPtrVector &numVect, ArgumentsPtrVector &exprVect,
                          ArgumentsPtrVector &literalVect, ArgumentsPtrVector &funcVect, ArgumentsPtrVector &powVect) {
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
  }*/

protected:
  void compress() final {
    Derived compressedExpr(ArgumentsPtrVector{});

    for (auto &child : polynomVect) {
      compressedExpr.addElement(std::move(child));
    }

    polynomVect = std::move(compressedExpr.polynomVect);
  }
};

}
