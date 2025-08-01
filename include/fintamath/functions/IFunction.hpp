#pragma once

#include "fintamath/core/IMathObject.hpp"
#include <functional>
#include <optional>
#include <unordered_map>

namespace fintamath {

class IFunction : public IMathObject {
  FINTAMATH_INTERFACE_BODY(IFunction, IMathObject)

public:
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
  using NameToFunctionMakersMap = std::unordered_map<std::string, FunctionMakers>;

public:
  virtual const Declaration &getDeclaration() const noexcept = 0;

  std::string toString() const noexcept override;

  Shared<IMathObject> unwrapp() const noexcept override;

  const Arguments &getArguments() const noexcept;

  static const FunctionMakers *parseFunctionMakers(const std::string &str);

protected:
  virtual Shared<IFunction> makeSelf(Arguments inArgs) const = 0;

  void registerDefaultObject() const override;

  void initSelf(Arguments inArgs);

private:
  static void validateArgumentsNonNull(const Arguments &inArgs);

  static void validateArgumentsMatch(const Declaration &decl, const Arguments &inArgs);

  static bool doArgumentsMatch(const Declaration &decl, const Arguments &inArgs) noexcept;

  static bool doArgumentsMatchNonVariadic(const Declaration &decl, const Arguments &inArgs) noexcept;

  static bool doArgumentsMatchVariadic(const Declaration &decl, const Arguments &inArgs) noexcept;

  static bool doesArgumentMatch(MathObjectClass expectedClass, const Argument &inArgs) noexcept;

  static Arguments unwrappArguments(Arguments inArgs) noexcept;

  static Arguments compressArguments(const Declaration &decl, MathObjectClass funcClass, Arguments inArgs) noexcept;

  static NameToFunctionMakersMap &getNameToFunctionMakersMap();

private:
  Arguments args;
};

}
