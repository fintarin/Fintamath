#include "fintamath/functions/ntheory/Mod.hpp"

#include <memory>
#include <utility>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectUtils.hpp"
#include "fintamath/core/MultiMethod.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/literals/constants/Undefined.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/Integer.hpp"

namespace fintamath {

using namespace detail;

std::unique_ptr<IMathObject> Mod::call(const ArgumentRefVector &argVect) const {
  const auto &lhs = cast<INumber>(argVect.front().get());
  const auto &rhs = cast<INumber>(argVect.back().get());

  if (rhs == Integer(0)) {
    return Undefined{}.clone();
  }

  return multiModSimplify(lhs, rhs);
}

std::unique_ptr<IMathObject> Mod::multiModSimplify(const INumber &lhs, const INumber &rhs) {
  // TODO: implement non-integer modulo

  static const auto multiMod = [] {
    static MultiMethod<std::unique_ptr<IMathObject>(const INumber &, const INumber &)> outMultiMod;

    outMultiMod.add<Integer, Integer>([](const Integer &inLhs, const Integer &inRhs) {
      Integer mod = inLhs % inRhs;

      if (mod != 0 && inLhs.sign() != inRhs.sign()) {
        mod += inRhs;
      }

      return std::move(mod).clone();
    });

    return outMultiMod;
  }();

  return multiMod(lhs, rhs);
}

}
