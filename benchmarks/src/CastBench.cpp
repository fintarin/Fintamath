#include <benchmark/benchmark.h>

#include "fintamath/constants/IConstant.hpp"
#include "fintamath/core/MathObjectUtils.hpp"
#include "fintamath/numbers/Integer.hpp"

using namespace fintamath;

static void BM_FintamathCast(benchmark::State &state) {
  Integer integ = 1;
  IMathObject *obj = &integ;

  for (auto _ : state) {
    benchmark::DoNotOptimize(cast<Integer>(obj));
    benchmark::DoNotOptimize(cast<INumber>(obj));
    benchmark::DoNotOptimize(cast<IConstant>(obj));
  }
}

static void BM_DynamicCast(benchmark::State &state) {
  Integer integ = 1;
  IMathObject *obj = &integ;

  for (auto _ : state) {
    benchmark::DoNotOptimize(dynamic_cast<Integer *>(obj));
    benchmark::DoNotOptimize(dynamic_cast<INumber *>(obj));
    benchmark::DoNotOptimize(dynamic_cast<IConstant *>(obj));
  }
}

BENCHMARK(BM_FintamathCast)->Unit(benchmark::TimeUnit::kNanosecond);
BENCHMARK(BM_DynamicCast)->Unit(benchmark::TimeUnit::kNanosecond);

BENCHMARK_MAIN();
