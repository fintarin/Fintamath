#pragma once

#include "fintamath/core/IMathObject.hpp"
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

  using Argument = Shared<IMathObject>;
  using Arguments = std::vector<Argument>;

  class FunctionMaker {
  public:
    FunctionMaker(const IFunction &inDefaultFunc);

    Shared<IFunction> make(Arguments inArgs) const;

    bool doArgumentsMatch(const Arguments &inArgs) const noexcept;

    const Declaration &getDeclaration() const noexcept;

    MathObjectClass getClass() const noexcept;

  private:
    std::reference_wrapper<const IFunction> defaultFunc;
  };

  using FunctionMakers = std::vector<FunctionMaker>;

private:
  using NameToFunctionMakersMap = std::unordered_map<std::string, FunctionMakers>;

  using ModifySelfCallback = std::function<Shared<IMathObject>(const IFunction &)>;

  using ModifyCallback = std::function<void(Argument &)>;

public:
  virtual const Declaration &getDeclaration() const noexcept = 0;

  std::string toString() const noexcept override;

  Shared<IMathObject> unwrapp() const noexcept override;

  const Arguments &getArguments() const noexcept;

  static const FunctionMakers *parseFunctionMakers(const std::string &str);

  static void preSimplify(Argument &arg);

  static void simplify(Argument &arg);

  static void solve(Argument &arg);

  static void approximate(Argument &arg);

protected:
  virtual Shared<IFunction> makeSelf(Arguments inArgs) const = 0;

  virtual Shared<IMathObject> preSimplifySelf() const;

  virtual Shared<IMathObject> simplifySelf() const;

  virtual Shared<IMathObject> solveSelf() const;

  virtual Shared<IMathObject> approximateSelf() const;

  void registerDefaultObject() const override;

  void initSelf(Arguments inArgs);

private:
  static bool areArgumentsNonNull(const Arguments &args);

  static bool doArgumentsMatch(const Declaration &decl, const Arguments &args) noexcept;

  static bool doArgumentsMatchNonVariadic(const Declaration &decl, const Arguments &args) noexcept;

  static bool doArgumentsMatchVariadic(const Declaration &decl, const Arguments &args) noexcept;

  static bool doesArgumentMatch(MathObjectClass expectedClass, const Argument &args) noexcept;

  static Arguments unwrappArguments(Arguments args) noexcept;

  static Arguments compressArguments(const Declaration &decl, MathObjectClass funcClass, Arguments args) noexcept;

  static void modify(Argument &arg, const ModifySelfCallback &modifySelf, const ModifyCallback &modify, const ModifyCallback &prevModify, FunctionState stateAfterModify);

  static void modifyArguments(Shared<IFunction> &func, const ModifyCallback &modify);

  static NameToFunctionMakersMap &getNameToFunctionMakersMap();

private:
  Arguments args;

  mutable FunctionState state = FunctionState::None;
};

}
