#include "fintamath/numbers/NumberFunctions.hpp"

#include "fintamath/core/Converter.hpp"
#include "fintamath/core/MathObjectUtils.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

namespace fintamath {

namespace {

template <typename Number>
void addFunctionToBinaryMultimethod(auto &multi, auto func) {
  multi.template add<Number, Number>([func = std::move(func)](const Number &lhs, const Number &rhs) {
    return makeObject<Number>(func(lhs, rhs));
  });
}

auto makeBinaryMultimethod(auto func) {
  detail::MultiMethod<std::unique_ptr<INumber>(const INumber &, const INumber &)> multi;
  addFunctionToBinaryMultimethod<Integer>(multi, std::move(func));
  addFunctionToBinaryMultimethod<Rational>(multi, std::move(func));
  addFunctionToBinaryMultimethod<Real>(multi, std::move(func));
  return multi;
}

std::unique_ptr<INumber> callBinaryMultimethod(const auto &multi, const INumber &lhs, const INumber &rhs) {
  if (lhs.getClass() == rhs.getClass()) {
    return multi(lhs, rhs);
  }
  if (auto convRhs = convert(lhs, rhs)) {
    return multi(lhs, *convRhs);
  }
  if (auto convLhs = convert(rhs, lhs)) {
    return multi(*convLhs, rhs);
  }
  return nullptr;
}

}

std::unique_ptr<INumber> operator+(const INumber &lhs, const INumber &rhs) {
  static const auto multiAdd = makeBinaryMultimethod([](const auto &inLhs, const auto &inRhs) {
    return inLhs + inRhs;
  });
  return callBinaryMultimethod(multiAdd, lhs, rhs);
}

}
