#include <benchmark/benchmark.h>

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionFunctions.hpp"

using namespace fintamath;

constexpr size_t strSize = 10'000;

static void BM_SimplifyAddExpression(benchmark::State &state) {
  std::string str = "x";
  while (str.size() < strSize) {
    str += "+x";
  }

  for (auto _ : state) {
    state.PauseTiming();
    Expression expr(str);
    state.ResumeTiming();

    benchmark::DoNotOptimize(simplify(expr).toString());
  }
}

static void BM_SimplifySinExpression(benchmark::State &state) {
  std::string str = "x";
  while (str.size() < strSize) {
    str = "sin(" + str + ")";
  }

  for (auto _ : state) {
    state.PauseTiming();
    Expression expr(str);
    state.ResumeTiming();

    benchmark::DoNotOptimize(simplify(expr).toString());
  }
}

BENCHMARK(BM_SimplifyAddExpression)->Iterations(10)->Unit(benchmark::TimeUnit::kMillisecond);
BENCHMARK(BM_SimplifySinExpression)->Iterations(10)->Unit(benchmark::TimeUnit::kMillisecond);

BENCHMARK_MAIN();
