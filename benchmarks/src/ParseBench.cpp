#include <benchmark/benchmark.h>

#include "fintamath/core/CoreUtils.hpp"
#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionFunctions.hpp"

using namespace fintamath;
using namespace fintamath::detail;

namespace {

constexpr size_t functionsNum = 5'000;

std::string getAddExprStr() {
  std::string str = "x";
  repeat(functionsNum, [&str] {
    str += "+x";
  });
  return str;
}

std::string getMinStr() {
  std::string str = "x";
  repeat(functionsNum - 1, [&str] {
    str += ",x";
  });
  return "min(" + str + ")";
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
    benchmark::DoNotOptimize(simplify(Expression(str)));
  }
}

static void BM_ParseMinExpression(benchmark::State &state) {
  const std::string str = getMinStr();

  for (auto _ : state) {
    benchmark::DoNotOptimize(Expression(str));
  }
}

static void BM_ParseSimplifyMinExpression(benchmark::State &state) {
  const std::string str = getMinStr();

  for (auto _ : state) {
    benchmark::DoNotOptimize(simplify(Expression(str)));
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
    benchmark::DoNotOptimize(simplify(Expression(str)));
  }
}

BENCHMARK(BM_ParseAddExpression)->Unit(benchmark::TimeUnit::kMillisecond);
BENCHMARK(BM_ParseSimplifyAddExpression)->Unit(benchmark::TimeUnit::kMillisecond);
BENCHMARK(BM_ParseMinExpression)->Unit(benchmark::TimeUnit::kMillisecond);
BENCHMARK(BM_ParseSimplifyMinExpression)->Unit(benchmark::TimeUnit::kMillisecond);
BENCHMARK(BM_ParseSinExpression)->Unit(benchmark::TimeUnit::kMillisecond);
BENCHMARK(BM_ParseSimplifySinExpression)->Unit(benchmark::TimeUnit::kMillisecond);

BENCHMARK_MAIN();
