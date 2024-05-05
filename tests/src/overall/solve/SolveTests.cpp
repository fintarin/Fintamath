#include <gtest/gtest.h>

#include "fintamath/expressions/ExpressionFunctions.hpp"

using namespace fintamath;

// TODO!!! uncomment

// TEST(SolveTests, solveTest) {
//   EXPECT_EQ(solve(Expression("x - 10 = 0")).toString(),
//             "x = 10");
//   EXPECT_EQ(solve(Expression("-10 - x = 0")).toString(),
//             "x = -10");

//   EXPECT_EQ(solve(Expression("z - 10 - I = 0")).toString(),
//             "z = 10 + I");
//   EXPECT_EQ(solve(Expression("(6 + 3I)^2 = 4I - 30z")).toString(),
//             "z = -9/10 - 16/15 I");

//   EXPECT_EQ(solve(Expression("x^2 - 10 = 39")).toString(),
//             "x = -7 | x = 7");
//   EXPECT_EQ(solve(Expression("x^2 = 0")).toString(),
//             "x = 0");
//   EXPECT_EQ(solve(Expression("x^2 = 1")).toString(),
//             "x = -1 | x = 1");
//   EXPECT_EQ(solve(Expression("x^2 - 2x - 3 = 0")).toString(),
//             "x = -1 | x = 3");
//   EXPECT_EQ(solve(Expression("15 - 2x - x^2 = 0")).toString(),
//             "x = -5 | x = 3");
//   EXPECT_EQ(solve(Expression("x^2 + 12x + 36 = 0")).toString(),
//             "x = -6");
//   EXPECT_EQ(solve(Expression("x^2 + 12x = 0")).toString(),
//             "x = -12 | x = 0");
//   EXPECT_EQ(solve(Expression("x^2 - 23x - 3 = 0")).toString(),
//             "x = -sqrt(541)/2 + 23/2 | x = sqrt(541)/2 + 23/2");
//   EXPECT_EQ(solve(Expression("-12x^2 - 23x + 30 = 0")).toString(),
//             "x = -sqrt(1969)/24 - 23/24 | x = sqrt(1969)/24 - 23/24");
//   EXPECT_EQ(solve(Expression("-33x^2 - x + 34 = 0")).toString(),
//             "x = -34/33 | x = 1");
//   EXPECT_EQ(solve(Expression("2x^2 + 2sqrt(2)x + 1 = 0")).toString(),
//             "x = -sqrt(2)/2");

//   EXPECT_EQ(solve(Expression("x^2 = -1")).toString(),
//             "x = -I | x = I");
//   EXPECT_EQ(solve(Expression("x^2 + 4x + 5 = 0")).toString(),
//             "x = -2 - I | x = -2 + I");
//   EXPECT_EQ(solve(Expression("2x^2 + x + 1 = 0")).toString(),
//             "x = -(I sqrt(7))/4 - 1/4 | x = (I sqrt(7))/4 - 1/4");
//   EXPECT_EQ(solve(Expression("x^2 + 3x + 5 = 0")).toString(),
//             "x = -(I sqrt(11))/2 - 3/2 | x = (I sqrt(11))/2 - 3/2");

//   // TODO: implement cubic equations
//   EXPECT_EQ(solve(Expression("x^3 - 3x^2 + 3x - 1 = 0")).toString(),
//             "x^3 - 3 x^2 + 3 x - 1 = 0"); // TODO: x = 1
//   // EXPECT_EQ(solve(Expression("x^3 - 6x^2 + 11x - 6 = 0")).toString(),
//   //           "x = 1 | x = 2 | x = 3");
//   // EXPECT_EQ(solve(Expression("x^3 + 2x^2 - 5x - 6 = 0")).toString(),
//   //           "x = -3 | x = -1 | x = 2");
//   // EXPECT_EQ(solve(Expression("x^3 = 0")).toString(),
//   //           "x = 0");
//   // EXPECT_EQ(solve(Expression("x^3 + 1 = 0")).toString(),
//   //           "x = -1");
//   // EXPECT_EQ(solve(Expression("x^3 - 1 = 0")).toString(),
//   //           "x = 1");
//   // EXPECT_EQ(solve(Expression("x^3 + 2x^2 + x = 0")).toString(),
//   //           "x = -1 | x = 0");
//   // EXPECT_EQ(solve(Expression("-x^3 + 5x^2 - 8x + 4 = 0")).toString(),
//   //           "x = 1 | x = 2");
//   // EXPECT_EQ(solve(Expression("-2x^3 + 4x^2 + 4x - 8 = 0")).toString(),
//   //           "x = -1 | x = 1 | x = 2");
//   // EXPECT_EQ(solve(Expression("2x^3 - 3x^2 - 11x + 6 = 0")).toString(),
//   //           "x = -2 | x = 1/2 | x = 3");
//   // EXPECT_EQ(solve(Expression("3x^3 - 3x^2 - 12x - 8 = 0")).toString(),
//   //           "1/9 (3 + (1485 - 162 sqrt(23))^(1/3) + 3 (55 + 6 sqrt(23))^(1/3))");

