#pragma once

#include <memory>
#include <string>

#include "fintamath/core/IMathObject.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> parseExpr(const std::string &str);

}
