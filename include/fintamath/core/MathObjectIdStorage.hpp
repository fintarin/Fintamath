#pragma once

#include <unordered_map>

#include "fintamath/core/MathObjectClass.hpp"

namespace fintamath {

class MathObjectIdStorage {
  using MathObjectClassToIdMap = std::unordered_map<MathObjectClass, size_t>;

public:
  static size_t get(MathObjectClass objClass) noexcept;

  static void add(MathObjectClass objClass) noexcept;

private:
  static MathObjectClassToIdMap &getMap() noexcept;

private:
  static inline size_t maxId = 1;
};

}
