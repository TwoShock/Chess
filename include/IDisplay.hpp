#pragma once
#include <string>
namespace chess{
class IDisplay {
 public:
  virtual auto display() const -> std::string = 0;
};
}  // namespace
