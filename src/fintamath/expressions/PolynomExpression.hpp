#pragma once

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/IExpression.hpp"
#include "fintamath/functions/powers/Pow.hpp" // TODO: remove this include
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/NumberConstants.hpp"

namespace fintamath {

// TODO: try to remove this and use Expression instead
struct PolynomElement {
  MathObjectPtr info;

  bool inverted = false;

public:
  PolynomElement() = default;

  PolynomElement(const PolynomElement &rhs);

  PolynomElement(PolynomElement &&rhs) = default;

  PolynomElement &operator=(const PolynomElement &rhs);

  PolynomElement &operator=(PolynomElement &&rhs) noexcept = default;

  virtual ~PolynomElement() = default;

  PolynomElement(const MathObjectPtr &info, bool inverted = false);

  PolynomElement(MathObjectPtr &&info, bool inverted = false);

  void setPrecision(uint8_t precision);
};

// TODO: try to remove the 2sd template argument and use Expression instead
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

  void addElement(Element &&elem) {
    PolynomVector elemPolynom;

    if (auto *expr = cast<Derived>(elem.info.get())) {
      elemPolynom = std::move(expr->polynomVect);
    } else if (auto *expr = cast<Expression>(elem.info.get())) {
      if (expr->getChildren().empty()) {
        addElement(Element(std::move(expr->getInfo()), elem.inverted));
        return;
      }
    }

    if (elemPolynom.empty()) {
      polynomVect.emplace_back(std::move(elem));
      return;
    }

    for (auto &child : elemPolynom) {
      polynomVect.emplace_back(std::move(child));

      if (elem.inverted) {
        polynomVect.back().inverted = !polynomVect.back().inverted;
      }
    }
  }

  void setPrecision(uint8_t precision) final {
    for (auto &child : polynomVect) {
      child.setPrecision(precision);
    }
  }

  std::vector<MathObjectPtr> getVariables() const final {
    std::vector<MathObjectPtr> vars;

    for (const auto &child : polynomVect) {
      if (is<Variable>(child.info)) {
        vars.emplace_back(child.info->clone());
        continue;
      }

      if (const auto *childExpr = cast<IExpression>(child.info.get())) {
        auto childVars = childExpr->getVariables();

        for (const auto &childVar : childVars) {
          vars.emplace_back(childVar->clone());
        }

        continue;
      }
    }

    return vars;
  }

  // TODO: refactor arguments
  static void sortPolynom(const PolynomVector &vect, PolynomVector &numVect, PolynomVector &exprVect,
                          PolynomVector &literalVect, PolynomVector &funcVect, PolynomVector &powVect) {
    for (const auto &child : vect) {
      // TODO: do not use Pow here
      if (const auto *childExpr = cast<Expression>(child.info.get())) {
        if (is<Pow>(childExpr->getInfo())) {
          powVect.emplace_back(child);
        } else {
          funcVect.emplace_back(child);
        }

        continue;
      }

      if (is<IExpression>(child.info) && !is<Derived>(child.info)) {
        exprVect.emplace_back(child);
        continue;
      }

      if (is<INumber>(child.info)) {
        numVect.emplace_back(child);
        continue;
      }

      if (is<ILiteral>(child.info)) {
        literalVect.emplace_back(child);
        continue;
      }
    }
  }

protected:
  void compress() final {
    Derived compressedExpr;

    for (auto &child : polynomVect) {
      compressedExpr.addElement({std::move(child)});
    }

    polynomVect = std::move(compressedExpr.polynomVect);
  }

  // TODO: remove this
  void validate() const final {
    for (const auto &child : polynomVect) {
      if (const auto *childExpr = cast<IExpression>(child.info.get())) {
        childExpr->validate();
      }
    }

    const IFunction *func = this->getFunction();

    for (size_t i = 1; i < polynomVect.size(); i++) {
      this->validateArgs(*func, {*polynomVect[i - 1].info, *polynomVect[i].info});
    }
  }

protected:
  PolynomVector polynomVect;
};

}
