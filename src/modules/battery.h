// Copyright (c) 2021 Marco Wang <m.aesophor@gmail.com>
#ifndef EXCALIBAR_BATTERY_H_
#define EXCALIBAR_BATTERY_H_

#include "module.h"

namespace excalibar {

class Battery : public Module {
 public:
  Battery(Display* dpy,
          Window root_window,
          Window bar_window,
          GC gc,
          Properties* prop,
          int x,
          int y);
  virtual ~Battery() = default;

  virtual void Update() override;
};

}  // namespace excalibar

#endif  // EXCALIBAR_BATTERY_H_
