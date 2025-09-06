#pragma once

#include <optional>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectUtils.hpp"
#include "fintamath/core/MultiMethod.hpp"

namespace fintamath {

class INumber : public IMathObject {
  FINTAMATH_INTERFACE_BODY(INumber, IMathObject)

  using BoolBinaryMultiMethod = detail::MultiMethod<bool(const SharedRef<INumber> &, const SharedRef<INumber> &)>;

  using NumberBinaryMultiMethod = detail::MultiMethod<SharedRef<INumber>(const SharedRef<INumber> &, const SharedRef<INumber> &)>;

public:
  virtual std::optional<unsigned> getPrecision() const noexcept;

  virtual bool isComplex() const noexcept;

  friend SharedRef<INumber> add(const SharedRef<INumber> &lhs, const SharedRef<INumber> &rhs);

protected:
  bool equals(const SharedRef<IMathObject> &lhs, const SharedRef<IMathObject> &rhs) const noexcept override;

  template <typename Num, typename Func>
  static void registerEqualsFunction(Func func = {});

  template <typename Num, typename Func>
  static void registerAddFunction(Func func = {});

private:
  static BoolBinaryMultiMethod &getEqualsMultimethod();

  static NumberBinaryMultiMethod &getAddMultimethod();

  template <typename Num>
  static void registerBoolBinaryFunction(auto &multimethod, auto func);

  template <typename Num>
  static void registerNumberBinaryFunction(auto &multimethod, auto func);
};

template <typename Num, typename Func = detail::EqualTo<Num>>
inline void INumber::registerEqualsFunction(Func func) {
  registerBoolBinaryFunction<Num>(getEqualsMultimethod(), std::move(func));
}

template <typename Num, typename Func = detail::AddTo<Num, Num>>
inline void INumber::registerAddFunction(Func func) {
  registerNumberBinaryFunction<Num>(getAddMultimethod(), std::move(func));
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
      auto res = func(*lhs, *rhs);

      if (auto resUnwrapped = cast<INumber>(res.unwrapp())) {
        return resUnwrapped.toRef();
      }

      return makeShared<decltype(res)>(std::move(res));
    }
  );
}

}
