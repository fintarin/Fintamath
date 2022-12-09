#include "fintamath/functions/logarithms/Log.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {
  std::string Log::toString() const {
    return "log";
  }

  std::string Log::getClassName() const {
    return "Log";
  }

  Expression Log::call(const std::vector<std::reference_wrapper<const IMathObject>> &argsVect) const {
    return *log(helpers::Converter::convert<Real>(argsVect.at(0)), helpers::Converter::convert<Real>(argsVect.at(1)))
                .simplify();
  }
}
