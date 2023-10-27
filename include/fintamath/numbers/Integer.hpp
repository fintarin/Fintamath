#pragma once

#include <boost/multiprecision/cpp_int.hpp>

#include "fintamath/numbers/IInteger.hpp"

namespace fintamath {

class Integer : public IIntegerCRTP<Integer> {
public:
  Integer();

  Integer(const Integer &rhs);

  Integer(Integer &&rhs) noexcept;

  Integer &operator=(const Integer &rhs);

  Integer &operator=(Integer &&rhs) noexcept;

  ~Integer() override;

  Integer(boost::multiprecision::cpp_int inBackend);

  explicit Integer(std::string str);

  explicit Integer(std::integral auto val) : backend(val) {
  }

  Integer(int64_t val);

  std::string toString() const override;

  int sign() const;

  const boost::multiprecision::cpp_int &getBackend() const;

  template <std::integral T>
  explicit operator T() const {
    return backend.convert_to<T>();
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::Integer;
  }

protected:
  bool equals(const Integer &rhs) const override;

  std::strong_ordering compare(const Integer &rhs) const override;

  Integer &add(const Integer &rhs) override;

  Integer &substract(const Integer &rhs) override;

  Integer &multiply(const Integer &rhs) override;

  std::unique_ptr<IArithmetic> multiplyAbstract(const IArithmetic &rhs) const override;

  Integer &divide(const Integer &rhs) override;

  std::unique_ptr<IArithmetic> divideAbstract(const IArithmetic &rhs) const override;

  Integer &mod(const Integer &rhs) override;

  Integer &bitAnd(const Integer &rhs) override;

  Integer &bitOr(const Integer &rhs) override;

  Integer &bitXor(const Integer &rhs) override;

  Integer &bitLeftShift(const Integer &rhs) override;

  Integer &bitRightShift(const Integer &rhs) override;

  Integer &bitNot() override;

  Integer &negate() override;

  Integer &increase() override;

  Integer &decrease() override;

private:
  boost::multiprecision::cpp_int backend;
};

}
