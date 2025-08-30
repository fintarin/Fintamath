#include <benchmark/benchmark.h>

#include "fintamath/core/CoreUtils.hpp"
#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionFunctions.hpp"

using namespace fintamath;

namespace {

constexpr size_t functionsNum = 10'000;

std::string getAddExprStr() {
  std::string str = "x";
  repeat(functionsNum, [&str] {
    str += "+x";
  });
  return str;
}

std::string getAddVariadicStr() {
  std::string str = "x";
  repeat(functionsNum - 1, [&str] {
    str += ",x";
  });
  return "add(" + str + ")";
}

std::string getSinExprStr() {
  std::string str = "x";
  repeat(functionsNum, [&str] {
    str = "sin(" + str + ")";
  });
  return str;
}

}

static void BM_ParseAddExpression(benchmark::State &state) {
  const std::string str = getAddExprStr();

  for (auto _ : state) {
    benchmark::DoNotOptimize(Expression(str));
  }
}

static void BM_ParseSimplifyAddExpression(benchmark::State &state) {
  const std::string str = getAddExprStr();

  for (auto _ : state) {
    benchmark::DoNotOptimize(Expression(str).toMinimalObject());
  }
}

static void BM_ParseAddVariadicExpression(benchmark::State &state) {
  const std::string str = getAddVariadicStr();

  for (auto _ : state) {
    benchmark::DoNotOptimize(Expression(str));
  }
}

static void BM_ParseSimplifyAddVariadicExpression(benchmark::State &state) {
  const std::string str = getAddVariadicStr();

  for (auto _ : state) {
    benchmark::DoNotOptimize(Expression(str).toMinimalObject());
  }
}

static void BM_ParseSinExpression(benchmark::State &state) {
  const std::string str = getSinExprStr();

  for (auto _ : state) {
    benchmark::DoNotOptimize(Expression(str));
  }
}

static void BM_ParseSimplifySinExpression(benchmark::State &state) {
  const std::string str = getSinExprStr();

  for (auto _ : state) {
    benchmark::DoNotOptimize(Expression(str).toMinimalObject());
  }
}

BENCHMARK(BM_ParseAddExpression)->Unit(benchmark::TimeUnit::kMillisecond);
BENCHMARK(BM_ParseSimplifyAddExpression)->Unit(benchmark::TimeUnit::kMillisecond);
BENCHMARK(BM_ParseAddVariadicExpression)->Unit(benchmark::TimeUnit::kMillisecond);
BENCHMARK(BM_ParseSimplifyAddVariadicExpression)->Unit(benchmark::TimeUnit::kMillisecond);
BENCHMARK(BM_ParseSinExpression)->Unit(benchmark::TimeUnit::kMillisecond);
BENCHMARK(BM_ParseSimplifySinExpression)->Unit(benchmark::TimeUnit::kMillisecond);

BENCHMARK_MAIN();
