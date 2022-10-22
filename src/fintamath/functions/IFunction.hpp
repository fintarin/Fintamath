#pragma once

#include "fintamath/core/Defines.hpp"
#include "fintamath/core/IMathObject.hpp"
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
        throwInvalidSize(argsVect.size());
      }

      validateArgs(argsVect);

      return call(argsVect);
    }

    bool equals(const Derived & /*rhs*/) const final {
      return true;
    }

  private:
    void validateArgs(const ArgumentsVector &argsVect) const {
      if (isTypeAny) {
        validateTypeAnyArgs(argsVect);
      } else {
        validateArgs<0, Args...>(argsVect);
      }
    }

    template <int32_t i, typename Head, typename... Tail>
    void validateArgs(const ArgumentsVector &argsVect) const {
      if (!argsVect.at(i).get().instanceOf<Head>()) {
        throwInvalidArgument(i);
      }

      validateArgs<i + 1, Tail...>(argsVect);
    }

    template <int32_t>
    void validateArgs(const ArgumentsVector & /*unused*/) const {
      // validation passes
    }

    void validateTypeAnyArgs(const ArgumentsVector &argsVect) const {
      for (size_t i = 0; i < argsVect.size(); i++) {
        if ((!argsVect.at(i).get().instanceOf<Args>() && ...)) {
          throwInvalidArgument(i);
        }
      }
    }

    void throwInvalidArgument(size_t argPos) const {
      throw std::invalid_argument(exceptionPrefix() + "unexpected argument at position " + std::to_string(argPos + 1));
    }

    void throwInvalidSize(size_t size) const {
      throw std::invalid_argument(exceptionPrefix() + std::to_string(sizeof...(Args)) + " arguments required, but " +
                                  std::to_string(size) + " obtained");
    }

    std::string exceptionPrefix() const {
      return "\"" + toString() + "\": ";
    }

    bool isTypeAny;
  };
}
