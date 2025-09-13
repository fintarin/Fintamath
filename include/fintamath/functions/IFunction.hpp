#pragma once

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectUtils.hpp"

#include <functional>
#include <optional>
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
  struct OperatorDeclaration {
    OperatorPriority priority = OperatorPriority::Exponentiation;
    bool isAssociative = false;
  };

  struct Declaration {
    std::string name;
    std::vector<MathObjectClass> argumentClasses;
    MathObjectClass returnClass = nullptr;
    std::optional<OperatorDeclaration> operatorDeclaration = std::nullopt;
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

public:
  IFunction() = default;

  explicit IFunction(const Declaration &inDeclaration, Arguments inArgs);

  virtual const Declaration &getDeclaration() const noexcept = 0;

  std::string toString() const noexcept override;

  const Arguments &getArguments() const noexcept;

  static const FunctionMakers *parseFunctionMakers(const std::string &str);

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

  bool equals(const SharedRef<IMathObject> &self, const SharedRef<IMathObject> &rhs) const noexcept final;

  void registerDefaultObject() const override;

private:
  using NameToFunctionMakersMap = std::unordered_map<std::string, FunctionMakers>;

private:
  bool hasUndefined() const noexcept;

  static bool doArgumentsMatch(const Declaration &decl, const Arguments &args) noexcept;

  static bool doArgumentsMatchNonVariadic(const Declaration &decl, const Arguments &args) noexcept;

  static bool doArgumentsMatchVariadic(const Declaration &decl, const Arguments &args) noexcept;

  static bool doesArgumentMatch(MathObjectClass expectedClass, const SharedRef<IMathObject> &arg) noexcept;

  static Arguments unwrappArguments(Arguments args) noexcept;

  static void compress(SharedRef<IMathObject> &arg);

  static void preSimplify(SharedRef<IMathObject> &arg);

  template <typename ModifySelfCallback, typename ModifyCallback, typename PreviousModifyCallback>
  static void modify(SharedRef<IMathObject> &arg, const ModifySelfCallback &modifySelf, const ModifyCallback &modify, const PreviousModifyCallback &prevModify, FunctionState stateAfterModify);

  template <typename ModifyCallback>
  static void modifyFunctionArguments(SharedRef<IFunction> &func, const ModifyCallback &modify);

  static NameToFunctionMakersMap &getNameToFunctionMakersMap();

private:
  Arguments args;

  mutable FunctionState state = FunctionState::Raw;

  static std::mutex modifyStateMutex;
};

template <std::derived_from<IFunction> T>
SharedRef<T> makeShared(std::initializer_list<IFunction::Arguments::value_type> inArgs) {
  return makeShared<T>(IFunction::Arguments(inArgs));
}

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
