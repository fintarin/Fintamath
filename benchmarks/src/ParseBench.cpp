#include <benchmark/benchmark.h>

#include "fintamath/expressions/Expression.hpp"

using namespace fintamath;

constexpr size_t strSize = 10'000;

static void BM_ParseAddExpression(benchmark::State &state) {
  std::string str = "x";
  while (str.size() < strSize) {
    str += "+x";
  }

  for (auto _ : state) {
    benchmark::DoNotOptimize(Expression(str).toString());
  }
}

static void BM_ParseSinExpression(benchmark::State &state) {
  std::string str = "x";
  while (str.size() < strSize) {
    str = "sin(" + str + ")";
  }

  for (auto _ : state) {
    benchmark::DoNotOptimize(Expression(str).toString());
  }
}

BENCHMARK(BM_ParseAddExpression)->Unit(benchmark::TimeUnit::kMillisecond);
BENCHMARK(BM_ParseSinExpression)->Unit(benchmark::TimeUnit::kMillisecond);

BENCHMARK_MAIN();
