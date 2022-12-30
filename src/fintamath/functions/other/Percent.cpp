#include "fintamath/functions/other/Percent.hpp"

#include "fintamath/exceptions/UndefinedUnaryOpearatorException.hpp"
#include "fintamath/numbers/Rational.hpp"

namespace fintamath {

constexpr int64_t PERCENT_VALUE = 100;

Expression Percent::call(const std::vector<std::reference_wrapper<const IMathObject>> &argsVect) const {
  const auto &rhs = argsVect.at(0).get();

  if (!rhs.is<Integer>()) {
    throw UndefinedUnaryOpearatorException("%", rhs.toString(), UndefinedUnaryOpearatorException::Type::Postfix);
  }

  return *(helpers::Converter::convert(argsVect.at(0), Rational())->to<Rational>() / PERCENT_VALUE).simplify();
}

}
