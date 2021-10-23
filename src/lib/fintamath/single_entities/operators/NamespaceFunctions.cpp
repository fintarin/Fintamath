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

static size_t getNewPrecision(size_t precision);
static Rational getPrecisionFrac(size_t precision);
static void round(Rational &a, size_t precision);

static Integer abs(const Integer &a);
static Rational lnReduce(const Rational &a, Integer &multiplier, size_t precision);
static Integer naturalPow(const Integer &inA, const Integer &inN);
static Rational naturalPow(const Rational &inA, const Integer &inN);
static Rational trigonometryReduce(const Rational &a, size_t pMultiplier, size_t precision);
static Integer factorialTree(const Integer &left, const Integer &right);

Rational functions::abs(const Rational &a) {
  if (a < 0) {
    return Rational(a * -1);
  }
  return a;
}

// Вычисление квадратного корня, используется функция для длинного числа
Rational functions::sqrt(const Rational &a, size_t precision) {
  if (a < 0) {
    throw domain_error("sqrt out of range");
  }
  if (a == 0) {
    return Rational(0);
  }

  string shift(precision, '0');
  string shiftPow2(precision * 2, '0');
  shift.insert(shift.begin(), '1');
  shiftPow2.insert(shiftPow2.begin(), '1');

  Rational res(sqrt((a * Integer(shiftPow2)).getInteger()), Integer(shift));

  round(res, precision);
  return res;
}

// Логарифм по произвольному основанию. Используется формула: log(a, b) = ln(b) / ln(a).
Rational functions::log(const Rational &a, const Rational &b, size_t precision) {
  try {
    return ln(b, precision) / ln(a, precision);
  } catch (const domain_error &) {
    throw domain_error("log out of range");
  }
}

// Вычисление натурального ln(a), используется ряд Тейлора: ln(a) = sum_{k=0}^{inf} (2/(2k+1)) * ((a-1)/(a+1))^(2k+1)
Rational functions::ln(const Rational &inA, size_t precision) {
  if (inA <= 0) {
    throw domain_error("ln out of range");
  }

  Integer multiplier;
  Rational a = lnReduce(inA, multiplier, precision);
  a = (a - 1) / (a + 1);
  round(a, getNewPrecision(precision));

  Integer k = 1;
  Rational a_i;
  Rational res = a;
  Rational aPow2kPlus1 = a;
  Rational aPow2 = a * a;
  Rational precisionFrac = getPrecisionFrac(getNewPrecision(precision));

  do {
    aPow2kPlus1 *= aPow2;
    a_i = aPow2kPlus1;
    round(a_i, getNewPrecision(precision));
    a_i /= (2 * k + 1);
    res += a_i;
    ++k;
  } while (abs(a_i) > precisionFrac);

  res *= 2 * multiplier;

  round(res, precision);
  return res;
}

// log2(a)
Rational functions::lb(const Rational &a, size_t precision) {
  const int64_t logBase = 2;
  try {
    return log(logBase, a, precision);
  } catch (const domain_error &) {
    throw domain_error("lb out of range");
  }
}

// log10(a)
Rational functions::lg(const Rational &a, size_t precision) {
  const int64_t logBase = 10;
  try {
    return log(logBase, a, precision);
  } catch (const domain_error &) {
    throw domain_error("lg out of range");
  }
}

