#include "fintamath/expressions/functions/arithmetic/AddOper.hpp"

#include "fintamath/core/MathObjectUtils.hpp"
#include "fintamath/expressions/functions/arithmetic/Add.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(AddOper)

const AddOper::OperatorDeclaration addOperDeclaration = {
  .functionDeclarion = {
    .expressionDeclarion = {
      .domainAndRangeVariants = {{
        .returnClass = INumber::getClassStatic(),
        .childClasses = {INumber::getClassStatic(), INumber::getClassStatic()},
      }},
      .isVariadic = false,
    },
    .functionName = "+",
  },
  .operatorPriority = AddOper::Priority::Addition,
};

std::unique_ptr<IFunction> AddOper::makeFunction(Children inChildren) const {
  return makeObject<Add>(std::move(inChildren));
}

}
