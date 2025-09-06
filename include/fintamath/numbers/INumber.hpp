#pragma once

#include <optional>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectUtils.hpp"
#include "fintamath/core/MultiMethod.hpp"

namespace fintamath {

class INumber : public IMathObject {
  FINTAMATH_INTERFACE_BODY(INumber, IMathObject)

  using BoolBinaryMultiMethod = detail::MultiMethod<bool(const Shared<INumber> &, const Shared<INumber> &)>;

  using NumberBinaryMultiMethod = detail::MultiMethod<Shared<INumber>(const Shared<INumber> &, const Shared<INumber> &)>;

public:
  virtual std::optional<unsigned> getPrecision() const noexcept;

  virtual bool isComplex() const noexcept;

  friend Shared<INumber> add(const Shared<INumber> &lhs, const Shared<INumber> &rhs);

protected:
  bool equals(const Shared<IMathObject> &lhs, const Shared<IMathObject> &rhs) const noexcept override;

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
  multimethod.template add<Num, Num>([func = std::move(func)](const Shared<Num> &lhs, const Shared<Num> &rhs) {
    assert(lhs && rhs);
    return func(*lhs, *rhs);
  });
}

template <typename Num>
inline void INumber::registerNumberBinaryFunction(auto &multimethod, auto func) {
  multimethod.template add<Num, Num>(
    [func = std::move(func)](const Shared<Num> &lhs, const Shared<Num> &rhs) -> Shared<INumber> {
      assert(lhs && rhs);

      auto res = func(*lhs, *rhs);

      if (auto resUnwrapped = cast<INumber>(res.unwrapp())) {
        return resUnwrapped;
      }

      return makeShared<decltype(res)>(std::move(res));
    }
  );
}

}