/*
  Возведение действительного a в действительную степень n. n можно представить в виде
  n_int + n_float, где |n_float| <= 1, тогда a^n = a^n_int * a^n_float. Для вычисления a^n_float, используется ряд
  Тейлора: a^n = 1 + sum_{k=1}^{inf} (n * ln(a))^k / k! при |n| <= 1.
*/
Rational functions::pow(const Rational &inA, const Rational &n, size_t precision) {
  if (inA == 0 && n == 0) {
    throw domain_error("Zero pow zero");
  }
  if (inA < 0 && n.getNumerator() != 0) {
    throw domain_error("pow out of range");
  }
  if (n == 0) {
    return 1;
  }

  Rational a = inA;
  if (n < 0) {
    a = 1 / a;
  }

  Rational aPowInt = naturalPow(a, n.getInteger());
  if (n.getDenominator() == 1) {
    return aPowInt;
  }

  Rational nLna;
  try {
    nLna = Rational(n.getNumerator(), n.getDenominator()) * ln(a, precision);
  } catch (const domain_error &) {
    throw domain_error("pow out of range");
  }

  Integer k = 1;
  Rational a_i = 1;
  Rational aPowFloat = 1;
  Rational precisionFrac = getPrecisionFrac(getNewPrecision(precision));

  do {
    a_i *= nLna;
    round(a_i, getNewPrecision(precision));
    a_i /= k;
    aPowFloat += a_i;
    ++k;
  } while (abs(a_i) > precisionFrac);

  Rational res = aPowFloat * aPowInt;

  round(res, precision);
  return res;
}

Rational functions::exp(const Rational &inFrac, size_t precision) {
  Rational e = getE(precision);
  return pow(e, inFrac, precision);
}

/*
  Вычисление sin(a), используется ряд Тейлора: sin(a) = sum_{k=0}^{k=1} (-1)^k * x^(2k+1) / (2k+1)! Для большего
  сокращения a используются формулы приведения.
*/
Rational functions::sin(const Rational &inA, size_t precision) {
  Rational pi = functions::getPi(precision);
  Rational piMult2 = pi * 2;
  Rational piDiv2 = pi / 2;

  Rational a = inA;
  bool minus = false;

  if (a < 0) {
    minus = true;
    a *= -1;
  }
  if (a >= piMult2) {
    a = trigonometryReduce(a, 2, precision);
  }
  if (a >= pi) {
    minus = !minus;
    a -= pi;
  }
  if (a >= piDiv2) {
    a = cos(a - piDiv2, precision);
    if (minus) {
      a *= -1;
    }
    return a;
  }
  round(a, getNewPrecision(precision));

  Integer k = 2;
  Rational a_i = a;
  Rational res = a;
  Rational aPow2 = a * a;
  Rational precisionFrac = getPrecisionFrac(getNewPrecision(precision));

  do {
    a_i *= -1 * aPow2;
    round(a_i, getNewPrecision(precision));
    a_i /= (k * (k + 1));
    res += a_i;
    k += 2;
  } while (abs(a_i) > precisionFrac);

  if (minus) {
    res *= -1;
  }

  round(res, precision);
  return res;
}

/*
  Вычисление cos(a), используется ряд Тейлора: sin(a) = sum_{k=0}^{k=1} (-1)^k * x^(2k) / (2k)! Для большего сокращения
  a используются формулы приведения.
*/
Rational functions::cos(const Rational &inA, size_t precision) {
  if (inA == 0) {
    return 1;
  }

  Rational pi = functions::getPi(precision);
  Rational piMult2 = pi * 2;
  Rational piDiv2 = pi / 2;

  Rational a = inA;
  bool minus = false;

  if (a < 0) {
    a *= -1;
  }
  if (a > piMult2) {
    a = trigonometryReduce(a, 2, precision);
  }
  if (a >= pi) {
    minus = !minus;
    a = (a - pi) * -1;
  }
  if (a >= piDiv2) {
    return sin(a - piDiv2, precision) * -1;
  }
  round(a, getNewPrecision(precision));

  Integer k = 2;
  Rational a_i = 1;
  Rational res = 1;
  Rational aPow2 = a * a;
  round(aPow2, getNewPrecision(precision));
  Rational precisionFrac = getPrecisionFrac(getNewPrecision(precision));

  do {
    a_i *= -1 * aPow2;
    round(a_i, getNewPrecision(precision));
    a_i /= (k * (k - 1));
    res += a_i;
    k += 2;
  } while (abs(a_i) > precisionFrac);

  if (minus) {
    res *= -1;
  }

  round(res, precision);
  return res;
}

