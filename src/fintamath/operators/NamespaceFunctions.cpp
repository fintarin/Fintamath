#include "operators/NamespaceFunctions.hpp"

#include <string>

#include "calculator/Calculator.hpp"
#include "calculator/ExceptionClasses.hpp"

constexpr long long PRECISION_OF_FUNCTIONS = PRECISION + ROUND_CONST;

// Округление
void round(Fraction &a, const size_t precision) {
  a.round(PRECISION_OF_FUNCTIONS);
}

// Получение значения погрешности
Fraction getPrecisionFrac(const size_t precision) {
  std::string precStr(PRECISION_OF_FUNCTIONS + 1, '0');
  precStr.front() = '1';
  return (Fraction(1, BigInteger(precStr)));
}

BigInteger abs(const BigInteger &a) {
  if (a < 0) {
    return BigInteger(a * -1);
  }
  return a;
}

Fraction functions::abs(const Fraction &a) {
  if (a < 0) {
    return Fraction(a * -1);
  }
  return a;
}

/*
  Бинарное возведение длинного числа a в натуральную степень n:
  (n mod 2 = 0) -> a^n = a^(n/2) * a^(n/2),
  (n mod 2 = 1) -> a^n = a^(n-1) * a.
  Применяется, пока n != 0
*/
BigInteger naturalPow(const BigInteger &inA, const BigInteger &inN) {
  BigInteger res = 1;
  BigInteger a = inA;
  BigInteger n = abs(inN);

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
Fraction naturalPow(const Fraction &inA, const BigInteger &inN) {
  Fraction res = 1;
  Fraction a = inA;
  BigInteger n = abs(inN);

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

// Вычисление квадратного корня, используется функция для длинного числа
Fraction functions::sqrt(const Fraction &a, const size_t precision) {
  if (a < 0) {
    throw OutOfRange("square root");
  }
  if (a == 0) {
    return Fraction(0);
  }

  std::string shift((PRECISION_OF_FUNCTIONS), '0');
  std::string shiftPow2(2 * (PRECISION_OF_FUNCTIONS), '0');
  shift.insert(shift.begin(), '1');
  shiftPow2.insert(shiftPow2.begin(), '1');

  Fraction res(sqrt((a * BigInteger(shiftPow2)).getInteger()), BigInteger(shift));

  round(res, precision);
  return res;
}

/*
  Уменьшение значение a под логарифмом так, чтобы a -> 1, поскольку в окрестности данной точке ряд Тейлора быстро
  сходится. Используя формулу log(a^n) = n*log, путем множественного взятия квадратного корня, число приводится к
  требуемуму виду. После расчета логарифма получившегося числа, результат домножается на 2^n, где n — количество
  опреаций взятия корня.
*/
Fraction lnReduce(const Fraction &a, BigInteger &multiplier, const size_t precision) {
  Fraction res = a;
  round(res, precision);
  Fraction prec("0.01");
  multiplier = 1;

  while (functions::abs(res - 1) > prec) {
    multiplier *= 2;
    round(res, precision);
    res = functions::sqrt(res, precision);
  }

  round(res, precision);
  return res;
}

// Логарифм по произвольному основанию. Используется формула: log(a, b) = ln(b) / ln(a).
Fraction functions::log(const Fraction &a, const Fraction &b, const size_t precision) {
  try {
    return ln(b, precision) / ln(a, precision);
  } catch (...) {
    throw OutOfRange("log");
  }
}

// Вычисление натурального ln(a), используется ряд Тейлора: ln(a) = sum_{k=0}^{inf} (2/(2k+1)) * ((a-1)/(a+1))^(2k+1)
Fraction functions::ln(const Fraction &inA, const size_t precision) {
  if (inA <= 0) {
    throw OutOfRange("ln");
  }

  BigInteger multiplier;
  Fraction a = lnReduce(inA, multiplier, precision);
  a = (a - 1) / (a + 1);
  round(a, precision);

  BigInteger k = 1;
  Fraction a_i, res = a;
  Fraction aPow2kPlus1 = a, aPow2 = a * a;
  Fraction precisionFrac = getPrecisionFrac(precision);

  do {
    aPow2kPlus1 *= aPow2;
    a_i = aPow2kPlus1;
    round(a_i, precision);
    a_i /= (2 * k + 1);
    res += a_i;
    ++k;
  } while (abs(a_i) > precisionFrac);

  res *= 2 * multiplier;

  round(res, precision);
  return res;
}

// log2(a)
Fraction functions::lb(const Fraction &a, const size_t precision) {
  try {
    return log(2, a, precision);
  } catch (...) {
    throw OutOfRange("lb");
  }
}

// log10(a)
Fraction functions::lg(const Fraction &a, const size_t precision) {
  try {
    return log(10, a, precision);
  } catch (...) {
    throw OutOfRange("lg");
  }
}

/*
  Возведение действительного a в действительную степень n. n можно представить в виде
  n_int + n_float, где |n_float| <= 1, тогда a^n = a^n_int * a^n_float. Для вычисления a^n_float, используется ряд
  Тейлора: a^n = 1 + sum_{k=1}^{inf} (n * ln(a))^k / k! при |n| <= 1.
*/
Fraction functions::pow(const Fraction &inA, const Fraction &n, const size_t precision) {
  if (inA == 0 && n == 0) {
    throw ZeroPowZero("power");
  }
  if (inA < 0 && n.getNumerator() != 0) {
    throw OutOfRange("power");
  }
  if (n == 0) {
    return 1;
  }

  Fraction a = inA;
  if (n < 0) {
    a = 1 / a;
  }

  Fraction aPowInt = naturalPow(a, n.getInteger());
  if (n.getDenominator() == 1) {
    return aPowInt;
  }

  Fraction nLna;
  try {
    nLna = Fraction(n.getNumerator(), n.getDenominator()) * ln(a, precision);
  } catch (OutOfRange) {
    throw OutOfRange("power");
  }

  BigInteger k = 1;
  Fraction a_i = 1, aPowFloat = 1;
  Fraction precisionFrac = getPrecisionFrac(precision);

  do {
    a_i *= nLna;
    round(a_i, precision);
    a_i /= k;
    aPowFloat += a_i;
    ++k;
  } while (abs(a_i) > precisionFrac);

  Fraction res = aPowFloat * aPowInt;

  round(res, precision);
  return res;
}

Fraction functions::exp(const Fraction &inFrac, const size_t precision) {
  Fraction e = getE(PRECISION_OF_CONSTANTS);
  return pow(e, inFrac, precision);
}

/*
  Уменьшение значения a под тригонометрической функцией. Т.к. тригонометрические функции являются периодическими, для
  них верно следующее: f(a) = f(b + k*p) = f(b), где k — натуральное число, p - период функции. Тогда b = a - k*period,
  k = a div p.
*/
Fraction trigonometryReduce(const Fraction &a, const size_t &pMultiplier, const size_t precision) {
  Fraction p = pMultiplier * functions::getPi(precision + a.getInteger().size());
  BigInteger k = (a / p).getInteger();
  Fraction res = a - k * p;
  if (res >= p) {
    k = (res / p).getInteger();
    res -= k * p;
  }
  return res;
}

/*
  Вычисление sin(a), используется ряд Тейлора: sin(a) = sum_{k=0}^{k=1} (-1)^k * x^(2k+1) / (2k+1)! Для большего
  сокращения a используются формулы приведения.
*/
Fraction functions::sin(const Fraction &inA, const size_t precision) {
  Fraction pi = functions::getPi(PRECISION_OF_FUNCTIONS);
  Fraction piMult2 = pi * 2;
  Fraction piDiv2 = pi / 2;

  Fraction a = inA;
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
  round(a, precision);

  BigInteger k = 2;
  Fraction a_i = a, res = a, aPow2 = a * a;
  Fraction precisionFrac = getPrecisionFrac(precision);

  do {
    a_i *= -1 * aPow2;
    round(a_i, precision);
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
Fraction functions::cos(const Fraction &inA, const size_t precision) {
  if (inA == 0) {
    return 1;
  }

  Fraction pi = functions::getPi(PRECISION_OF_FUNCTIONS);
  Fraction piMult2 = pi * 2;
  Fraction piDiv2 = pi / 2;

  Fraction a = inA;
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
  round(a, precision);

  BigInteger k = 2;
  Fraction a_i = 1, res = 1, aPow2 = a * a;
  round(aPow2, precision);
  Fraction precisionFrac = getPrecisionFrac(precision);

  do {
    a_i *= -1 * aPow2;
    round(a_i, precision);
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
Fraction functions::tan(const Fraction &inA, const size_t precision) {
  Fraction pi = functions::getPi(PRECISION_OF_FUNCTIONS);
  Fraction piDiv2 = pi / 2;

  Fraction a = inA;
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
  round(a, precision);

  Fraction cosFrac = cos(a, precision);
  if (Fraction(cosFrac).round(PRECISION) == 0) {
    throw OutOfRange("tan");
  }

  Fraction res = sqrt(1 - cosFrac * cosFrac, precision) / cosFrac;
  if (minus) {
    res *= -1;
  }

  round(res, precision);
  return res;
}

// Вычисление cot(a) = cos(a) / sin(a). Для большего сокращения a используются формулы приведения.
Fraction functions::cot(const Fraction &inA, const size_t precision) {
  Fraction pi = functions::getPi(PRECISION_OF_FUNCTIONS);
  Fraction piDiv2 = pi / 2;

  Fraction a = inA;
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
  round(a, precision);

  Fraction sinFrac = sin(a, precision);
  if (Fraction(sinFrac).round(PRECISION) == 0) {
    throw OutOfRange("cot");
  }

  Fraction res = sqrt(1 - sinFrac * sinFrac, precision) / sinFrac;
  if (minus) {
    res *= -1;
  }

  round(res, precision);
  return res;
}

// Вычисление asin(x) = pi/2 - acos(x)
Fraction functions::asin(const Fraction &a, const size_t precision) {
  if (abs(a) > 1) {
    throw OutOfRange("asin");
  }

  Fraction res = (functions::getPi(PRECISION_OF_FUNCTIONS) / 2 - functions::acos(a, precision));
  round(res, precision);
  return res;
}

/*
  Вычисление acos(a).

  При |a| <= 1/5 используется ряд Тейлора (при данных значениях он быстро сходится):
  acos(a) = pi/2 - sum_{k=0}^{inf}((2k)! * a^(2k+1) / (4^k * (k!)^2 * (2k+1)).

  При других значениях используется формула: acos(a) = 2atan(sqrt((1-x)/(1+x))).
*/
Fraction functions::acos(const Fraction &inA, const size_t precision) {
  if (abs(inA) > 1) {
    throw OutOfRange("acos");
  }
  if (inA == 1) {
    return Fraction(0);
  }
  if (inA == -1) {
    return functions::getPi(PRECISION_OF_FUNCTIONS);
  }

  Fraction a = inA;
  round(a, precision);
  bool minus = false;
  if (a < 0) {
    minus = true;
    a *= -1;
  }

  Fraction pi = functions::getPi(PRECISION_OF_FUNCTIONS);

  if (a <= Fraction(1, 5)) {
    BigInteger k = 1;
    Fraction a_i, f_a = a, res = a, aPow2 = a * a;
    Fraction precisionFrac = getPrecisionFrac(precision);

    do {
      f_a *= ((2 * k - 1)) * aPow2;
      round(f_a, precision);
      f_a /= (2 * k);
      round(f_a, precision);
      a_i = f_a / (2 * k + 1);
      res += a_i;
      ++k;
    } while (abs(a_i) > precisionFrac);

    res = pi / 2 - res;
    if (minus) {
      res = pi - res;
    }

    round(res, precision);
    return res;
  }

  Fraction res = 2 * atan(sqrt((1 - a) / (1 + a), precision), precision);
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
Fraction functions::atan(const Fraction &inA, const size_t precision) {
  if (inA == 0) {
    return Fraction(0);
  }

  Fraction a = inA;
  round(a, precision);
  bool minus = false;
  if (a < 0) {
    minus = true;
    a *= -1;
  }

  if (a <= Fraction(1, 5)) {
    BigInteger k = 2;
    Fraction a_i, f_a = a, res = a, aPow2 = a * a;
    Fraction precisionFrac = getPrecisionFrac(precision);

    do {
      f_a *= -1 * aPow2;
      round(f_a, precision);
      a_i = f_a / (2 * k - 1);
      round(a_i, precision);
      res += a_i;
      k += 1;
    } while (abs(a_i) > precisionFrac);

    if (minus) {
      res *= -1;
    }

    round(res, precision);
    return res;
  }

  Fraction res = acos(1 / sqrt(1 + a * a, precision), precision);
  if (minus) {
    res *= -1;
  }

  round(res, precision);
  return res;
}

// Вычисление acot(x) = pi/2 - atan(x)
Fraction functions::acot(const Fraction &a, const size_t precision) {
  Fraction res = (getPi(PRECISION_OF_FUNCTIONS) / 2 - functions::atan(a, precision));
  round(res, precision);
  return res;
}

/*
  Вычисление факториала через разложение множителей в дерево. Такое вычисление факториала быстрее, чем наивный алгоритм,
  т.к. умножать большие числа примерно равной длины гораздо быстрее, чем большие числа на маленькие. Это обусловлено
  использованием алгоритма Карацубы.
*/
BigInteger factorialTree(const BigInteger &left, const BigInteger &right) {
  if (left == right) {
    return left;
  }
  if (right - left == 1) {
    return left * right;
  }
  BigInteger mid = (left + right) / 2;
  return factorialTree(left, mid) * factorialTree(mid + 1, right);
}

// Обертка над вычислением факториала через дерево
Fraction functions::factorial(const Fraction &a) {
  if (a < 0 || a.getNumerator() != 0) {
    throw OutOfRange("factorial");
  }
  if (a < 2) {
    return 1;
  }
  return factorialTree(2, a.getInteger());
}

// Вычисление двойного факториала (наивный алгоритм)
Fraction functions::doubleFactorial(const Fraction &a) {
  if (a < 0 || a.getNumerator() != 0) {
    throw OutOfRange("factorial");
  }
  BigInteger res = 1;
  for (BigInteger i = a.getInteger(); i > 0; i -= 2) {
    res *= i;
  }
  return res;
}

// Вычисление значения e через ряд Тейлора: e = sum_{k=0}^{inf} 1/n!
Fraction functions::getE(const size_t precision) {
  if (precision <= PRECISION_OF_CONSTANTS) {
    return Calculator::getE();
  }

  BigInteger k = 1;
  Fraction a_i = 1, res = 1;
  Fraction precisionFrac = getPrecisionFrac(precision);

  do {
    a_i /= k;
    round(a_i, precision);
    res += a_i;
    ++k;
  } while (abs(a_i) > precisionFrac);

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
Fraction functions::getPi(const size_t precision) {
  if (precision <= PRECISION_OF_CONSTANTS) {
    return Calculator::getPi();
  }

  BigInteger numOfIterations = functions::lb(precision, PRECISION).getInteger() + 1;
  BigInteger p = 1;
  Fraction a = 1, b = 1 / functions::sqrt(2, precision), t = Fraction(1, 4);

  for (BigInteger i = 0; i < numOfIterations; ++i) {
    Fraction prevA = a, prevB = b, prevT = t;
    a = (prevA + prevB) / 2;
    b = functions::sqrt(prevA * prevB, precision);
    Fraction diff = (prevA - a);
    t = prevT - p * diff * diff;
    round(t, precision);
    p *= 2;
  }

  Fraction res = (a + b) * (a + b) / (4 * t);
  round(res, precision);
  return res;
}
