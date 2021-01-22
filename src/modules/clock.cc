// Copyright (c) 2021 Marco Wang <m.aesophor@gmail.com>
#include "clock.h"

#include <iomanip>
#include <sstream>

namespace excalibar {

Clock::Clock(Display* dpy,
             Window root_window,
             Window bar_window,
             GC gc,
             Properties* prop,
             int x,
             int y)
    : Module(dpy, root_window, bar_window, gc, prop, x, y),
      t_(),
      lt_() {}


void Clock::Update() {
  t_ = ::std::time(nullptr);
  lt_ = *::std::localtime(&t_);

  ::std::ostringstream oss;
  oss << ::std::put_time(&lt_, "%m/%d %H:%M %p");
  text_ = oss.str();
}

}  // namespace excalibar