// Вычисление tan(a) = sin(a) / cos(a). Для большего сокращения a используются формулы приведения.
Rational functions::tan(const Rational &inA, size_t precision) {
  Rational pi = functions::getPi(precision);
  Rational piDiv2 = pi / 2;

  Rational a = inA;
  bool minus = false;

  if (a < 0) {
    minus = true;
    a *= -1;
  }
  if (a >= pi) {
    a = trigonometryReduce(a, 2, precision);
  }
  if (a >= piDiv2) {
    a = cot(a - piDiv2, precision) * (-1);
    if (minus) {
      a *= -1;
    }
    return a;
  }
  round(a, getNewPrecision(precision));

  Rational cosFrac = cos(a, precision);
  if (Rational(cosFrac).round(getNewPrecision(precision)) == 0) {
    throw domain_error("tan out of range");
  }

  Rational res = sqrt(1 - cosFrac * cosFrac, precision) / cosFrac;
  if (minus) {
    res *= -1;
  }

  round(res, precision);
  return res;
}

// Вычисление cot(a) = cos(a) / sin(a). Для большего сокращения a используются формулы приведения.
Rational functions::cot(const Rational &inA, size_t precision) {
  Rational pi = functions::getPi(precision);
  Rational piDiv2 = pi / 2;

  Rational a = inA;
  bool minus = false;

  if (a < 0) {
    minus = true;
    a *= -1;
  }
  if (a >= pi) {
    a = trigonometryReduce(a, 2, precision);
  }
  if (a >= piDiv2) {
    a = tan(a - piDiv2, precision) * (-1);
    if (minus) {
      a *= -1;
    }
    return a;
  }
  round(a, getNewPrecision(precision));

  Rational sinFrac = sin(a, precision);
  if (Rational(sinFrac).round(getNewPrecision(precision)) == 0) {
    throw domain_error("cot out of range");
  }

  Rational res = sqrt(1 - sinFrac * sinFrac, precision) / sinFrac;
  if (minus) {
    res *= -1;
  }

  round(res, precision);
  return res;
}

// Вычисление asin(x) = pi/2 - acos(x)
Rational functions::asin(const Rational &a, size_t precision) {
  if (abs(a) > 1) {
    throw domain_error("asin out of range");
  }

  Rational res = (functions::getPi(precision) / 2 - functions::acos(a, precision));
  round(res, precision);
  return res;
}

/*
  Вычисление acos(a).

  При |a| <= 1/5 используется ряд Тейлора (при данных значениях он быстро сходится):
  acos(a) = pi/2 - sum_{k=0}^{inf}((2k)! * a^(2k+1) / (4^k * (k!)^2 * (2k+1)).

  При других значениях используется формула: acos(a) = 2atan(sqrt((1-x)/(1+x))).
*/
Rational functions::acos(const Rational &inA, size_t precision) {
  if (abs(inA) > 1) {
    throw domain_error("acos out of range");
  }
  if (inA == 1) {
    return Rational(0);
  }
  if (inA == -1) {
    return functions::getPi(precision);
  }

  Rational a = inA;
  round(a, getNewPrecision(precision));
  bool minus = false;
  if (a < 0) {
    minus = true;
    a *= -1;
  }

  Rational pi = functions::getPi(precision);

  const Rational maxNumberToReduce(1, 5);

  if (a <= maxNumberToReduce) {
    Integer k = 1;
    Rational a_i;
    Rational f_a = a;
    Rational res = a;
    Rational aPow2 = a * a;
    Rational precisionFrac = getPrecisionFrac(getNewPrecision(precision));

    do {
      f_a *= ((2 * k - 1)) * aPow2;
      round(f_a, getNewPrecision(precision));
      f_a /= (2 * k);
      round(f_a, getNewPrecision(precision));
      a_i = f_a / (2 * k + 1);
      res += a_i;
      ++k;
    } while (abs(a_i) > precisionFrac);

    res = pi / 2 - res;
    if (minus) {
      res = pi - res;
    }

    round(res, getNewPrecision(precision));
    return res;
  }

  Rational res = 2 * atan(sqrt((1 - a) / (1 + a), precision), precision);
  if (minus) {
    res = pi - res;
  }

  round(res, precision);
  return res;
}

