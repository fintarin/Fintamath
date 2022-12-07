#pragma once

#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "fintamath/core/IModular.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {
  class IntegerImpl;

  class Integer : public INumberCRTP<Integer>, public IModularCRTP<Integer> {
  public:
    Integer();

    Integer(const Integer &rhs);

    Integer(Integer &&rhs) noexcept;

    Integer &operator=(const Integer &rhs);

    Integer &operator=(Integer &&rhs) noexcept;

    ~Integer() override;

    explicit Integer(std::string str);

    Integer(int64_t val);

    std::string toString() const override;

    std::string getClassName() const override;

    friend Integer sqrt(Integer rhs);

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
    std::unique_ptr<IntegerImpl> value;
  };
}
