// Copyright (c) 2021 Marco Wang <m.aesophor@gmail.com>
#include "battery.h"

#include "status_bar.h"

namespace excalibar {

Battery::Battery(Display* dpy,
                 Window root_window,
                 Window bar_window,
                 GC gc,
                 Properties* prop,
                 int x,
                 int y)
      : Module(dpy, root_window, bar_window, gc, prop, x, y) {}


void Battery::Update() {
  text_ = "BAT: 100%";
}

}  // namespace excalibar
