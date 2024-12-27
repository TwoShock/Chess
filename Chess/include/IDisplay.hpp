#pragma once
#include <string>
namespace {
class IDisplay {
 public:
  virtual auto display() const -> std::string = 0;
};
}  // namespace
