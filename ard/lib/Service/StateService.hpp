#pragma once

enum OperationMode {
  Automatic,
  Override,
};

template<typename T>
struct Device {
  const char* label;
  T device;
};

class StateService {
 public:
  OperationMode getMode();
  void setMode(OperationMode mode);

 private:
  OperationMode _mode;
};
