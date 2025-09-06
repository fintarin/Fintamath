#pragma once

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectUtils.hpp"

#include <functional>
#include <optional>
#include <unordered_map>

namespace fintamath {

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

enum class FunctionState : uint8_t {
  None,
  PreSimplify,
  Simplify,
  Solve,
  Approximate,
};

class IFunction : public IMathObject {
  FINTAMATH_INTERFACE_BODY(IFunction, IMathObject)

public:
  struct Declaration {
    std::string name;
    std::vector<MathObjectClass> argumentClasses;
    MathObjectClass returnClass = {};
    std::optional<OperatorPriority> operatorPriority = std::nullopt;
    bool isVariadic = false;
  };

  using Arguments = std::vector<SharedRef<IMathObject>>;

  class FunctionMaker {
  public:
    FunctionMaker(const IFunction &inDefaultFunc);

    SharedRef<IFunction> make(Arguments inArgs) const;

    bool doArgumentsMatch(const Arguments &inArgs) const noexcept;

    const Declaration &getDeclaration() const noexcept;

    MathObjectClass getClass() const noexcept;

  private:
    std::reference_wrapper<const IFunction> defaultFunc;
  };

  using FunctionMakers = std::vector<FunctionMaker>;

private:
  using NameToFunctionMakersMap = std::unordered_map<std::string, FunctionMakers>;

public:
  virtual const Declaration &getDeclaration() const noexcept = 0;

  std::string toString() const noexcept override;

  SharedPtr<IMathObject> unwrapp() const noexcept override;

  const Arguments &getArguments() const noexcept;

  static const FunctionMakers *parseFunctionMakers(const std::string &str);

  static void compress(SharedRef<IMathObject> &arg);

  static void preSimplify(SharedRef<IMathObject> &arg);

  static void simplify(SharedRef<IMathObject> &arg);

  static void solve(SharedRef<IMathObject> &arg);

  static void approximate(SharedRef<IMathObject> &arg);

protected:
  virtual SharedRef<IFunction> makeSelf(Arguments inArgs) const = 0;

  virtual SharedPtr<IMathObject> compressSelf() const;

  virtual SharedPtr<IMathObject> preSimplifySelf() const;

  virtual SharedPtr<IMathObject> simplifySelf() const;

  virtual SharedPtr<IMathObject> solveSelf() const;

  virtual SharedPtr<IMathObject> approximateSelf() const;

  bool equals(const SharedRef<IMathObject> &lhs, const SharedRef<IMathObject> &rhs) const noexcept override;

  void registerDefaultObject() const override;

  void initSelf(Arguments inArgs);

private:
  static bool doArgumentsMatch(const Declaration &decl, const Arguments &args) noexcept;

  static bool doArgumentsMatchNonVariadic(const Declaration &decl, const Arguments &args) noexcept;

  static bool doArgumentsMatchVariadic(const Declaration &decl, const Arguments &args) noexcept;

  static bool doesArgumentMatch(MathObjectClass expectedClass, const SharedRef<IMathObject> &arg) noexcept;

  static Arguments unwrappArguments(Arguments args) noexcept;

  static void appendVariadicFunctionArgument(const SharedRef<IMathObject> &arg, const MathObjectClass &selfClass, Arguments &outArgs);

  static void appendVariadicFunctionArguments(const IFunction &func, const MathObjectClass &selfClass, Arguments &outArgs) noexcept;

  template <typename ModifySelfCallback, typename ModifyCallback, typename PreviousModifyCallback>
  static void modify(SharedRef<IMathObject> &arg, const ModifySelfCallback &modifySelf, const ModifyCallback &modify, const PreviousModifyCallback &prevModify, FunctionState stateAfterModify);

  template <typename ModifyCallback>
  static void modifyFunctionArguments(SharedRef<IFunction> &func, const ModifyCallback &modify);

  static NameToFunctionMakersMap &getNameToFunctionMakersMap();

private:
  Arguments args;

  mutable FunctionState state = FunctionState::None;

  static std::mutex modifyStateMutex;
};

template <typename ModifySelfCallback, typename ModifyCallback, typename PreviousModifyCallback>
inline void IFunction::modify(SharedRef<IMathObject> &arg, const ModifySelfCallback &modifySelf, const ModifyCallback &modify, const PreviousModifyCallback &prevModify, FunctionState stateAfterModify) {
  auto funcPtr = cast<IFunction>(arg);
  if (!funcPtr || funcPtr->state >= stateAfterModify) {
    return;
  }

  prevModify(arg);

  if (arg != funcPtr) {
    funcPtr = cast<IFunction>(arg);

    if (!funcPtr) {
      return;
    }
  }

  auto func = std::move(funcPtr).toRef();
  modifyFunctionArguments(func, modify);
  arg = func;

  if (auto resPtr = modifySelf(*func)) {
    auto res = std::move(resPtr).toRef();
    modify(res);
    arg = std::move(res);
  }
  else {
    const std::lock_guard lock(modifyStateMutex);
    func->state = std::max(stateAfterModify, func->state);
  }
}

template <typename ModifyCallback>
inline void IFunction::modifyFunctionArguments(SharedRef<IFunction> &func, const ModifyCallback &modify) {
  const Arguments &oldArgs = func->getArguments();
  std::optional<Arguments> newArgsFound;
  size_t argIndex = 0;

  for (; argIndex < oldArgs.size(); argIndex++) {
    const SharedRef<IMathObject> &oldArg = oldArgs[argIndex];
    SharedRef<IMathObject> newArg = oldArg;
    modify(newArg);

    if (newArg != oldArg) {
      newArgsFound = oldArgs;
      (*newArgsFound)[argIndex] = newArg;
      break;
    }
  }

  if (!newArgsFound) {
    return;
  }

  Arguments &newArgs = *newArgsFound;

  argIndex++;

  for (; argIndex < newArgs.size(); argIndex++) {
    modify(newArgs[argIndex]);
  }

  func = func->makeSelf(std::move(newArgs));
}

}
