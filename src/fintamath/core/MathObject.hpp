#pragma once

#include <memory>
#include <sstream>
#include <string>

#include "fintamath/meta/Converter.hpp"

#define FINTAMATH_CALL_OPERATOR(OPER)                                                                                  \
  if (rhs.is<Derived>()) {                                                                                             \
    return *this OPER rhs.to<Derived>();                                                                               \
  }                                                                                                                    \
  if (auto tmp = meta::convertRhsToLhsType(*this, rhs); tmp != nullptr) {                                              \
    return *this OPER * tmp;                                                                                           \
  }                                                                                                                    \
  if (auto tmp = meta::convertRhsToLhsType(rhs, *this); tmp != nullptr) {                                              \
    return *tmp OPER rhs;                                                                                              \
  }                                                                                                                    \
  return false

namespace fintamath {
  class MathObject;
  using MathObjectPtr = std::unique_ptr<MathObject>;

  class MathObject {
  public:
    virtual ~MathObject() = default;

    virtual std::string toString() const = 0;

    virtual MathObjectPtr clone() const = 0;

    template <typename T>
    bool is() const {
      return typeid(*this) == typeid(T);
    }

    template <typename T>
    bool instanceOf() const {
      return dynamic_cast<const T *>(this);
    }

    template <typename T>
    const T &to() const {
      return dynamic_cast<const T &>(*this);
    }

    friend bool operator==(const MathObject &lhs, const MathObject &rhs);

    friend bool operator!=(const MathObject &lhs, const MathObject &rhs);

  protected:
    virtual bool equalsAbstract(const MathObject &rhs) const = 0;
  };

  inline bool operator==(const MathObject &lhs, const MathObject &rhs) {
    return lhs.equalsAbstract(rhs);
  }

  inline bool operator!=(const MathObject &lhs, const MathObject &rhs) {
    return !lhs.equalsAbstract(rhs);
  }

  template <typename Derived>
  class MathObjectImpl : virtual public MathObject {
  public:
    ~MathObjectImpl() override = default;

    MathObjectPtr clone() const final {
      return std::make_unique<Derived>(to<Derived>());
    }

    bool operator==(const Derived &rhs) const {
      return equals(rhs);
    }

    bool operator!=(const Derived &rhs) const {
      return !equals(rhs);
    }

  protected:
    virtual bool equals(const Derived &rhs) const = 0;

    bool equalsAbstract(const MathObject &rhs) const final {
      FINTAMATH_CALL_OPERATOR(==);
    }
  };

  template <typename LhsType, typename RhsType,
            typename = std::enable_if_t<std::is_base_of_v<MathObject, LhsType> &&
                                        std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
  bool operator==(const LhsType &lhs, const RhsType &rhs) {
    return lhs == LhsType(rhs);
  }

  template <typename RhsType, typename LhsType,
            typename = std::enable_if_t<std::is_base_of_v<MathObject, RhsType> &&
                                        std::is_convertible_v<LhsType, RhsType> && !std::is_same_v<LhsType, RhsType>>>
  bool operator==(const LhsType &lhs, const RhsType &rhs) {
    return RhsType(lhs) == rhs;
  }

  template <typename LhsType, typename RhsType,
            typename = std::enable_if_t<std::is_base_of_v<MathObject, LhsType> &&
                                        std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
  bool operator!=(const LhsType &lhs, const RhsType &rhs) {
    return lhs != LhsType(rhs);
  }

  template <typename RhsType, typename LhsType,
            typename = std::enable_if_t<std::is_base_of_v<MathObject, RhsType> &&
                                        std::is_convertible_v<LhsType, RhsType> && !std::is_same_v<LhsType, RhsType>>>
  bool operator!=(const LhsType &lhs, const RhsType &rhs) {
    return RhsType(lhs) != rhs;
  }

  inline std::ostream &operator<<(std::ostream &out, const MathObject &rhs) {
    return out << rhs.toString();
  }
}

#undef FINTAMATH_CALL_OPERATOR
