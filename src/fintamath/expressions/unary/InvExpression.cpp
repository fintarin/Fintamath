// #include "fintamath/expressions/unary/InvExpression.hpp"

// #include "fintamath/expressions/ExpressionUtils.hpp"
// #include "fintamath/expressions/IInvertableExpression.hpp"
// #include "fintamath/functions/arithmetic/Add.hpp"
// #include "fintamath/functions/arithmetic/Div.hpp"
// #include "fintamath/functions/arithmetic/Inv.hpp"
// #include "fintamath/numbers/NumberConstants.hpp"

// namespace fintamath {

// const Inv INV;

// InvExpression::InvExpression(const ArgumentPtr &child) : IUnaryExpressionCRTP(INV, child) {
// }

// ArgumentPtr InvExpression::preSimplify() const {
//   auto simpl = IUnaryExpression::preSimplify();

//   auto simplExpr = cast<InvExpression>(simpl);
//   if (!simplExpr) {
//     return simpl;
//   }

//   // TODO: change when inf will be implemented
//   if (const auto &number = cast<INumber>(simplExpr->child); number && *number == ZERO) {
//     auto error = Integer(1) / Integer(0);
//   }

//   if (const auto expr = cast<InvExpression>(simplExpr->child)) {
//     return expr->child;
//   }

//   return simpl;
// }

// ArgumentPtr InvExpression::postSimplify() const {
//   auto simpl = IUnaryExpression::postSimplify();

//   auto simplExpr = cast<InvExpression>(simpl);
//   if (!simplExpr) {
//     return simpl;
//   }

//   // TODO: change when inf will be implemented
//   if (const auto &number = cast<INumber>(simplExpr->child); number && *number == ZERO) {
//     auto error = Integer(1) / Integer(0);
//   }

//   if (auto expr = cast<IInvertableExpression>(simplExpr->child)) {
//     return expr->invert();
//   }

//   return simpl;
// }

// string InvExpression::toString() const {
//   string childToStr = getChildren()[0]->toString();

//   if (const auto &sumChildExpr = cast<IExpression>(getChildren()[0]);
//       sumChildExpr && is<Add>(sumChildExpr->getFunction())) {

//     childToStr = putInBrackets(childToStr);
//   }

//   return ONE.toString() + Div().toString() + childToStr;
// }

// }
