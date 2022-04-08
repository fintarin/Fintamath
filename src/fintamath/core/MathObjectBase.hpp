#pragma once

#include <memory>
#include <sstream>
#include <string>

namespace fintamath {
  class MathObjectBase {
  public:
    virtual ~MathObjectBase() = default;

    virtual std::string toString() const = 0;

    virtual std::unique_ptr<MathObjectBase> clone() const = 0;

    bool operator==(const MathObjectBase &rhs) const {
      return equals(rhs);
    }

    bool operator!=(const MathObjectBase &rhs) const {
      return !equals(rhs);
    }

    template <typename T, typename = std::enable_if_t<std::is_base_of_v<MathObjectBase, T>>>
    const T &to() const {
      return dynamic_cast<const T &>(*this);
    }

    template <typename T, typename = std::enable_if_t<std::is_base_of_v<MathObjectBase, T>>>
    bool is() const {
      return dynamic_cast<const T *>(this);
    }

  protected:
    virtual bool equals(const MathObjectBase &rhs) const = 0;
  };

  template <typename LhsType, typename RhsType,
            typename = std::enable_if_t<std::is_base_of_v<MathObjectBase, LhsType> && std::is_convertible_v<RhsType, LhsType> &&
                                        !std::is_same_v<LhsType, RhsType>>>
  bool operator==(const LhsType &lhs, const RhsType &rhs) {
    return lhs == LhsType(rhs);
  }

  template <typename RhsType, typename LhsType,
            typename = std::enable_if_t<std::is_base_of_v<MathObjectBase, RhsType> && std::is_convertible_v<LhsType, RhsType> &&
                                        !std::is_same_v<LhsType, RhsType>>>
  bool operator==(const LhsType &lhs, const RhsType &rhs) {
    return RhsType(lhs) == rhs;
  }

  template <typename LhsType, typename RhsType,
            typename = std::enable_if_t<std::is_base_of_v<MathObjectBase, LhsType> && std::is_convertible_v<RhsType, LhsType> &&
                                        !std::is_same_v<LhsType, RhsType>>>
  bool operator!=(const LhsType &lhs, const RhsType &rhs) {
    return lhs != LhsType(rhs);
  }

  template <typename RhsType, typename LhsType,
            typename = std::enable_if_t<std::is_base_of_v<MathObjectBase, RhsType> && std::is_convertible_v<LhsType, RhsType> &&
                                        !std::is_same_v<LhsType, RhsType>>>
  bool operator!=(const LhsType &lhs, const RhsType &rhs) {
    return RhsType(lhs) != rhs;
  }

  inline std::ostream &operator<<(std::ostream &out, const MathObjectBase &rhs) {
    return out << rhs.toString();
  }
}