/*
  Вычисление atan(a).

  При |a| <= 1/5 используется ряд Тейлора (при данных значениях он быстро сходится): acos(a) = sum_{k=1}^{inf}
  ((-1)^(k-1) * a^(2k-1)) / ((2k-1)).

  При других значениях используется формула: acos(a) = acos(1 / sqrt(1 + x^2)).
*/
Rational functions::atan(const Rational &inA, size_t precision) {
  if (inA == 0) {
    return Rational(0);
  }

  Rational a = inA;
  round(a, getNewPrecision(precision));
  bool minus = false;
  if (a < 0) {
    minus = true;
    a *= -1;
  }

  const Rational maxNumberToReduce(1, 5);

  if (a <= maxNumberToReduce) {
    Integer k = 2;
    Rational a_i;
    Rational f_a = a;
    Rational res = a;
    Rational aPow2 = a * a;
    Rational precisionFrac = getPrecisionFrac(getNewPrecision(precision));

    do {
      f_a *= -1 * aPow2;
      round(f_a, getNewPrecision(precision));
      a_i = f_a / (2 * k - 1);
      round(a_i, getNewPrecision(precision));
      res += a_i;
      k += 1;
    } while (abs(a_i) > precisionFrac);

    if (minus) {
      res *= -1;
    }

    round(res, precision);
    return res;
  }

  Rational res = acos(1 / sqrt(1 + a * a, precision), precision);
  if (minus) {
    res *= -1;
  }

  round(res, precision);
  return res;
}

// Вычисление acot(x) = pi/2 - atan(x)
Rational functions::acot(const Rational &a, size_t precision) {
  Rational res = (getPi(precision) / 2 - functions::atan(a, precision));
  round(res, precision);
  return res;
}

// Обертка над вычислением факториала через дерево
Rational functions::factorial(const Rational &a) {
  if (a < 0 || a.getNumerator() != 0) {
    throw domain_error("factorial out of range");
  }
  if (a < 2) {
    return 1;
  }
  return factorialTree(2, a.getInteger());
}

// Вычисление двойного факториала (наивный алгоритм)
Rational functions::doubleFactorial(const Rational &a) {
  if (a < 0 || a.getNumerator() != 0) {
    throw domain_error("factorial out of range");
  }
  Integer res = 1;
  for (Integer i = a.getInteger(); i > 0; i -= 2) {
    res *= i;
  }
  return res;
}

