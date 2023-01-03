#pragma once

#include <string>
#include <vector>

namespace fintamath {

using TokenVector = std::vector<std::string>;

std::string tokenVectorToString(const TokenVector &tokenVector);

}
