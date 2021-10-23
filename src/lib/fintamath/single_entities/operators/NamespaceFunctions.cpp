#include "single_entities/operators/NamespaceFunctions.hpp"

#include <cmath>
#include <stdexcept>
#include <string>

using namespace std;

// NOLINTNEXTLINE
const Rational E_CONST("2.71828182845904523536028747135266249775724709369995957496696762772407663035354759");
const int64_t E_INITIAL_PRECISION = 72;

// NOLINTNEXTLINE
const Rational PI_CONST("3.14159265358979323846264338327950288419716939937510582097494459230781640628620899");
const int64_t PI_INITIAL_PRECISION = 72;

static int64_t getNewPrecision(size_t precision);
static Rational getInversedPrecisionVal(size_t precision);

static Rational lnReduce(const Rational &rhs, Integer &multiplier, size_t precision);
static Rational naturalPow(const Rational &lhs, const Integer &rhs);
static Rational trigonometryReduce(const Rational &rhs, size_t multiplier, size_t precision);
static Integer factorialRec(const Integer &left, const Integer &right);

namespace functions {
Rational abs(const Rational &rhs) {
  if (rhs < 0) {
    return -rhs;
  }
  return rhs;
}

// Вычисление квадратного корня, используется функция для длинного числа
Rational sqrt(const Rational &rhs, size_t precision) {
  if (rhs < 0) {
    throw domain_error("sqrt out of range");
  }
  if (rhs == 0) {
    return 0;
  }

  string shift(precision, '0');
  string shiftMult2(precision * 2, '0');
  shift.insert(shift.begin(), '1');
  shiftMult2.insert(shiftMult2.begin(), '1');

  Rational val(sqrt((rhs * Integer(shiftMult2)).getInteger()), Integer(shift));
  return val.round(precision);
}

// Логарифм по произвольному основанию. Используется формула: log(a, b) = ln(b) / ln(a).
Rational log(const Rational &lhs, const Rational &rhs, size_t precision) {
  try {
    return (ln(rhs, precision) / ln(lhs, precision)).round(precision);
  } catch (const domain_error &) {
    throw domain_error("log out of range");
  }
}

// Вычисление натурального ln(a), используется ряд Тейлора: ln(a) = sum_{k=0}^{inf} (2/(2k+1)) * ((a-1)/(a+1))^(2k+1)
Rational ln(const Rational &rhs, size_t precision) {
  if (rhs <= 0) {
    throw domain_error("ln out of range");
  }

  Integer multiplier;
  Rational rhsStep = lnReduce(rhs, multiplier, precision);
  rhsStep = ((rhsStep - 1) / (rhsStep + 1)).round(getNewPrecision(precision));

  Integer step = 1;
  Rational precisionVal = getInversedPrecisionVal(getNewPrecision(precision));
  Rational powRhs = rhsStep;
  Rational rhsSqr = (rhsStep * rhsStep).round(getNewPrecision(precision));
  Rational res = rhsStep;

  do {
    powRhs *= rhsSqr;
    rhsStep = powRhs / (step * 2 + 1);
    rhsStep = rhsStep.round(getNewPrecision(precision));
    res += rhsStep;
    step++;
  } while (abs(rhsStep) > precisionVal);

  return (res * multiplier * 2).round(precision);
}

// log2(a)
Rational lb(const Rational &rhs, size_t precision) {
  const int64_t logBase = 2;
  try {
    return log(logBase, rhs, precision);
  } catch (const domain_error &) {
    throw domain_error("lb out of range");
  }
}

// log10(a)
Rational lg(const Rational &rhs, size_t precision) {
  const int64_t logBase = 10;
  try {
    return log(logBase, rhs, precision);
  } catch (const domain_error &) {
    throw domain_error("lg out of range");
  }
}

/*
  Возведение действительного a в действительную степень n. n можно представить в виде
  n_int + n_float, где |n_float| <= 1, тогда a^n = a^n_int * a^n_float. Для вычисления a^n_float, используется ряд
  Тейлора: a^n = 1 + sum_{k=1}^{inf} (n * ln(a))^k / k! при |n| <= 1.
*/
Rational pow(const Rational &lhs, const Rational &rhs, size_t precision) {
  if (lhs == 0 && rhs == 0) {
    throw domain_error("Zero pow zero");
  }
  if (lhs < 0 && rhs.getNumerator() != 0) {
    throw domain_error("pow out of range");
  }
  if (rhs == 0) {
    return 1;
  }

  Rational rhsStep = lhs;
  if (rhs < 0) {
    rhsStep = 1 / rhsStep;
  }

  Rational lhsPowIntRhs = naturalPow(rhsStep, rhs.getInteger());
  if (rhs.getDenominator() == 1) {
    return lhsPowIntRhs;
  }

  auto rhsMultLnRhs = Rational(rhs.getNumerator(), rhs.getDenominator()) * ln(rhsStep, precision);

  Integer step = 1;
  Rational precisionVal = getInversedPrecisionVal(getNewPrecision(precision));
  Rational lhsPowFloatRhs = 1;

  do {
    rhsStep *= rhsMultLnRhs;
    rhsStep /= step;
    rhsStep = rhsStep.round(getNewPrecision(precision));
    lhsPowFloatRhs += rhsStep;
    step++;
  } while (abs(rhsStep) > precisionVal);

  return (lhsPowFloatRhs * lhsPowIntRhs).round(precision);
}

Rational exp(const Rational &rhs, size_t precision) {
  return pow(getE(precision), rhs, precision);
}

/*
  Вычисление sin(a), используется ряд Тейлора: sin(a) = sum_{k=0}^{k=1} (-1)^k * x^(2k+1) / (2k+1)! Для большего
  сокращения a используются формулы приведения.
*/
Rational sin(const Rational &rhs, size_t precision) {
  Rational pi = getPi(precision);
  Rational piMult2 = pi * 2;
  Rational piDiv2 = pi / 2;

  Rational rhsStep = rhs;
  bool isNegative = false;

  if (rhsStep < 0) {
    isNegative = true;
    rhsStep = -rhsStep;
  }
  if (rhsStep >= piMult2) {
    rhsStep = trigonometryReduce(rhsStep, 2, precision);
  }
  if (rhsStep >= pi) {
    isNegative = !isNegative;
    rhsStep -= pi;
  }
  if (rhsStep >= piDiv2) {
    rhsStep = cos(rhsStep - piDiv2, precision);
    if (isNegative) {
      rhsStep = -rhsStep;
    }
    return rhsStep.round(precision);
  }
  rhsStep = rhsStep.round(getNewPrecision(precision));

  Integer step = 2;
  Rational precisionVal = getInversedPrecisionVal(getNewPrecision(precision));
  Rational rhsSqr = (rhsStep * rhsStep).round(getNewPrecision(precision));
  Rational res = rhsStep;

  do {
    rhsStep *= -rhsSqr;
    rhsStep /= (step * (step + 1));
    rhsStep = rhsStep.round(getNewPrecision(precision));
    res += rhsStep;
    step += 2;
  } while (abs(rhsStep) > precisionVal);

  if (isNegative) {
    res = -res;
  }
  return res.round(precision);
}

/*
  Вычисление cos(a), используется ряд Тейлора: sin(a) = sum_{k=0}^{k=1} (-1)^k * x^(2k) / (2k)! Для большего сокращения
  a используются формулы приведения.
*/
Rational cos(const Rational &rhs, size_t precision) {
  Rational pi = getPi(precision);
  Rational piMult2 = pi * 2;
  Rational piDiv2 = pi / 2;

  Rational rhsStep = rhs;
  bool isNegative = false;

  if (rhsStep < 0) {
    rhsStep = -rhsStep;
  }
  if (rhsStep > piMult2) {
    rhsStep = trigonometryReduce(rhsStep, 2, precision);
  }
  if (rhsStep >= pi) {
    isNegative = !isNegative;
    rhsStep = -(rhsStep - pi);
  }
  if (rhsStep >= piDiv2) {
    return -sin(rhsStep - piDiv2, precision);
  }
  rhsStep = rhsStep.round(getNewPrecision(precision));

  Integer step = 2;
  Rational precisionVal = getInversedPrecisionVal(getNewPrecision(precision));
  Rational rhsSqr = (rhsStep * rhsStep).round(getNewPrecision(precision));
  Rational res = 1;
  rhsStep = 1;

  do {
    rhsStep *= -rhsSqr;
    rhsStep /= step * (step - 1);
    rhsStep = rhsStep.round(getNewPrecision(precision));
    res += rhsStep;
    step += 2;
  } while (abs(rhsStep) > precisionVal);

  if (isNegative) {
    res = -res;
  }

  return res.round(precision);
}

// Вычисление tan(a) = sin(a) / cos(a). Для большего сокращения a используются формулы приведения.
Rational tan(const Rational &rhs, size_t precision) {
  Rational pi = getPi(precision);
  Rational piDiv2 = pi / 2;

  Rational val = rhs;
  bool isNegative = false;

  if (val < 0) {
    isNegative = true;
    val = -val;
  }
  if (val >= pi) {
    val = trigonometryReduce(val, 2, precision);
  }
  if (val >= piDiv2) {
    try {
      val = -cot(val - piDiv2, precision);
    } catch (const domain_error &) {
      throw domain_error("tan out of range");
    }

    if (isNegative) {
      val = -val;
    }
    return val;
  }

  val = cos(val, precision);

  Rational res = sqrt(1 - val * val, precision) / val;
  if (isNegative) {
    res = -res;
  }
  return res.round(precision);
}

// Вычисление cot(a) = cos(a) / sin(a). Для большего сокращения a используются формулы приведения.
Rational cot(const Rational &rhs, size_t precision) {
  Rational pi = getPi(precision);
  Rational piDiv2 = pi / 2;

  Rational val = rhs;
  bool isNegative = false;

  if (val < 0) {
    isNegative = true;
    val = -val;
  }
  if (val >= pi) {
    val = trigonometryReduce(val, 2, precision);
  }
  if (val >= piDiv2) {
    try {
      val = -tan(val - piDiv2, precision);
    } catch (const domain_error &) {
      throw domain_error("cot out of range");
    }

    if (isNegative) {
      val = -val;
    }
    return val;
  }

  Rational sinVal = sin(val, precision);
  if (sinVal.round(precision - 1) == 0) {
    throw domain_error("cot out of range");
  }

  Rational res = sqrt(1 - sinVal * sinVal, precision) / sinVal;
  if (isNegative) {
    res = -res;
  }
  return res.round(precision);
}

// Вычисление asin(x) = pi/2 - acos(x)
Rational asin(const Rational &rhs, size_t precision) {
  if (abs(rhs) > 1) {
    throw domain_error("asin out of range");
  }
  Rational res = (getPi(precision) / 2 - acos(rhs, precision));
  return res.round(precision);
}

/*
  Вычисление acos(a).

  При |a| <= 1/5 используется ряд Тейлора (при данных значениях он быстро сходится):
  acos(a) = pi/2 - sum_{k=0}^{inf}((2k)! * a^(2k+1) / (4^k * (k!)^2 * (2k+1)).

  При других значениях используется формула: acos(a) = 2atan(sqrt((1-x)/(1+x))).
*/
Rational acos(const Rational &rhs, size_t precision) {
  if (abs(rhs) > 1) {
    throw domain_error("acos out of range");
  }

  Rational rhsStep = rhs.round(getNewPrecision(precision));
  bool isNegative = false;
  if (rhsStep < 0) {
    isNegative = true;
    rhsStep = -rhsStep;
  }

  Rational pi = getPi(precision);
  const Rational maxRedusedVal(1, 5);

  if (rhsStep <= maxRedusedVal) {
    Integer step = 1;
    Rational precisionVal = getInversedPrecisionVal(getNewPrecision(precision));
    Rational val = rhsStep;
    Rational rhsSqr = (rhsStep * rhsStep).round(getNewPrecision(precision));
    Rational res = rhsStep;

    do {
      val *= (step * 2 - 1) * rhsSqr;
      val /= step * 2;
      val = val.round(getNewPrecision(precision));
      rhsStep = val / (step * 2 + 1);
      rhsStep = rhsStep.round(getNewPrecision(precision));
      res += rhsStep;
      step++;
    } while (abs(rhsStep) > precisionVal);

    res = pi / 2 - res;
    if (isNegative) {
      res = pi - res;
    }
    return res.round(precision);
  }

  Rational res = atan(sqrt((1 - rhsStep) / (1 + rhsStep), precision), precision) * 2;
  if (isNegative) {
    res = pi - res;
  }
  return res.round(precision);
}

/*
  Вычисление atan(a).

  При |a| <= 1/5 используется ряд Тейлора (при данных значениях он быстро сходится): acos(a) = sum_{k=1}^{inf}
  ((-1)^(k-1) * a^(2k-1)) / ((2k-1)).

  При других значениях используется формула: acos(a) = acos(1 / sqrt(1 + x^2)).
*/
Rational atan(const Rational &rhs, size_t precision) {
  Rational rhsStep = rhs.round(getNewPrecision(precision));
  bool isNegative = false;
  if (rhsStep < 0) {
    isNegative = true;
    rhsStep = -rhsStep;
  }

  const Rational maxNumberToReduce(1, 5);

  if (rhsStep <= maxNumberToReduce) {
    Integer step = 2;
    Rational precisionVal = getInversedPrecisionVal(getNewPrecision(precision));
    Rational val = rhsStep;
    Rational rhsSqr = (rhsStep * rhsStep).round(getNewPrecision(precision));
    Rational res = rhsStep;

    do {
      val *= -rhsSqr;
      val = val.round(getNewPrecision(precision));
      rhsStep = val / (step * 2 - 1);
      rhsStep = rhsStep.round(getNewPrecision(precision));
      res += rhsStep;
      step++;
    } while (abs(rhsStep) > precisionVal);

    if (isNegative) {
      res = -res;
    }
    return res.round(precision);
  }

  Rational res = acos(1 / sqrt(1 + rhsStep * rhsStep, precision), precision);
  if (isNegative) {
    res = -res;
  }
  return res.round(precision);
}

// Вычисление acot(x) = pi/2 - atan(x)
Rational acot(const Rational &rhs, size_t precision) {
  Rational res = getPi(precision) / 2;
  if (rhs < 0) {
    res = -res;
  }
  return (res - atan(rhs, precision)).round(precision);
}

// Обертка над вычислением факториала через дерево
Rational factorial(const Rational &rhs) {
  if (rhs < 0 || rhs.getNumerator() != 0) {
    throw domain_error("factorial out of range");
  }
  if (rhs < 2) {
    return 1;
  }
  return factorialRec(2, rhs.getInteger());
}

// Вычисление двойного факториала (наивный алгоритм)
Rational doubleFactorial(const Rational &rhs) {
  if (rhs < 0 || rhs.getNumerator() != 0) {
    throw domain_error("factorial out of range");
  }
  Integer res = 1;
  for (Integer i = rhs.getInteger(); i > 0; i -= 2) {
    res *= i;
  }
  return res;
}

// Вычисление значения e через ряд Тейлора: e = sum_{k=0}^{inf} 1/n!
Rational getE(size_t precision) {
  if (precision <= E_INITIAL_PRECISION) {
    return E_CONST;
  }

  Integer step = 1;
  Rational precisionVal = getInversedPrecisionVal(getNewPrecision(precision));
  Rational stepVal = 1;
  Rational res = 1;

  do {
    stepVal /= step;
    res += stepVal;
    step++;
  } while (abs(stepVal) > precisionVal);

  return res.round(precision);
}

/*
  Вычисление значения pi по алгоритму Брента — Саламина:

  a0 = 1,
  b0 = 1/sqrt2,
  t0 = 1/4,
  p = 1.

  a_{n+1} = (a_n + b) / 2,
  b_{n+1} = sqrt(a_n * b_n),
  t_{n+1} = t_n - p_n * (a_n - a_{n+1})^2,
  p_{n+1} = 2*p_n.
*/
Rational getPi(size_t precision) {
  if (precision <= PI_INITIAL_PRECISION) {
    return PI_CONST;
  }

  Integer step = lb((int64_t)precision, precision).getInteger() + 1;
  Integer p = 1;
  Rational a = 1;
  Rational b = 1 / functions::sqrt(2, precision);
  auto t = Rational(1, 4);

  for (Integer i = 0; i < step; ++i) {
    Rational prevA = a;
    Rational prevB = b;
    Rational prevT = t;
    a = (prevA + prevB) / 2;
    b = sqrt(prevA * prevB, precision);
    Rational diff = (prevA - a);
    t = (prevT - p * diff * diff).round(precision);
    p *= 2;
  }

  return ((a + b) * (a + b) / (4 * t)).round(precision);
}
} // namespace functions