// Вычисление значения e через ряд Тейлора: e = sum_{k=0}^{inf} 1/n!
Rational functions::getE(size_t precision) {
  if (precision <= E_INITIAL_PRECISION) {
    return E_CONST;
  }

  Integer k = 1;
  Rational a_i = 1;
  Rational res = 1;
  Rational precisionFrac = getPrecisionFrac(precision);

  do {
    a_i /= k;
    round(a_i, precision);
    res += a_i;
    ++k;
  } while (abs(a_i) > precisionFrac);

  round(res, precision);
  return res;
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
Rational functions::getPi(size_t precision) {
  if (precision <= PI_INITIAL_PRECISION) {
    return PI_CONST;
  }

  Integer numOfIterations = functions::lb((int64_t)precision, precision).getInteger() + 1;
  Integer p = 1;
  Rational a = 1;
  Rational b = 1 / functions::sqrt(2, precision);
  Rational t = Rational(1, 4);

  for (Integer i = 0; i < numOfIterations; ++i) {
    Rational prevA = a;
    Rational prevB = b;
    Rational prevT = t;
    a = (prevA + prevB) / 2;
    b = functions::sqrt(prevA * prevB, precision);
    Rational diff = (prevA - a);
    t = prevT - p * diff * diff;
    round(t, precision);
    p *= 2;
  }

  Rational res = (a + b) * (a + b) / (4 * t);
  round(res, precision);
  return res;
}

static size_t getNewPrecision(size_t precision) {
  return precision + (int64_t)std::sqrt(precision);
}

// Получение значения погрешности
static Rational getPrecisionFrac(size_t precision) {
  string precStr(precision + 1, '0');
  precStr.front() = '1';
  return (Rational(1, Integer(precStr)));
}

// Округление
static void round(Rational &a, size_t precision) {
  a = a.round(precision);
}

static Integer abs(const Integer &a) {
  if (a < 0) {
    return Integer(a * -1);
  }
  return a;
}

/*
  Уменьшение значение a под логарифмом так, чтобы a -> 1, поскольку в окрестности данной точке ряд Тейлора быстро
  сходится. Используя формулу log(a^n) = n*log, путем множественного взятия квадратного корня, число приводится к
  требуемуму виду. После расчета логарифма получившегося числа, результат домножается на 2^n, где n — количество
  опреаций взятия корня.
*/
static Rational lnReduce(const Rational &a, Integer &multiplier, size_t precision) {
  Rational res = a;
  round(res, getNewPrecision(precision));
  Rational prec("0.01");
  multiplier = 1;

  while (functions::abs(res - 1) > prec) {
    multiplier *= 2;
    round(res, getNewPrecision(precision));
    res = functions::sqrt(res, getNewPrecision(precision));
  }

  round(res, precision);
  return res;
}

/*
  Бинарное возведение длинного числа a в натуральную степень n:
  (n mod 2 = 0) -> a^n = a^(n/2) * a^(n/2),
  (n mod 2 = 1) -> a^n = a^(n-1) * a.
  Применяется, пока n != 0
*/
static Integer naturalPow(const Integer &inA, const Integer &inN) {
  Integer res = 1;
  Integer a = inA;
  Integer n = abs(inN);

  while (n != 0) {
    if ((*(n.toString().end() - 1) - '0') % 2 == 0) {
      n /= 2;
      a *= a;
    } else {
      --n;
      res *= a;
    }
  }

  return res;
}

/*
  Бинарное возведение действительного a в натуральную степень n.
  Алгоритм аналогичен возведению длинного числа в натуральную степень.
*/
static Rational naturalPow(const Rational &inA, const Integer &inN) {
  Rational res = 1;
  Rational a = inA;
  Integer n = abs(inN);

  while (n != 0) {
    if ((*(n.toString().end() - 1) - '0') % 2 == 0) {
      n /= 2;
      a *= a;
    } else {
      --n;
      res *= a;
    }
  }

  return res;
}

/*
  Уменьшение значения a под тригонометрической функцией. Т.к. тригонометрические функции являются периодическими, для
  них верно следующее: f(a) = f(b + k*p) = f(b), где k — натуральное число, p - период функции. Тогда b = a - k*period,
  k = a div p.
*/
static Rational trigonometryReduce(const Rational &a, size_t pMultiplier, size_t precision) {
  Rational p = (int64_t)pMultiplier * functions::getPi(getNewPrecision(precision) + a.getInteger().size());
  Integer k = (a / p).getInteger();
  Rational res = a - k * p;
  if (res >= p) {
    k = (res / p).getInteger();
    res -= k * p;
  }
  return res;
}

/*
  Вычисление факториала через разложение множителей в дерево. Такое вычисление факториала быстрее, чем наивный алгоритм,
  т.к. умножать большие числа примерно равной длины гораздо быстрее, чем большие числа на маленькие. Это обусловлено
  использованием алгоритма Карацубы.
*/
static Integer factorialTree(const Integer &left, const Integer &right) {
  if (left == right) {
    return left;
  }
  if (right - left == 1) {
    return left * right;
  }
  Integer mid = (left + right) / 2;
  return factorialTree(left, mid) * factorialTree(mid + 1, right);
}
