#pragma once

#include <unordered_map>

#include "fintamath/core/MathObjectType.hpp"

namespace fintamath {

bool isBaseOf(const MathObjectType &toType, const MathObjectType &fromType);

namespace detail {

class MathObjectBoundTypes final {
  using enum MathObjectType::Id;

  using TypeIdToBoundTypeIdMap = std::unordered_map<size_t, size_t>;

  static TypeIdToBoundTypeIdMap &getMap() {
    static TypeIdToBoundTypeIdMap typeIdToBoundTypeIdMap{
        makeTypeIdPair(IMathObject, None),
        makeTypeIdPair(IArithmetic, ILiteral),
        makeTypeIdPair(IArithmetic, ILiteral),
        makeTypeIdPair(IExpression, IComparable),
        makeTypeIdPair(IUnaryExpression, IBinaryExpression),
        makeTypeIdPair(IBinaryExpression, IPolynomExpression),
        makeTypeIdPair(IPolynomExpression, IComparable),
        makeTypeIdPair(IComparable, ILiteral),
        makeTypeIdPair(INumber, ILiteral),
        makeTypeIdPair(IInteger, ILiteral),
        makeTypeIdPair(ILiteral, IFunction),
        makeTypeIdPair(IConstant, IFunction),
        makeTypeIdPair(IFunction, None),
        makeTypeIdPair(IOperator, None),
    };
    return typeIdToBoundTypeIdMap;
  }

public:
  static void bindTypes(const MathObjectType &type, const MathObjectType &boundType) {
    getMap().emplace(type.getId(), boundType.getId());
  }

  friend bool fintamath::isBaseOf(const MathObjectType &toType, const MathObjectType &fromType);

private:
  static std::pair<size_t, size_t> makeTypeIdPair(const MathObjectType::Id lhs, const MathObjectType::Id rhs) {
    return {static_cast<size_t>(lhs), static_cast<size_t>(rhs)};
  }
};

}

inline bool isBaseOf(const MathObjectType &toType, const MathObjectType &fromType) {
  const auto &map = detail::MathObjectBoundTypes::getMap();

  if (const auto boundaries = map.find(toType.getId()); boundaries != map.end()) {
    return fromType.getId() >= boundaries->first && fromType.getId() < boundaries->second;
  }

  return toType == fromType;
}

}
