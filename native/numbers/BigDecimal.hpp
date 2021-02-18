#ifndef BIG_DECIMAL_HPP
#define BIG_DECIMAL_HPP

///////////////////////////////////////////////////////////
/// @brief BigDecimal
///
class BigDecimal {
public:
    BigDecimal();
    virtual ~BigDecimal(); // TODO: Is VIRTUAL needed?
    BigDecimal(const BigDecimal &other);
    BigDecimal(BigDecimal &&other);
    BigDecimal &operator=(const BigDecimal &other);
    BigDecimal &operator=(BigDecimal &&other);

private:
    // Members
};

#endif // BIG_DECIMAL_HPP
