#pragma once

#include <utility>

#include "fintamath/exceptions/Exception.h"

namespace fintamath {
  class UndefinedException : public Exception {
  public:
    ~UndefinedException() override = default;
  };
}
