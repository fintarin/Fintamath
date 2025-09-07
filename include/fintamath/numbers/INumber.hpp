#pragma once

#include <optional>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectUtils.hpp"
#include "fintamath/core/MultiMethod.hpp"

namespace fintamath {

class INumber : public IMathObject {
  FINTAMATH_INTERFACE_BODY(INumber, IMathObject)

  using BoolBinaryMultiMethod = detail::MultiMethod<bool(
    const SharedRef<INumber> &,
    const SharedRef<INumber> &
  )>;

  using NumberBinaryMultiMethod = detail::MultiMethod<SharedRef<INumber>(
    const SharedRef<INumber> &,
    const SharedRef<INumber> &
  )>;

  using NumberUnaryMultiMethod = detail::MultiMethod<SharedRef<INumber>(
    const SharedRef<INumber> &
  )>;

public:
  virtual std::optional<unsigned> getPrecision() const noexcept;

  virtual bool isComplex() const noexcept;

  friend bool less(const SharedRef<INumber> &lhs, const SharedRef<INumber> &rhs);

  friend bool greater(const SharedRef<INumber> &lhs, const SharedRef<INumber> &rhs);

  friend bool lessEquals(const SharedRef<INumber> &lhs, const SharedRef<INumber> &rhs);

  friend bool greaterEquals(const SharedRef<INumber> &lhs, const SharedRef<INumber> &rhs);

  friend SharedRef<INumber> add(const SharedRef<INumber> &lhs, const SharedRef<INumber> &rhs);

  friend SharedRef<INumber> sub(const SharedRef<INumber> &lhs, const SharedRef<INumber> &rhs);

  friend SharedRef<INumber> mul(const SharedRef<INumber> &lhs, const SharedRef<INumber> &rhs);

  friend SharedRef<INumber> div(const SharedRef<INumber> &lhs, const SharedRef<INumber> &rhs);

  friend SharedRef<INumber> neg(const SharedRef<INumber> &rhs);

protected:
  bool equals(const SharedRef<IMathObject> &self, const SharedRef<IMathObject> &rhs) const noexcept override;

  template <typename Num, typename Func>
  static void registerEqualsFunction(Func func = {});

  template <typename Num, typename Func>
  static void registerLessFunction(Func func = {});

  template <typename Num, typename Func>
  static void registerGreaterFunction(Func func = {});

  template <typename Num, typename Func>
  static void registerLessEqualsFunction(Func func = {});

  template <typename Num, typename Func>
  static void registerGreaterEqualsFunction(Func func = {});

  template <typename Num, typename Func>
  static void registerAddFunction(Func func = {});

  template <typename Num, typename Func>
  static void registerSubFunction(Func func = {});

  template <typename Num, typename Func>
  static void registerMulFunction(Func func = {});

  template <typename Num, typename Func>
  static void registerDivFunction(Func func = {});

  template <typename Num, typename Func>
  static void registerNegFunction(Func func = {});

private:
  static BoolBinaryMultiMethod &getEqualsMultimethod();

  static BoolBinaryMultiMethod &getLessMultimethod();

  static BoolBinaryMultiMethod &getGreaterMultimethod();

  static BoolBinaryMultiMethod &getLessEqualsMultimethod();

  static BoolBinaryMultiMethod &getGreaterEqualsMultimethod();

  static NumberBinaryMultiMethod &getAddMultimethod();

  static NumberBinaryMultiMethod &getSubMultimethod();

  static NumberBinaryMultiMethod &getMulMultimethod();

  static NumberBinaryMultiMethod &getDivMultimethod();

  static NumberUnaryMultiMethod &getNegMultimethod();

  template <typename Num>
  static void registerBoolBinaryFunction(auto &multimethod, auto func);

  template <typename Num>
  static void registerNumberBinaryFunction(auto &multimethod, auto func);

  template <typename Num>
  static void registerNumberUnaryFunction(auto &multimethod, auto func);

  template <typename Num>
  static SharedRef<INumber> numberToSharedRef(Num &&num);
};

template <typename Num, typename Func = std::equal_to<Num>>
inline void INumber::registerEqualsFunction(Func func) {
  registerBoolBinaryFunction<Num>(getEqualsMultimethod(), std::move(func));
}

template <typename Num, typename Func = std::less<Num>>
inline void INumber::registerLessFunction(Func func) {
  registerBoolBinaryFunction<Num>(getLessMultimethod(), std::move(func));
}

template <typename Num, typename Func = std::greater<Num>>
inline void INumber::registerGreaterFunction(Func func) {
  registerBoolBinaryFunction<Num>(getGreaterMultimethod(), std::move(func));
}

template <typename Num, typename Func = std::less_equal<Num>>
inline void INumber::registerLessEqualsFunction(Func func) {
  registerBoolBinaryFunction<Num>(getLessEqualsMultimethod(), std::move(func));
}

template <typename Num, typename Func = std::greater_equal<Num>>
inline void INumber::registerGreaterEqualsFunction(Func func) {
  registerBoolBinaryFunction<Num>(getGreaterEqualsMultimethod(), std::move(func));
}

template <typename Num, typename Func = detail::AddCallable<Num>>
inline void INumber::registerAddFunction(Func func) {
  registerNumberBinaryFunction<Num>(getAddMultimethod(), std::move(func));
}

template <typename Num, typename Func = detail::SubCallable<Num>>
inline void INumber::registerSubFunction(Func func) {
  registerNumberBinaryFunction<Num>(getSubMultimethod(), std::move(func));
}

template <typename Num, typename Func = detail::MulCallable<Num>>
inline void INumber::registerMulFunction(Func func) {
  registerNumberBinaryFunction<Num>(getMulMultimethod(), std::move(func));
}

template <typename Num, typename Func = detail::DivCallable<Num>>
inline void INumber::registerDivFunction(Func func) {
  registerNumberBinaryFunction<Num>(getMulMultimethod(), std::move(func));
}

template <typename Num, typename Func = detail::NegCallable<Num>>
inline void INumber::registerNegFunction(Func func) {
  registerNumberUnaryFunction<Num>(getNegMultimethod(), std::move(func));
}

template <typename Num>
inline void INumber::registerBoolBinaryFunction(auto &multimethod, auto func) {
  multimethod.template add<Num, Num>([func = std::move(func)](const SharedRef<Num> &lhs, const SharedRef<Num> &rhs) {
    return func(*lhs, *rhs);
  });
}

template <typename Num>
inline void INumber::registerNumberBinaryFunction(auto &multimethod, auto func) {
  multimethod.template add<Num, Num>(
    [func = std::move(func)](const SharedRef<Num> &lhs, const SharedRef<Num> &rhs) -> SharedRef<INumber> {
      return numberToSharedRef(func(*lhs, *rhs));
    }
  );
}

template <typename Num>
inline void INumber::registerNumberUnaryFunction(auto &multimethod, auto func) {
  multimethod.template add<Num>(
    [func = std::move(func)](const SharedRef<Num> &rhs) -> SharedRef<INumber> {
      return numberToSharedRef(func(*rhs));
    }
  );
}

template <typename Num>
inline SharedRef<INumber> INumber::numberToSharedRef(Num &&num) {
  if (auto unwrapped = cast<INumber>(num.unwrapp())) {
    return unwrapped.toRef();
  }

  return makeShared<detail::RemoveQualifiers<Num>>(std::forward<Num>(num));
}

}
