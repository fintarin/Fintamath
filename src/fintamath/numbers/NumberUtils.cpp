#include "fintamath/numbers/NumberUtils.hpp"

#include <cstddef>
#include <string>

namespace fintamath::detail {

std::string removeLeadingZeroes(std::string str) {
  size_t firstDigit = 0;
  if (str.front() == '-') {
    firstDigit++;
  }

  const size_t firstNonZeroDigit = str.find_first_not_of('0', firstDigit);

  if (firstNonZeroDigit == std::string::npos) {
    str.insert(firstDigit, "0");
  }
  else if (firstNonZeroDigit > firstDigit) {
    str.erase(firstDigit, firstNonZeroDigit - firstDigit);
  }

  return str;
}

}
