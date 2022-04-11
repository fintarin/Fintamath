#pragma once

#include <memory>
#include <sstream>
#include <string>

namespace fintamath {
  class MathObject {
  public:
    virtual ~MathObject() = default;

    virtual std::string toString() const = 0;

    virtual std::unique_ptr<MathObject> clone() const = 0;

    bool operator==(const MathObject &rhs) const {
      return equals(rhs);
    }

    bool operator!=(const MathObject &rhs) const {
      return !equals(rhs);
    }

    template <typename T, typename = std::enable_if_t<std::is_base_of_v<MathObject, T>>>
    const T &to() const {
      return dynamic_cast<const T &>(*this);
    }

    template <typename T, typename = std::enable_if_t<std::is_base_of_v<MathObject, T>>>
    bool is() const {
      return dynamic_cast<const T *>(this);
    }

  protected:
    virtual bool equals(const MathObject &rhs) const = 0;
  };

  template <typename Derived>
  class MathObjectImpl : virtual public MathObject {
  public:
    ~MathObjectImpl() override = default;

    std::unique_ptr<MathObject> clone() const final {
      return std::make_unique<Derived>(to<Derived>());
    }

  protected:
    virtual bool equals(const Derived &rhs) const = 0;

    bool equals(const MathObject &rhs) const final {
      if (!rhs.is<Derived>()) {
        return false;
      }
      return equals(rhs.to<Derived>());
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
