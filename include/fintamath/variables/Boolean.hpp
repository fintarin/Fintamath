#pragma once

#include <string>

#include "fintamath/core/ClassBody.hpp"
#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/IWithEqualsOperators.hpp"

namespace fintamath {

class Boolean : public IMathObject, public IWithEqualsOperators<Boolean> {
  FINTAMATH_CLASS_BODY(Boolean, IMathObject)

public:
  Boolean();

  template <std::same_as<bool> Bool>
  Boolean(const Bool rhs) noexcept : val(rhs) {}

  explicit Boolean(std::string_view str);

  std::string toString() const noexcept override;

  operator bool() const noexcept;

protected:
  bool equals(const SharedRef<IMathObject> &self, const SharedRef<IMathObject> &rhs) const noexcept override;

  bool equals(const Boolean &rhs) const noexcept override;

private:
  bool val;

  static constexpr std::string_view trueStr = "True";

  static constexpr std::string_view falseStr = "False";
};

}
