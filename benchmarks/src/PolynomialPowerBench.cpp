#include <benchmark/benchmark.h>

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionFunctions.hpp"

using namespace fintamath;

// TODO!!! uncomment

static void BM_PolynomialPower(benchmark::State &state) {
  // const Expression expr("x+y+z");
  // const Integer power = 100;

  // for (auto _ : state) {
  //   const Expression res = pow(expr, power);
  //   benchmark::DoNotOptimize(res.toMinimalObject()->toString());
  // }
}

BENCHMARK(BM_PolynomialPower)->Unit(benchmark::TimeUnit::kMillisecond);

BENCHMARK_MAIN();
