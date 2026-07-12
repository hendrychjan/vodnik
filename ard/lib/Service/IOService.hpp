#pragma once

class IOService {
 public:
  /// @brief A function describing workload of this service on each HW loop
  virtual void hook();
};
