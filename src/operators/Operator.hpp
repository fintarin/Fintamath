#ifndef OPERATOR_HPP
#define OPERATOR_HPP

#include <string>

#include "../calculator/NodeType.hpp"
#include "../numbers/Fraction.hpp"

class Operator : public NodeType {
public:
    Operator(const Operator &);
    explicit Operator(const std::string &);
    Operator &operator=(const Operator &);

    bool isEqualSign() const;
    Fraction solve(const Fraction &, const Fraction &) const;

    const std::string getTypeName() const override;
    const std::string toString() const override;

private:
    char oper;
};

namespace isType {
bool isOperator(const std::string &);
}

#endif // OPERATOR_HPP