static int64_t getNewPrecision(size_t precision) {
  return (int64_t)precision + (int64_t)std::sqrt(precision);
}

// Получение значения погрешности
static Rational getInversedPrecisionVal(size_t precision) {
  string precStr(precision + 1, '0');
  precStr.front() = '1';
  return (Rational(1, Integer(precStr)));
}

/*
  Уменьшение значение a под логарифмом так, чтобы a -> 1, поскольку в окрестности данной точке ряд Тейлора быстро
  сходится. Используя формулу log(a^n) = n*log, путем множественного взятия квадратного корня, число приводится к
  требуемуму виду. После расчета логарифма получившегося числа, результат домножается на 2^n, где n — количество
  опреаций взятия корня.
*/
static Rational lnReduce(const Rational &rhs, Integer &multiplier, size_t precision) {
  const Rational maxRedusedVal("0.01");
  Rational res = rhs.round(getNewPrecision(precision));
  multiplier = 1;

  while (functions::abs(res - 1) > maxRedusedVal) {
    multiplier *= 2;
    res = functions::sqrt(res, precision);
  }

  return res.round(precision);
}

/*
  Бинарное возведение длинного числа a в натуральную степень n:
  (n mod 2 = 0) -> a^n = a^(n/2) * a^(n/2),
  (n mod 2 = 1) -> a^n = a^(n-1) * a.
  Применяется, пока n != 0
*/
static Rational naturalPow(const Rational &lhs, const Integer &rhs) {
  Rational res = 1;
  Rational tmpLhs = lhs;
  Integer tmpRhs = rhs;

  while (tmpRhs != 0) {
    if ((*(tmpRhs.toString().end() - 1) - '0') % 2 == 0) {
      tmpRhs /= 2;
      tmpLhs *= tmpLhs;
    } else {
      --tmpRhs;
      res *= tmpLhs;
    }
  }

  return res;
}

/*
  Уменьшение значения a под тригонометрической функцией. Т.к. тригонометрические функции являются периодическими, для
  них верно следующее: f(a) = f(b + k*p) = f(b), где k — натуральное число, p - период функции. Тогда b = a - k*period,
  k = a div p.
*/
static Rational trigonometryReduce(const Rational &rhs, size_t multiplier, size_t precision) {
  Rational period = (int64_t)multiplier * functions::getPi(getNewPrecision(precision) + rhs.getInteger().size());
  Integer perionMultiplier = (rhs / period).getInteger();
  Rational res = rhs - perionMultiplier * period;
  return res;
}

/*
  Вычисление факториала через разложение множителей в дерево. Такое вычисление факториала быстрее, чем наивный алгоритм,
  т.к. умножать большие числа примерно равной длины гораздо быстрее, чем большие числа на маленькие. Это обусловлено
  использованием алгоритма Карацубы.
*/
static Integer factorialRec(const Integer &left, const Integer &right) {
  if (left == right) {
    return left;
  }
  if (right - left == 1) {
    return left * right;
  }
  Integer mid = (left + right) / 2;
  return factorialRec(left, mid) * factorialRec(mid + 1, right);
}
