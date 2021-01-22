// Copyright (c) 2021 Marco Wang <m.aesophor@gmail.com>
#ifndef EXCALIBAR_CLOCK_H_
#define EXCALIBAR_CLOCK_H_

#include "module.h"

#include <ctime>

namespace excalibar {

class Clock : public Module {
 public:
  Clock(Display* dpy,
        Window root_window,
        Window bar_window,
        GC gc,
        Properties* prop,
        int x,
        int y);
  virtual ~Clock() = default;

  virtual void Update() override;

 private:
  ::std::time_t t_;
  ::std::tm lt_;
};

}  // namespace excalibar

#endif  // EXCALIBAR_CLOCK_H_
