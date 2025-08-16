#include "fintamath/numbers/NumberFunctions.hpp"

#include "fintamath/core/Converter.hpp"
#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

namespace fintamath {

namespace {

template <typename NumberType>
void addFunctionToBinaryMultimethod(auto &multi, auto func) {
  multi.template add<NumberType, NumberType>([func = std::move(func)](const Shared<NumberType> &lhs, const Shared<NumberType> &rhs) {
    auto res = makeShared<NumberType>(func(*lhs, *rhs));
    auto resUnwrapped = cast<INumber>(res->unwrapp());
    return resUnwrapped ? resUnwrapped : res;
  });
}

auto makeBinaryMultimethod(auto func) {
  detail::MultiMethod<Shared<INumber>(const Shared<INumber> &, const Shared<INumber> &)> multi;
  addFunctionToBinaryMultimethod<Integer>(multi, std::move(func));
  addFunctionToBinaryMultimethod<Rational>(multi, std::move(func));
  addFunctionToBinaryMultimethod<Real>(multi, std::move(func));
  return multi;
}

Shared<INumber> callBinaryMultimethod(const auto &multi, const Shared<INumber> &lhs, const Shared<INumber> &rhs) {
  if (!lhs) {
    throw InvalidInputException("Lhs is null");
  }
  if (!rhs) {
    throw InvalidInputException("Rhs is null");
  }

  if (lhs->getClass() == rhs->getClass()) {
    return multi(lhs, rhs);
  }
  if (auto convRhs = convert(*lhs, *rhs)) {
    return multi(lhs, convRhs);
  }
  if (auto convLhs = convert(*rhs, *lhs)) {
    return multi(convLhs, rhs);
  }
  return nullptr;
}

}

Shared<INumber> operator+(const Shared<INumber> &lhs, const Shared<INumber> &rhs) {
  static const auto multiAdd = makeBinaryMultimethod([](const auto &inLhs, const auto &inRhs) {
    return inLhs + inRhs;
  });
  return callBinaryMultimethod(multiAdd, lhs, rhs);
}

}