//   EXPECT_EQ(solve(Expression("x < 1")).toString(),
//             "x < 1");
//   EXPECT_EQ(solve(Expression("x < -10")).toString(),
//             "x < -10");
//   EXPECT_EQ(solve(Expression("x! = 0")).toString(),
//             "x! = 0");

//   // TODO: implement quadric inequalities
//   EXPECT_EQ(solve(Expression("x^2 + 2 x - 1 < 0")).toString(),
//             "x^2 + 2 x - 1 < 0");

//   EXPECT_EQ(solve(Expression("15x^2 + sin(25)x - 10% = Ey")).toString(),
//             "x^2 + (sin(25) x)/15 - (E y)/15 - 1/150 = 0");
//   EXPECT_EQ(solve(Expression("x + x_1 + x_2 + y + y_1 = 0")).toString(),
//             "x + x_1 + x_2 + y + y_1 = 0");
//   EXPECT_EQ(solve(Expression("-x^a = 0")).toString(),
//             "x^a = 0");
//   EXPECT_EQ(solve(Expression("sin(x) = 0")).toString(),
//             "sin(x) = 0");
//   EXPECT_EQ(solve(Expression("x^2 + y = 0")).toString(),
//             "x^2 + y = 0");
//   EXPECT_EQ(solve(Expression("x y = 0")).toString(),
//             "x y = 0");
//   EXPECT_EQ(solve(Expression("2 x^a = 0")).toString(),
//             "x^a = 0");
//   EXPECT_EQ(solve(Expression("x^b a = 0")).toString(),
//             "a x^b = 0");
//   EXPECT_EQ(solve(Expression("x/y = 0")).toString(),
//             "x = 0");
//   EXPECT_EQ(solve(Expression("x^2 - 2*sin(2) = 0")).toString(),
//             "x = -sqrt(8 sin(2))/2 | x = sqrt(8 sin(2))/2");
//   EXPECT_EQ(solve(Expression("x = x sqrt(x)")).toString(),
//             "x^(3/2) - x = 0");
//   EXPECT_EQ(solve(Expression("x = 3^x")).toString(),
//             "3^x - x = 0");

//   EXPECT_EQ(solve(Expression("E = Ey")).toString(),
//             "y = 1");
//   EXPECT_EQ(solve(Expression("sin(4) = sin(4) y")).toString(),
//             "y = 1");
//   EXPECT_EQ(solve(Expression("E >= Ey")).toString(),
//             "y <= 1");
//   EXPECT_EQ(solve(Expression("sin(4) >= sin(4) y")).toString(),
//             "y >= 1");
//   EXPECT_EQ(solve(Expression("x >= x sqrt(x)")).toString(),
//             "x^(3/2) - x <= 0");
//   EXPECT_EQ(solve(Expression("x >= x^(1/100)")).toString(),
//             "x - root(x, 100) >= 0");
// }

// TEST(SolveTests, solveApproximateTest) {
//   const Variable x("x");

//   {
//     Expression expr = pow(x + 1, 6);
//     EXPECT_EQ(expr.toString(), "x^6 + 6 x^5 + 15 x^4 + 20 x^3 + 15 x^2 + 6 x + 1");

//     expr = solve(expr);
//     EXPECT_EQ(expr.toString(), "x^6 + 6 x^5 + 15 x^4 + 20 x^3 + 15 x^2 + 6 x + 1");

//     expr = approximate(expr, 2);
//     EXPECT_EQ(expr.toString(), "x^6 + 6 x^5 + 15 x^4 + 20 x^3 + 15 x^2 + 6 x + 1");
//   }

//   {
//     Expression expr = pow(x + 1, 7);
//     EXPECT_EQ(expr.toString(), "x^7 + 7 x^6 + 21 x^5 + 35 x^4 + 35 x^3 + 21 x^2 + 7 x + 1");

//     expr = solve(expr);
//     EXPECT_EQ(expr.toString(), "x^7 + 7 x^6 + 21 x^5 + 35 x^4 + 35 x^3 + 21 x^2 + 7 x + 1");

//     expr = approximate(expr, 2);
//     EXPECT_EQ(expr.toString(), "x^7 + 7 x^6 + 21 x^5 + 35 x^4 + 35 x^3 + 21 x^2 + 7 x + 1");
//   }
// }
