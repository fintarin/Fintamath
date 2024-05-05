#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"

using namespace fintamath;

TEST(SimplifyInfinityTests, simplifyTest) {
  EXPECT_EQ(Expression("Inf").toString(),
            "Inf");
  EXPECT_EQ(Expression("-Inf").toString(),
            "-Inf");
  EXPECT_EQ(Expression("ComplexInf").toString(),
            "ComplexInf");
  EXPECT_EQ(Expression("-ComplexInf").toString(),
            "ComplexInf");
  EXPECT_EQ(Expression("1/0").toString(),
            "ComplexInf");
  EXPECT_EQ(Expression("a/0").toString(),
            "ComplexInf");
  EXPECT_EQ(Expression("1/Inf").toString(),
            "0");
  EXPECT_EQ(Expression("1/-Inf").toString(),
            "0");
  EXPECT_EQ(Expression("a/Inf").toString(),
            "0");
  EXPECT_EQ(Expression("a/-Inf").toString(),
            "0");
  EXPECT_EQ(Expression("1/ComplexInf").toString(),
            "0");
  EXPECT_EQ(Expression("a/ComplexInf").toString(),
            "0");
  EXPECT_EQ(Expression("0/Inf").toString(),
            "0");
  EXPECT_EQ(Expression("Inf/0").toString(),
            "ComplexInf");
  EXPECT_EQ(Expression("0/-Inf").toString(),
            "0");
  EXPECT_EQ(Expression("-Inf/0").toString(),
            "ComplexInf");
  EXPECT_EQ(Expression("0/ComplexInf").toString(),
            "0");
  EXPECT_EQ(Expression("ComplexInf/0").toString(),
            "ComplexInf");
  EXPECT_EQ(Expression("0 / (Inf x)").toString(),
            "0");
  EXPECT_EQ(Expression("(Inf/x) / 0").toString(),
            "ComplexInf");
  EXPECT_EQ(Expression("1/Inf - 1").toString(),
            "-1");
  EXPECT_EQ(Expression("Inf/2 - 1").toString(),
            "Inf");
  EXPECT_EQ(Expression("Inf + Inf").toString(),
            "Inf");
  EXPECT_EQ(Expression("-Inf - Inf").toString(),
            "-Inf");
  EXPECT_EQ(Expression("10 + Inf").toString(),
            "Inf");
  EXPECT_EQ(Expression("-10 + Inf").toString(),
            "Inf");
  EXPECT_EQ(Expression("10 - Inf").toString(),
            "-Inf");
  EXPECT_EQ(Expression("-10 - Inf").toString(),
            "-Inf");
  EXPECT_EQ(Expression("I + Inf").toString(),
            "Inf");
  EXPECT_EQ(Expression("I - Inf").toString(),
            "-Inf");
  EXPECT_EQ(Expression("I + ComplexInf").toString(),
            "ComplexInf");
  EXPECT_EQ(Expression("a + Inf").toString(),
            "Inf");
  EXPECT_EQ(Expression("-a - Inf").toString(),
            "-Inf");
  EXPECT_EQ(Expression("a + ComplexInf").toString(),
            "ComplexInf");
  EXPECT_EQ(Expression("a - ComplexInf").toString(),
            "ComplexInf");
  EXPECT_EQ(Expression("10 * Inf").toString(),
            "Inf");
  EXPECT_EQ(Expression("-10 * Inf").toString(),
            "-Inf");
  EXPECT_EQ(Expression("-2/3 * Inf").toString(),
            "-Inf");
  EXPECT_EQ(Expression("(I+2) * Inf").toString(),
            "(2 + I) Inf");
  EXPECT_EQ(Expression("(I+2) * -Inf").toString(),
            "(-2 - I) Inf");
  EXPECT_EQ(Expression("(I+2) * ComplexInf").toString(),
            "ComplexInf");
  EXPECT_EQ(Expression("Inf * Inf").toString(),
            "Inf");
  EXPECT_EQ(Expression("Inf * -Inf").toString(),
            "-Inf");
  EXPECT_EQ(Expression("-Inf * -Inf").toString(),
            "Inf");
  EXPECT_EQ(Expression("ComplexInf*ComplexInf").toString(),
            "ComplexInf");
  EXPECT_EQ(Expression("ComplexInf*Inf").toString(),
            "ComplexInf");
  EXPECT_EQ(Expression("ComplexInf*-Inf").toString(),
            "ComplexInf");
  EXPECT_EQ(Expression("a * Inf").toString(),
            "Inf a");
  EXPECT_EQ(Expression("Inf * (Inf x)").toString(),
            "Inf x");
  EXPECT_EQ(Expression("Inf * (Inf/x)").toString(),
            "Inf/x");
  EXPECT_EQ(Expression("Inf / a").toString(),
            "Inf/a");
  EXPECT_EQ(Expression("Inf / 2").toString(),
            "Inf");
  EXPECT_EQ(Expression("Inf / -2").toString(),
            "-Inf");
  EXPECT_EQ(Expression("Inf / I").toString(),
            "-I Inf");
  EXPECT_EQ(Expression("Inf / (-I - 3)").toString(),
            "-((3 - I) Inf)/10");
  EXPECT_EQ(Expression("Inf^2").toString(),
            "Inf");
  EXPECT_EQ(Expression("Inf^(2/3)").toString(),
            "Inf");
  EXPECT_EQ(Expression("Inf^-2").toString(),
            "0");
  EXPECT_EQ(Expression("Inf^(-2/3)").toString(),
            "0");
  EXPECT_EQ(Expression("(-Inf)^2").toString(),
            "Inf");
  EXPECT_EQ(Expression("(-Inf)^3").toString(),
            "-Inf");
  EXPECT_EQ(Expression("(-Inf)^(2/3)").toString(),
            "Inf sign((-1)^(2/3))");
  EXPECT_EQ(Expression("ComplexInf^2").toString(),
            "ComplexInf");
  EXPECT_EQ(Expression("ComplexInf^(2/3)").toString(),
            "ComplexInf");
  EXPECT_EQ(Expression("ComplexInf^-2").toString(),
            "0");
  EXPECT_EQ(Expression("ComplexInf^(-2/3)").toString(),
            "0");
  EXPECT_EQ(Expression("Inf^(I+2)").toString(),
            "ComplexInf");
  EXPECT_EQ(Expression("Inf^(I-2)").toString(),
            "0");
  EXPECT_EQ(Expression("Inf^(-I+2)").toString(),
            "ComplexInf");
  EXPECT_EQ(Expression("Inf^(-I-2)").toString(),
            "0");
  EXPECT_EQ(Expression("(-Inf)^(I+2)").toString(),
            "ComplexInf");
  EXPECT_EQ(Expression("(-Inf)^(I-2)").toString(),
            "0");
  EXPECT_EQ(Expression("(-Inf)^(-I+2)").toString(),
            "ComplexInf");
  EXPECT_EQ(Expression("(-Inf)^(-I-2)").toString(),
            "0");
  EXPECT_EQ(Expression("ComplexInf^(I+2)").toString(),
            "ComplexInf");
  EXPECT_EQ(Expression("ComplexInf^(I-2)").toString(),
            "0");
  EXPECT_EQ(Expression("ComplexInf^(-I+2)").toString(),
            "ComplexInf");
  EXPECT_EQ(Expression("ComplexInf^(-I-2)").toString(),
            "0");
  EXPECT_EQ(Expression("0^Inf").toString(),
            "0");
  EXPECT_EQ(Expression("0^-Inf").toString(),
            "ComplexInf");
  EXPECT_EQ(Expression("0^-1").toString(),
            "ComplexInf");
  EXPECT_EQ(Expression("2^Inf").toString(),
            "Inf");
  EXPECT_EQ(Expression("2^-Inf").toString(),
            "0");
  EXPECT_EQ(Expression("0.2^Inf").toString(),
            "0");
  EXPECT_EQ(Expression("0.2^-Inf").toString(),
            "Inf");
  EXPECT_EQ(Expression("Inf^Inf").toString(),
            "ComplexInf");
  EXPECT_EQ(Expression("(-Inf)^Inf").toString(),
            "ComplexInf");
  EXPECT_EQ(Expression("ComplexInf^Inf").toString(),
            "ComplexInf");
  EXPECT_EQ(Expression("0^(Inf/x)").toString(),
            "0^(Inf/x)");
  EXPECT_EQ(Expression("1^(Inf/x)").toString(),
            "1^(Inf/x)");
  EXPECT_EQ(Expression("sqrt(2) * Inf").toString(),
            "Inf");
  EXPECT_EQ(Expression("-sqrt(2) * Inf").toString(),
            "-Inf");
  EXPECT_EQ(Expression("sqrt(2) ^ Inf").toString(),
            "Inf");
  EXPECT_EQ(Expression("sqrt(0.5) ^ Inf").toString(),
            "0");
  EXPECT_EQ(Expression("sqrt(2) ^ (-Inf)").toString(),
            "0");
  EXPECT_EQ(Expression("sqrt(0.5) ^ (-Inf)").toString(),
            "Inf");
  EXPECT_EQ(Expression("Inf ^ sqrt(5)").toString(),
            "Inf");
  EXPECT_EQ(Expression("Inf ^ -sqrt(5)").toString(),
            "0");
  EXPECT_EQ(Expression("(-Inf) ^ sqrt(5)").toString(),
            "Inf sign((-1)^sqrt(5))");
  EXPECT_EQ(Expression("(-Inf) ^ -sqrt(5)").toString(),
            "0");
  EXPECT_EQ(Expression("ComplexInf ^ sqrt(5)").toString(),
            "ComplexInf");
  EXPECT_EQ(Expression("ComplexInf ^ -sqrt(5)").toString(),
            "0");
  EXPECT_EQ(Expression("sin(Inf)").toString(),
            "sin(Inf)"); // TODO: [-1, 1]
  EXPECT_EQ(Expression("log(1, 0)").toString(),
            "ComplexInf");
  EXPECT_EQ(Expression("log(1, 10)").toString(),
            "ComplexInf");
  EXPECT_EQ(Expression("log(10, 0)").toString(),
            "-Inf");
  EXPECT_EQ(Expression("log(1/10, 0)").toString(),
            "Inf");
  EXPECT_EQ(Expression("ln(0)").toString(),
            "-Inf");
  EXPECT_EQ(Expression("ln(Inf)").toString(),
            "Inf");
  EXPECT_EQ(Expression("ln(-Inf)").toString(),
            "Inf");
  EXPECT_EQ(Expression("ln(ComplexInf)").toString(),
            "Inf");
  EXPECT_EQ(Expression("(-1)!").toString(),
            "ComplexInf");
  EXPECT_EQ(Expression("tan(Pi/2)").toString(),
            "ComplexInf");
  EXPECT_EQ(Expression("tan(3/2*Pi)").toString(),
            "ComplexInf");
  EXPECT_EQ(Expression("cot(0)").toString(),
            "ComplexInf");
  EXPECT_EQ(Expression("cot(2*Pi)").toString(),
            "ComplexInf");
  EXPECT_EQ(Expression("sin(Inf)^2 + cos(Inf)^2").toString(),
            "sin(Inf)^2 + cos(Inf)^2");
  EXPECT_EQ(Expression("sin(Inf) cos(Inf)").toString(),
            "sin(Inf) cos(Inf)");
  EXPECT_EQ(Expression("tan(Inf)").toString(),
            "tan(Inf)");
  EXPECT_EQ(Expression("tan(Inf) * cot(Inf)").toString(),
            "tan(Inf) cot(Inf)");
  EXPECT_EQ(Expression("sign(Inf)").toString(),
            "1");
  EXPECT_EQ(Expression("sign(-Inf)").toString(),
            "-1");
  EXPECT_EQ(Expression("abs(Inf)").toString(),
            "Inf");
  EXPECT_EQ(Expression("abs(-Inf)").toString(),
            "Inf");
  EXPECT_EQ(Expression("abs(ComplexInf)").toString(),
            "Inf");
  EXPECT_EQ(Expression("0/sign(Inf)").toString(),
            "0");
  EXPECT_EQ(Expression("sign(Inf)/0").toString(),
            "ComplexInf");
  EXPECT_EQ(Expression("0^sign(Inf)").toString(),
            "0");
  EXPECT_EQ(Expression("sign(Inf)^0").toString(),
            "1");
  EXPECT_EQ(Expression("0 (Inf!)").toString(),
            "0 Inf!");
  EXPECT_EQ(Expression("0/(Inf!)").toString(),
            "0");
  EXPECT_EQ(Expression("(Inf!)/0").toString(),
            "ComplexInf");
  EXPECT_EQ(Expression("0^(Inf!)").toString(),
            "0^(Inf!)");
  EXPECT_EQ(Expression("(Inf!)^0").toString(),
            "(Inf!)^0");
  EXPECT_EQ(Expression("log((Inf!), (Inf!))").toString(),
            "log(Inf!, Inf!)");
  EXPECT_EQ(Expression("log((Inf!), Inf)").toString(),
            "log(Inf!, Inf)");
  EXPECT_EQ(Expression("log(Inf, (Inf!))").toString(),
            "log(Inf, Inf!)");
  EXPECT_EQ(Expression("log((Inf!), 1)").toString(),
            "log(Inf!, 1)");
  EXPECT_EQ(Expression("log(1, (Inf!))").toString(),
            "log(1, Inf!)");

  EXPECT_EQ(Expression("Inf = Inf").toString(),
            "True");
  EXPECT_EQ(Expression("Inf = -Inf").toString(),
            "False");
  EXPECT_EQ(Expression("-Inf = Inf").toString(),
            "False");
  EXPECT_EQ(Expression("-Inf = -Inf").toString(),
            "True");
  EXPECT_EQ(Expression("x = Inf").toString(),
            "False");
  EXPECT_EQ(Expression("x = -Inf").toString(),
            "False");
  EXPECT_EQ(Expression("Inf = x").toString(),
            "False");
  EXPECT_EQ(Expression("-Inf = x").toString(),
            "False");
  EXPECT_EQ(Expression("x != Inf").toString(),
            "True");
  EXPECT_EQ(Expression("x != -Inf").toString(),
            "True");
  EXPECT_EQ(Expression("Inf != x").toString(),
            "True");
  EXPECT_EQ(Expression("-Inf != x").toString(),
            "True");
  EXPECT_EQ(Expression("x > Inf").toString(),
            "x > Inf");
  EXPECT_EQ(Expression("x < Inf").toString(),
            "x < Inf");
  EXPECT_EQ(Expression("x <= Inf").toString(),
            "x <= Inf");
  EXPECT_EQ(Expression("x >= Inf").toString(),
            "x >= Inf");
  EXPECT_EQ(Expression("x > -Inf").toString(),
            "x > -Inf");
  EXPECT_EQ(Expression("x < -Inf").toString(),
            "x < -Inf");
  EXPECT_EQ(Expression("x <= -Inf").toString(),
            "x <= -Inf");
  EXPECT_EQ(Expression("x >= -Inf").toString(),
            "x >= -Inf");
  EXPECT_EQ(Expression("Inf > x").toString(),
            "Inf > x");
  EXPECT_EQ(Expression("Inf < x").toString(),
            "Inf < x");
  EXPECT_EQ(Expression("Inf <= x").toString(),
            "Inf <= x");
  EXPECT_EQ(Expression("Inf >= x").toString(),
            "Inf >= x");
  EXPECT_EQ(Expression("-Inf > x").toString(),
            "-Inf > x");
  EXPECT_EQ(Expression("-Inf < x").toString(),
            "-Inf < x");
  EXPECT_EQ(Expression("-Inf <= x").toString(),
            "-Inf <= x");
  EXPECT_EQ(Expression("-Inf >= x").toString(),
            "-Inf >= x");
  EXPECT_EQ(Expression("x Inf = Inf").toString(),
            "Inf x = Inf");
  EXPECT_EQ(Expression("Inf = x Inf").toString(),
            "Inf = Inf x");
  EXPECT_EQ(Expression("x Inf < Inf").toString(),
            "Inf x < Inf");
  EXPECT_EQ(Expression("Inf < x Inf").toString(),
            "Inf < Inf x");
  EXPECT_EQ(Expression("x Inf = 0").toString(),
            "Inf x = 0");
  EXPECT_EQ(Expression("0 = x Inf").toString(),
            "0 = Inf x");
  EXPECT_EQ(Expression("x Inf < 0").toString(),
            "Inf x < 0");
  EXPECT_EQ(Expression("0 < x Inf").toString(),
            "0 < Inf x");
  EXPECT_EQ(Expression("x = ComplexInf").toString(),
            "False");
  EXPECT_EQ(Expression("x != ComplexInf").toString(),
            "True");
  EXPECT_EQ(Expression("x < ComplexInf").toString(),
            "x < ComplexInf");
  EXPECT_EQ(Expression("x > ComplexInf").toString(),
            "x > ComplexInf");
  EXPECT_EQ(Expression("x <= ComplexInf").toString(),
            "x <= ComplexInf");
  EXPECT_EQ(Expression("x >= ComplexInf").toString(),
            "x >= ComplexInf");
  EXPECT_EQ(Expression("ComplexInf = x").toString(),
            "False");
  EXPECT_EQ(Expression("ComplexInf != x").toString(),
            "True");
  EXPECT_EQ(Expression("ComplexInf < x").toString(),
            "ComplexInf < x");
  EXPECT_EQ(Expression("ComplexInf > x").toString(),
            "ComplexInf > x");
  EXPECT_EQ(Expression("ComplexInf <= x").toString(),
            "ComplexInf <= x");
  EXPECT_EQ(Expression("ComplexInf >= x").toString(),
            "ComplexInf >= x");
  EXPECT_EQ(Expression("ComplexInf = ComplexInf").toString(),
            "ComplexInf = ComplexInf");
  EXPECT_EQ(Expression("Inf = Inf").toString(),
            "True");
  EXPECT_EQ(Expression("Inf != Inf").toString(),
            "False");
  EXPECT_EQ(Expression("Inf > Inf").toString(),
            "False");
  EXPECT_EQ(Expression("Inf < Inf").toString(),
            "False");
  EXPECT_EQ(Expression("Inf <= Inf").toString(),
            "True");
  EXPECT_EQ(Expression("-Inf >= Inf").toString(),
            "False");
  EXPECT_EQ(Expression("-Inf = Inf").toString(),
            "False");
  EXPECT_EQ(Expression("-Inf != Inf").toString(),
            "True");
  EXPECT_EQ(Expression("-Inf > Inf").toString(),
            "False");
  EXPECT_EQ(Expression("-Inf < Inf").toString(),
            "True");
  EXPECT_EQ(Expression("-Inf <= Inf").toString(),
            "True");
  EXPECT_EQ(Expression("-Inf >= Inf").toString(),
            "False");
  EXPECT_EQ(Expression("Inf = -Inf").toString(),
            "False");
  EXPECT_EQ(Expression("Inf != -Inf").toString(),
            "True");
  EXPECT_EQ(Expression("Inf > -Inf").toString(),
            "True");
  EXPECT_EQ(Expression("Inf < -Inf").toString(),
            "False");
  EXPECT_EQ(Expression("Inf <= -Inf").toString(),
            "False");
  EXPECT_EQ(Expression("Inf >= -Inf").toString(),
            "True");
  EXPECT_EQ(Expression("ComplexInf = Inf").toString(),
            "ComplexInf = Inf");
  EXPECT_EQ(Expression("ComplexInf != Inf").toString(),
            "ComplexInf != Inf");
  EXPECT_EQ(Expression("ComplexInf > Inf").toString(),
            "ComplexInf > Inf");
  EXPECT_EQ(Expression("ComplexInf < Inf").toString(),
            "ComplexInf < Inf");
  EXPECT_EQ(Expression("ComplexInf >= Inf").toString(),
            "ComplexInf >= Inf");
  EXPECT_EQ(Expression("ComplexInf <= Inf").toString(),
            "ComplexInf <= Inf");
  EXPECT_EQ(Expression("ComplexInf = -Inf").toString(),
            "ComplexInf = -Inf");
  EXPECT_EQ(Expression("ComplexInf != -Inf").toString(),
            "ComplexInf != -Inf");
  EXPECT_EQ(Expression("ComplexInf > -Inf").toString(),
            "ComplexInf > -Inf");
  EXPECT_EQ(Expression("ComplexInf < -Inf").toString(),
            "ComplexInf < -Inf");
  EXPECT_EQ(Expression("ComplexInf >= -Inf").toString(),
            "ComplexInf >= -Inf");
  EXPECT_EQ(Expression("ComplexInf <= -Inf").toString(),
            "ComplexInf <= -Inf");
  EXPECT_EQ(Expression("Inf = ComplexInf").toString(),
            "Inf = ComplexInf");
  EXPECT_EQ(Expression("Inf != ComplexInf").toString(),
            "Inf != ComplexInf");
  EXPECT_EQ(Expression("Inf > ComplexInf").toString(),
            "Inf > ComplexInf");
  EXPECT_EQ(Expression("Inf < ComplexInf").toString(),
            "Inf < ComplexInf");
  EXPECT_EQ(Expression("Inf >= ComplexInf").toString(),
            "Inf >= ComplexInf");
  EXPECT_EQ(Expression("Inf <= ComplexInf").toString(),
            "Inf <= ComplexInf");
  EXPECT_EQ(Expression("-Inf = ComplexInf").toString(),
            "-Inf = ComplexInf");
  EXPECT_EQ(Expression("-Inf != ComplexInf").toString(),
            "-Inf != ComplexInf");
  EXPECT_EQ(Expression("-Inf > ComplexInf").toString(),
            "-Inf > ComplexInf");
  EXPECT_EQ(Expression("-Inf < ComplexInf").toString(),
            "-Inf < ComplexInf");
  EXPECT_EQ(Expression("-Inf >= ComplexInf").toString(),
            "-Inf >= ComplexInf");
  EXPECT_EQ(Expression("-Inf <= ComplexInf").toString(),
            "-Inf <= ComplexInf");
  EXPECT_EQ(Expression("Inf * Inf + Inf - Inf * -1% = Inf").toString(),
            "True");
  EXPECT_EQ(Expression("Inf * Inf + Inf - Inf * -1% != Inf").toString(),
            "False");
  EXPECT_EQ(Expression("Inf * Inf + Inf - Inf * -1% < Inf").toString(),
            "False");
  EXPECT_EQ(Expression("Inf * Inf + Inf - Inf * -1% > Inf").toString(),
            "False");
  EXPECT_EQ(Expression("Inf * Inf + Inf - Inf * -1% <= Inf").toString(),
            "True");
  EXPECT_EQ(Expression("Inf * Inf + Inf - Inf * -1% >= Inf").toString(),
            "True");

  EXPECT_EQ(Expression("0*Inf").toString(),
            "Undefined");
  EXPECT_EQ(Expression("0*-Inf").toString(),
            "Undefined");
  EXPECT_EQ(Expression("0*ComplexInf").toString(),
            "Undefined");
  EXPECT_EQ(Expression("Inf - Inf").toString(),
            "Undefined");
  EXPECT_EQ(Expression("ComplexInf - ComplexInf").toString(),
            "Undefined");
  EXPECT_EQ(Expression("ComplexInf + ComplexInf").toString(),
            "Undefined");
  EXPECT_EQ(Expression("ComplexInf + Inf").toString(),
            "Undefined");
  EXPECT_EQ(Expression("ComplexInf - Inf").toString(),
            "Undefined");
  EXPECT_EQ(Expression("Inf + ComplexInf").toString(),
            "Undefined");
  EXPECT_EQ(Expression("-Inf + ComplexInf").toString(),
            "Undefined");
  EXPECT_EQ(Expression("0/0").toString(),
            "Undefined");
  EXPECT_EQ(Expression("Inf/Inf").toString(),
            "Undefined");
  EXPECT_EQ(Expression("-Inf/-Inf").toString(),
            "Undefined");
  EXPECT_EQ(Expression("Inf/-Inf").toString(),
            "Undefined");
  EXPECT_EQ(Expression("-Inf/Inf").toString(),
            "Undefined");
  EXPECT_EQ(Expression("ComplexInf/ComplexInf").toString(),
            "Undefined");
  EXPECT_EQ(Expression("ComplexInf/Inf").toString(),
            "Undefined");
  EXPECT_EQ(Expression("ComplexInf/-Inf").toString(),
            "Undefined");
  EXPECT_EQ(Expression("Inf/ComplexInf").toString(),
            "Undefined");
  EXPECT_EQ(Expression("-Inf/ComplexInf").toString(),
            "Undefined");
  EXPECT_EQ(Expression("x Inf / Inf").toString(),
            "Undefined");
  EXPECT_EQ(Expression("-Inf + Inf").toString(),
            "Undefined");
  EXPECT_EQ(Expression("Inf - Inf").toString(),
            "Undefined");
  EXPECT_EQ(Expression("0^0").toString(),
            "Undefined");
  EXPECT_EQ(Expression("Inf^0").toString(),
            "Undefined");
  EXPECT_EQ(Expression("(-Inf)^0").toString(),
            "Undefined");
  EXPECT_EQ(Expression("ComplexInf^0").toString(),
            "Undefined");
  EXPECT_EQ(Expression("Inf^I").toString(),
            "Undefined");
  EXPECT_EQ(Expression("(-Inf)^I").toString(),
            "Undefined");
  EXPECT_EQ(Expression("(ComplexInf)^I").toString(),
            "Undefined");
  EXPECT_EQ(Expression("1^Inf").toString(),
            "Undefined");
  EXPECT_EQ(Expression("1^-Inf").toString(),
            "Undefined");
  EXPECT_EQ(Expression("1^ComplexInf").toString(),
            "Undefined");
  EXPECT_EQ(Expression("x^ComplexInf").toString(),
            "Undefined");
  EXPECT_EQ(Expression("I^Inf").toString(),
            "Undefined");
  EXPECT_EQ(Expression("I^-Inf").toString(),
            "Undefined");
  EXPECT_EQ(Expression("I^ComplexInf").toString(),
            "Undefined");
  EXPECT_EQ(Expression("2^ComplexInf").toString(),
            "Undefined");
  EXPECT_EQ(Expression("0.2^ComplexInf").toString(),
            "Undefined");
  EXPECT_EQ(Expression("(x Inf)^0").toString(),
            "Undefined");
  EXPECT_EQ(Expression("0^(x Inf)").toString(),
            "Undefined");
  EXPECT_EQ(Expression("1^(x Inf)").toString(),
            "Undefined");
  EXPECT_EQ(Expression("sin(0/0)").toString(),
            "Undefined");
  EXPECT_EQ(Expression("1 + 0^0").toString(),
            "Undefined");
  EXPECT_EQ(Expression("1 + sin(asin(0^0)) + x").toString(),
            "Undefined");
  EXPECT_EQ(Expression("1 + (2^2 - 4)^0").toString(),
            "Undefined");
  EXPECT_EQ(Expression("0^((2^2 - 4)^0)").toString(),
            "Undefined");
  EXPECT_EQ(Expression("-((2^2 - 4)^0)").toString(),
            "Undefined");
  EXPECT_EQ(Expression("sin(-((2^2 - 4)^0))").toString(),
            "Undefined");
  EXPECT_EQ(Expression("0^0 - 0^0").toString(),
            "Undefined");
  EXPECT_EQ(Expression("0^0 * 0").toString(),
            "Undefined");
  EXPECT_EQ(Expression("0^0 / 0").toString(),
            "Undefined");
  EXPECT_EQ(Expression("0 / 0^0").toString(),
            "Undefined");
  EXPECT_EQ(Expression("0^0 / 0^0").toString(),
            "Undefined");
  EXPECT_EQ(Expression("(x/x - 1)^0 / 0^0").toString(),
            "Undefined");
  EXPECT_EQ(Expression("0/0 - 0/0").toString(),
            "Undefined");
  EXPECT_EQ(Expression("0/0 * 0").toString(),
            "Undefined");
  EXPECT_EQ(Expression("0/0 / 0").toString(),
            "Undefined");
  EXPECT_EQ(Expression("Inf / (Inf x)").toString(),
            "Undefined");
  EXPECT_EQ(Expression("(Inf x) / Inf").toString(),
            "Undefined");
  EXPECT_EQ(Expression("0 * (Inf x)").toString(),
            "Undefined");
  EXPECT_EQ(Expression("Inf^x").toString(),
            "Undefined");
  EXPECT_EQ(Expression("Inf^-x").toString(),
            "Undefined");
  EXPECT_EQ(Expression("x^Inf").toString(),
            "Undefined");
  EXPECT_EQ(Expression("(-x)^Inf").toString(),
            "Undefined");
  EXPECT_EQ(Expression("(Inf x) ^ 0").toString(),
            "Undefined");
  EXPECT_EQ(Expression("(Inf x) ^ Inf").toString(),
            "Undefined");
  EXPECT_EQ(Expression("0 ^ (Inf x)").toString(),
            "Undefined");
  EXPECT_EQ(Expression("Inf ^ (Inf x)").toString(),
            "Undefined");
  EXPECT_EQ(Expression("(Inf/x)^0").toString(),
            "Undefined");
  EXPECT_EQ(Expression("log(1, 1)").toString(),
            "Undefined");
  EXPECT_EQ(Expression("log(0, 0)").toString(),
            "Undefined");
  EXPECT_EQ(Expression("log(Inf, Inf)").toString(),
            "Undefined");
  EXPECT_EQ(Expression("log(0, Inf)").toString(),
            "Undefined");
  EXPECT_EQ(Expression("log(Inf, 0)").toString(),
            "Undefined");
  EXPECT_EQ(Expression("log(-Inf, -Inf)").toString(),
            "Undefined");
  EXPECT_EQ(Expression("log(0, -Inf)").toString(),
            "Undefined");
  EXPECT_EQ(Expression("log(-Inf, 0)").toString(),
            "Undefined");
  EXPECT_EQ(Expression("log(Inf, -Inf)").toString(),
            "Undefined");
  EXPECT_EQ(Expression("log(-Inf, Inf)").toString(),
            "Undefined");
  EXPECT_EQ(Expression("log(ComplexInf, ComplexInf)").toString(),
            "Undefined");
  EXPECT_EQ(Expression("log(0, ComplexInf)").toString(),
            "Undefined");
  EXPECT_EQ(Expression("log(ComplexInf, 0)").toString(),
            "Undefined");
  EXPECT_EQ(Expression("log(ComplexInf, Inf)").toString(),
            "Undefined");
  EXPECT_EQ(Expression("log(ComplexInf, -Inf)").toString(),
            "Undefined");
  EXPECT_EQ(Expression("log(Inf, ComplexInf)").toString(),
            "Undefined");
  EXPECT_EQ(Expression("log(-Inf, ComplexInf)").toString(),
            "Undefined");
  EXPECT_EQ(Expression("log(x Inf, Inf)").toString(),
            "Undefined");
  EXPECT_EQ(Expression("log(Inf, x Inf)").toString(),
            "Undefined");
  EXPECT_EQ(Expression("log(0^0, 0^0)").toString(),
            "Undefined");
  EXPECT_EQ(Expression("log(sign(Inf), -sign(-Inf))").toString(),
            "Undefined");
  EXPECT_EQ(Expression("tan(Pi) * cot(Pi)").toString(),
            "Undefined");
  EXPECT_EQ(Expression("sign(ComplexInf)").toString(),
            "Undefined");
  EXPECT_EQ(Expression("root(2, 0)").toString(),
            "Undefined");

  EXPECT_EQ(Expression("Undefined").toString(),
            "Undefined");
  EXPECT_EQ(Expression("-Undefined").toString(),
            "Undefined");
  EXPECT_EQ(Expression("Undefined!").toString(),
            "Undefined");
  EXPECT_EQ(Expression("Undefined + 10").toString(),
            "Undefined");
  EXPECT_EQ(Expression("Undefined - 10").toString(),
            "Undefined");
  EXPECT_EQ(Expression("0/Undefined").toString(),
            "Undefined");
  EXPECT_EQ(Expression("1/Undefined").toString(),
            "Undefined");
  EXPECT_EQ(Expression("Undefined^1").toString(),
            "Undefined");
  EXPECT_EQ(Expression("Undefined^0").toString(),
            "Undefined");
  EXPECT_EQ(Expression("sin(Undefined)").toString(),
            "Undefined");

  EXPECT_EQ(Expression("Undefined = Undefined").toString(),
            "Undefined = Undefined");
  EXPECT_EQ(Expression("0/0 = 0/0").toString(),
            "Undefined = Undefined");
  EXPECT_EQ(Expression("(sin(x)^2 + cos(x)^2 - 1)/0 = 0/(sin(x)^2 + cos(x)^2 - 1)").toString(),
            "Undefined = Undefined");
  EXPECT_EQ(Expression("Inf - Inf = 0").toString(),
            "Undefined = Undefined");
  EXPECT_EQ(Expression("Inf - Inf = 0 | a").toString(),
            "a | Undefined = Undefined");
  EXPECT_EQ(Expression("Undefined < Undefined").toString(),
            "Undefined < Undefined");
  EXPECT_EQ(Expression("0/0 < 0/0").toString(),
            "Undefined < Undefined");
  EXPECT_EQ(Expression("(sin(x)^2 + cos(x)^2 - 1)/0 < 0/(sin(x)^2 + cos(x)^2 - 1)").toString(),
            "Undefined < Undefined");
  EXPECT_EQ(Expression("Inf - Inf < 0").toString(),
            "Undefined < Undefined");
  EXPECT_EQ(Expression("Inf - Inf < 0 | a").toString(),
            "a | Undefined < Undefined");
}
