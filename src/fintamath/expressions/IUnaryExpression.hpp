#pragma once

#include "fintamath/expressions/IExpression.hpp"
#include "fintamath/meta/Converter.hpp"

namespace fintamath {

class IUnaryExpression : virtual public IExpression {
public:
  IUnaryExpression() = default;

  IUnaryExpression(const IUnaryExpression &rhs);

  IUnaryExpression(IUnaryExpression &&rhs) noexcept = default;

  IUnaryExpression &operator=(const IUnaryExpression &rhs);

  IUnaryExpression &operator=(IUnaryExpression &&rhs) noexcept = default;

  explicit IUnaryExpression(const IMathObject &rhs);

  explicit IUnaryExpression(MathObjectPtr &&rhs);

  void setPrecision(uint8_t precision) final;

  std::string toString() const final;

  MathObjectPtr getInfo() const;

  // TODO: remove this
  void validate() const final;

private:
  std::string postfixToString(const IFunction &oper) const;

  std::string prefixToString(const IFunction &oper) const;

  std::string functionToString(const IFunction &oper) const;

protected:
  void simplifyValue(bool isPrecise);

  MathObjectPtr info;
};

template <typename Derived>
class IUnaryExpressionCRTP : virtual public IExpressionCRTP<Derived>, virtual public IUnaryExpression {};

}