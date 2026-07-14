#pragma once

class IOService {
 public:
  virtual ~IOService() = default;

  /// @brief A function describing the initialization routing ran before the
  /// first HW loop
  virtual void setup() = 0;

  /// @brief A function describing workload of this service on each HW loop
  virtual void hook() = 0;
};
