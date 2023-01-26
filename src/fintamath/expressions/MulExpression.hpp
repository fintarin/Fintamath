#pragma once

#include <cstdint>

#include "fintamath/expressions/IExpression.hpp"

namespace fintamath {

struct MulElement {
  MathObjectPtr info;

  bool inverted = false;

public:
  MulElement() = default;

  MulElement(const MulElement &rhs);

  MulElement(MulElement &&rhs) = default;

  MulElement(const MathObjectPtr &info, bool inverted = false);

  MulElement &operator=(const MulElement &rhs);

  MulElement &operator=(MulElement &&rhs) noexcept = default;

  MathObjectPtr toMathObject(bool isPrecise) const;

  void setPrecision(uint8_t precision);

  void simplify(bool isPrecise);
};

//-----------------------------------------------------------------------------------------------------//

class MulExpression : public IExpressionCRTP<MulExpression> {
public:
  using PolynomVector = std::vector<MulElement>;

public:
  MulExpression() = default;

  explicit MulExpression(PolynomVector inMulPolynom);

  MulExpression(const IMathObject &rhs);

  std::string toString() const override;

  // TODO: implement iterator & remove this
  const PolynomVector &getPolynom() const;

  void addElement(const MulElement &elem);

  MathObjectPtr simplify() const override;

  MathObjectPtr simplify(bool isPrecise) const override;

  uint16_t getBaseOperatorPriority() const override;

  void setPrecision(uint8_t precision) override;

  std::vector<MathObjectPtr> getVariables() const override;

  MathObjectPtr getPowCoefficient(const MathObjectPtr &powValue) const;

  MathObjectPtr getPow() const;

private:
  // TODO: Implement a new Expression and remove this
  struct ObjectPow;
  using Objects = std::vector<ObjectPow>;

private:
  void compress();

  static std::string tryPutInBrackets(const MathObjectPtr &obj);

  static PolynomVector openPowMulExpression(const PolynomVector &powVect);

  static PolynomVector mulNumbers(const PolynomVector &numVect);

  static void multiplicateBraces(const PolynomVector &addVect, PolynomVector &positive, PolynomVector &negative);

  static PolynomVector multiplicateTwoBraces(const PolynomVector &lhs, const PolynomVector &rhs);

  static void sortPolynom(const PolynomVector &vect, PolynomVector &numVect, PolynomVector &addVect,
                          PolynomVector &literalVect, PolynomVector &funcVect, PolynomVector &powVect);

  void simplifyPolynom();

  void simplifyDivisions();

  static void simplifyPow(PolynomVector &powVect, PolynomVector &addVect, PolynomVector &literalVect,
                          PolynomVector &funcVect);

  static void multiplicatePolynom(PolynomVector &vect, PolynomVector &positive, PolynomVector &negative);

  static void sortPowObjects(Objects &objs, PolynomVector &powVect, PolynomVector &addVect, PolynomVector &literalVect,
                             PolynomVector &funcVect);

private:
  PolynomVector mulPolynom;
};

}