#pragma once

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectUtils.hpp"

#include <functional>
#include <optional>
#include <span>
#include <unordered_map>

namespace fintamath {

enum class FunctionState : uint8_t {
  Raw,
  PreSimplify,
  Simplify,
  Solve,
  Approximate,
};

enum class OperatorPriority : uint8_t {
  Exponentiation, // e.g.  a ^ b
  PostfixUnary,   // e.g.  a!
  PrefixUnary,    // e.g.  -a
  Multiplication, // e.g.  a * b
  Addition,       // e.g.  a + b
  Modulo,         // e.g.  a mod b
  Comparison,     // e.g.  a = b
  Conjunction,    // e.g.  a & b
  Disjunction,    // e.g.  a | b
  Implication,    // e.g.  a -> b
  Equivalence,    // e.g.  a <-> b
  Comma,          // e.g.  a , b
};

class IFunction : public IMathObject {
  FINTAMATH_INTERFACE_BODY(IFunction, IMathObject)

public:
  using ArgSpan = std::span<const SharedRef<IMathObject>>;

  using ArgSpanMutable = std::span<SharedRef<IMathObject>>;

  using ArgVector = std::vector<SharedRef<IMathObject>>;

  struct OperatorDeclaration {
    OperatorPriority priority = OperatorPriority::Exponentiation;
    bool isAssociative = false;
  };

  struct Declaration {
    std::string name;
    std::vector<MathObjectClass> argClasses;
    MathObjectClass returnClass = nullptr;
    std::optional<OperatorDeclaration> operatorDeclaration = std::nullopt;
    bool isVariadic = false;
  };

  class FunctionMaker {
  public:
    FunctionMaker(const IFunction &inDefaultFunc);

    SharedRef<IFunction> make(ArgVector args) const;

    bool doArgsMatch(ArgSpan args) const noexcept;

    const Declaration &getDeclaration() const noexcept;

    MathObjectClass getClass() const noexcept;

  private:
    std::reference_wrapper<const IFunction> defaultFunc;
  };

  using FunctionMakers = std::vector<FunctionMaker>;

public:
  virtual const Declaration &getDeclaration() const noexcept = 0;

  virtual ArgSpan getArgs() const noexcept = 0;

  std::string toString() const noexcept override;

  static const FunctionMakers *parseFunctionMakers(const std::string &str);

  static void simplify(SharedRef<IMathObject> &arg);

  static void solve(SharedRef<IMathObject> &arg);

  static void approximate(SharedRef<IMathObject> &arg);
  
protected:
  IFunction() = default;

  explicit IFunction(const Declaration &inDeclaration, ArgSpan inArgs);

  virtual SharedRef<IFunction> makeSelf(ArgVector args) const = 0;

  virtual SharedRef<IFunction> makeSelf(ArgSpan args) const = 0;

  virtual SharedPtr<IMathObject> preSimplifySelf() const;

  virtual SharedPtr<IMathObject> simplifySelf() const;

  virtual SharedPtr<IMathObject> solveSelf() const;

  virtual SharedPtr<IMathObject> approximateSelf() const;

  bool equals(const SharedRef<IMathObject> &self, const SharedRef<IMathObject> &rhs) const noexcept final;

  void registerDefaultObject() const override;

private:
  using NameToFunctionMakersMap = std::unordered_map<std::string, FunctionMakers>;

private:
  bool hasUndefined() const noexcept;

  static bool doArgsMatch(const Declaration &decl, const ArgSpan &args) noexcept;

  static bool doArgsMatchNonVariadic(const Declaration &decl, const ArgSpan &args) noexcept;

  static bool doArgsMatchVariadic(const Declaration &decl, const ArgSpan &args) noexcept;

  static bool doesArgMatch(MathObjectClass expectedClass, const SharedRef<IMathObject> &arg) noexcept;

  static void preSimplify(SharedRef<IMathObject> &arg);

  template <typename ModifySelfCallback, typename ModifyCallback, typename PreviousModifyCallback>
  static void modify(SharedRef<IMathObject> &arg, const ModifySelfCallback &modifySelf, const ModifyCallback &modify, const PreviousModifyCallback &prevModify, FunctionState stateAfterModify);

  static NameToFunctionMakersMap &getNameToFunctionMakersMap();

private:
  mutable FunctionState state = FunctionState::Raw;
};

template <std::derived_from<IFunction> T>
SharedRef<T> makeShared(typename T::Args args) {
  return makeShared<T>(T(std::move(args)));
}

template <typename ModifySelfCallback, typename ModifyCallback, typename PreviousModifyCallback>
inline void IFunction::modify(SharedRef<IMathObject> &arg, const ModifySelfCallback &modifySelf, const ModifyCallback &modify, const PreviousModifyCallback &prevModify, FunctionState stateAfterModify) {
  auto func = cast<IFunction>(arg);
  if (func && func->state >= stateAfterModify) {
    return;
  }

  prevModify(arg);

  if (!func) {
    return;
  }

  for (;;) {
    func = cast<IFunction>(arg);
    if (!func) {
      modify(arg);
      break;
    }

    SharedPtr<IMathObject> res = modifySelf(*func);
    if (!res) {
      func->state = stateAfterModify;
      break;
    }

    arg = res.toRef();
  }
}

}
