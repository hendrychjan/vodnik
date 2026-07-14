#pragma once

class IOObject {
 public:
  virtual ~IOObject() = default;

  /// @brief Describes the object initialization that should run before any
  /// other readings/actions are done
  virtual void setup() = 0;
};
