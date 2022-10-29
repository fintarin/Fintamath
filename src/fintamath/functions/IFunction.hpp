#pragma once

#include "fintamath/core/Defines.hpp"
#include "fintamath/core/IMathObject.hpp"
#include "fintamath/exceptions/FunctionCallException.hpp"
#include "fintamath/helpers/Parser.hpp"

namespace fintamath {
  class IFunction;
  using FunctionPtr = std::unique_ptr<IFunction>;

  class IFunction : virtual public IMathObject {
  public:
    enum class Type : uint16_t {
      None,    // 0 arguments
      Unary,   // 1 argument
      Binary,  // 2 arguments
      Ternary, // 3 arguments
      Any,     // undefined number of arguments
    };

  public:
    ~IFunction() override = default;

    virtual IFunction::Type getFunctionType() const = 0;

    template <typename... Args>
    MathObjectPtr operator()(const Args &...args) const {
      ArgumentsVector argsVect = {args...};
      return callAbstract(argsVect);
    }

    template <typename T, typename = std::enable_if_t<std::is_base_of_v<IFunction, T>>>
    static void addParser() {
      helpers::addParser<T>(parserMap);
    }

    static FunctionPtr parse(const std::string &parsedStr, IFunction::Type type = IFunction::Type::Any) {
      return helpers::parse<FunctionPtr>(parserMap, parsedStr, [type](const FunctionPtr &func) {
        return type == IFunction::Type::Any || func->getFunctionType() == type;
      });
    }

  protected:
    virtual MathObjectPtr callAbstract(const ArgumentsVector &argsVect) const = 0;

  private:
    static helpers::ParserMap<FunctionPtr> parserMap;
  };

  template <typename Derived, typename... Args>
  class IFunctionCRTP : virtual public IFunction, virtual public IMathObjectCRTP<Derived> {
  public:
    IFunctionCRTP(bool inIsTypeAny = false) : isTypeAny(inIsTypeAny) {
    }

    ~IFunctionCRTP() override = default;

    IFunction::Type getFunctionType() const final {
      return IFunction::Type(sizeof...(Args));
    }

  protected:
    virtual MathObjectPtr call(const ArgumentsVector &argsVect) const = 0;

    MathObjectPtr callAbstract(const ArgumentsVector &argsVect) const final {
      if (!isTypeAny && argsVect.size() != sizeof...(Args)) {
        throwInvalidInput(argsVect);
      }

      validateArgs(argsVect);

      return call(argsVect);
    }

    bool equals(const Derived & /*rhs*/) const final {
      return true;
    }

  private:
    void validateArgs(const ArgumentsVector &args) const {
      if (isTypeAny) {
        validateTypeAnyArgs(args);
      } else {
        validateArgs<0, Args...>(args);
      }
    }

    template <size_t i, typename Head, typename... Tail>
    void validateArgs(const ArgumentsVector &args) const {
      if (!args.at(i).get().instanceOf<Head>()) {
        throwInvalidInput(args);
      }

      validateArgs<i + 1, Tail...>(args);
    }

    template <size_t>
    void validateArgs(const ArgumentsVector & /*unused*/) const {
      // validation passes
    }

    void validateTypeAnyArgs(const ArgumentsVector &args) const {
      for (const auto &arg : args) {
        if ((!arg.get().instanceOf<Args>() && ...)) {
          throwInvalidInput(args);
        }
      }
    }

    void throwInvalidInput(const ArgumentsVector &argsVect) const {
      std::vector<std::string> argNamesVect(argsVect.size());

      for (size_t i = 0; i < argNamesVect.size(); i++) {
        argNamesVect.at(i) = argsVect.at(i).get().toString();
      }

      throw FunctionCallException(toString(), argNamesVect);
    }

    bool isTypeAny;
  };
}
