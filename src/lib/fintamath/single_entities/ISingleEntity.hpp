#ifndef ISINGLEENTITY_HPP
#define ISINGLEENTITY_HPP

#include <string>

class ISingleEntity {
protected:
  ISingleEntity() = default;
  ISingleEntity(ISingleEntity &&rhs) = default;
  ISingleEntity(const ISingleEntity &rhs) = default;
  ISingleEntity &operator=(ISingleEntity &&rhs) = default;
  ISingleEntity &operator=(const ISingleEntity &rhs) = default;

public:
  virtual ~ISingleEntity() = 0;

  virtual std::string getTypeName() const = 0;
  virtual std::string toString() const = 0;
};

inline ISingleEntity::~ISingleEntity() = default;

#endif // ISINGLEENTITY_HPP
