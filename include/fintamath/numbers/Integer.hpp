#pragma once

#include <memory>

#include "fintamath/core/IModular.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class IntegerImpl;

class Integer : public INumberCRTP<Integer>, public IModularCRTP<Integer>, public IIncrementalCRTP<Integer> {
public:
  Integer();

  Integer(const Integer &rhs);

  Integer(Integer &&rhs) noexcept;

  Integer &operator=(const Integer &rhs);

  Integer &operator=(Integer &&rhs) noexcept;

  ~Integer() override;

  Integer(const IntegerImpl &impl);

  explicit Integer(std::string str);

  Integer(int64_t val);

  std::string toString() const override;

  int sign() const;

  const std::unique_ptr<IntegerImpl> &getImpl() const;

protected:
  bool equals(const Integer &rhs) const override;

  bool less(const Integer &rhs) const override;

  bool more(const Integer &rhs) const override;

  Integer &add(const Integer &rhs) override;

  Integer &substract(const Integer &rhs) override;

  Integer &multiply(const Integer &rhs) override;

  Integer &divide(const Integer &rhs) override;

  Integer &mod(const Integer &rhs) override;

  Integer &negate() override;

  Integer &increase() override;

  Integer &decrease() override;

private:
  std::unique_ptr<IntegerImpl> impl;
};

}
