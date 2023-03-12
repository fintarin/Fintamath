#pragma once

#include "fintamath/expressions/IExpression.hpp"

namespace fintamath {

class IUnaryExpression : virtual public IExpression, public std::enable_shared_from_this<IUnaryExpression> {
public:
  IUnaryExpression(const IUnaryExpression &rhs);

  IUnaryExpression(IUnaryExpression &&rhs) noexcept = default;

  IUnaryExpression &operator=(const IUnaryExpression &rhs);

  IUnaryExpression &operator=(IUnaryExpression &&rhs) noexcept = default;

  explicit IUnaryExpression(const IFunction &func, std::shared_ptr<IMathObject> arg);

  void setPrecision(uint8_t precision) final;

  std::string toString() const final;

  std::shared_ptr<IFunction> getFunction() const final;

  ArgumentsPtrVector getChildren() const override;

  void simplifyValue(bool isPrecise);

protected:
  virtual std::shared_ptr<IMathObject> simplifyChildren() = 0;

  std::shared_ptr<IMathObject> simplify() final;

  void validate() const final;

private:
  std::string postfixToString() const;

  std::string prefixToString() const;

  std::string functionToString() const;

protected:
  std::shared_ptr<IFunction> func;

  std::shared_ptr<IMathObject> child;
};

template <typename Derived>
class IUnaryExpressionCRTP : virtual public IExpressionCRTP<Derived>, virtual public IUnaryExpression {};

}