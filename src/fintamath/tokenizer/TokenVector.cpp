#include "fintamath/tokenizer/TokenVector.hpp"

namespace fintamath {

std::string tokenVectorToString(const TokenVector &tokenVector) {
  std::string res;

  for (const auto &token : tokenVector) {
    res += token;
  }

  return res;
}

}
