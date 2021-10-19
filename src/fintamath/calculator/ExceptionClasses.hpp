#ifndef EXCEPTIONCLASSES_HPP
#define EXCEPTIONCLASSES_HPP

#include <string>

class IncorrectInput {
public:
  explicit IncorrectInput(const std::string &getError) {
    this->error = getError;
    this->error += " : Incorrect input";
  }

  std::string getError() const {
    return this->error;
  }

private:
  std::string error;
};

class DividedByZero {
public:
  explicit DividedByZero(const std::string &getError) {
    this->error = getError;
    this->error += " : Divided by zero";
  }

  std::string getError() const {
    return this->error;
  }

private:
  std::string error;
};

class ZeroPowZero {
public:
  explicit ZeroPowZero(const std::string &getError) {
    this->error = getError;
    this->error += " : Zero to the power of zero";
  }

  std::string getError() const {
    return this->error;
  }

private:
  std::string error;
};

class OutOfRange {
public:
  explicit OutOfRange(const std::string &getError) {
    this->error = getError;
    this->error += " : Out of range";
  }

  std::string getError() const {
    return this->error;
  }

private:
  std::string error;
};

class Undefined {
public:
  explicit Undefined(const std::string &getError) {
    this->error = getError;
    this->error += " : Undefined";
  }

  std::string getError() const {
    return this->error;
  }

private:
  std::string error;
};

#endif // EXCEPTIONCLASSES_HPP