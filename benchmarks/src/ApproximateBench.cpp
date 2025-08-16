#include <benchmark/benchmark.h>

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionFunctions.hpp"
#include "fintamath/numbers/Real.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

using namespace fintamath;

const Real start = -5;
const Real end = 5;
const Real step = Rational(1, 100);

constexpr double doubleStart = -5.0;
constexpr double doubleEnd = 5.0;
constexpr double doubleStep = 1.0 / 100.0;

static auto func(const auto &arg) {
  return sin(sin(sin(arg)));
}

static void BM_ApproximateExpression(benchmark::State &state) {
  Real::ScopedSetPrecision(10);

  const Variable var("x");
  const Expression expr = func(var);

  for (auto _ : state) {
    for (Real i = start; i <= end; i += step) {
      if (abs(i) < step) {
        i = 0;
      }

      Expression res = expr;
      res.setVariable(var, i);
      res = approximate(res);
      benchmark::DoNotOptimize(res.toString());
    }
  }
}

static void BM_ApproximateReal(benchmark::State &state) {
  Real::ScopedSetPrecision(10);

  for (auto _ : state) {
    for (Real i = start; i <= end; i += step) {
      if (abs(i) < step) {
        i = 0;
      }

      const Real res = func(i);
      benchmark::DoNotOptimize(res.toString());
    }
  }
}

static void BM_ApproximateRealBackend(benchmark::State &state) {
  Real::ScopedSetPrecision(10);

  for (auto _ : state) {
    for (Real::Backend i = start.getBackend(); i <= end.getBackend(); i += step.getBackend()) {
      if (abs(i) < step.getBackend()) {
        i = 0;
      }

      const Real::Backend res = func(i);
      benchmark::DoNotOptimize(res.str());
    }
  }
}

static void BM_ApproximateDouble(benchmark::State &state) {
  for (auto _ : state) {
    for (double i = doubleStart; i < doubleEnd; i += doubleStep) {
      if (abs(i) < doubleStep) {
        i = 0;
      }

      const double res = func(i);
      benchmark::DoNotOptimize(std::to_string(res));
    }
  }
}

BENCHMARK(BM_ApproximateExpression)->Unit(benchmark::TimeUnit::kMillisecond);
BENCHMARK(BM_ApproximateReal)->Unit(benchmark::TimeUnit::kMillisecond);
BENCHMARK(BM_ApproximateRealBackend)->Unit(benchmark::TimeUnit::kMillisecond);
BENCHMARK(BM_ApproximateDouble)->Unit(benchmark::TimeUnit::kMillisecond);

BENCHMARK_MAIN();
