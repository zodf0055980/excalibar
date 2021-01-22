// Copyright (c) 2021 Marco Wang <m.aesophor@gmail.com>
#include "xtitle.h"

extern "C" {
#include <X11/Xutil.h>
}

#include <iostream>

namespace excalibar {

XTitle::XTitle(Display* dpy,
               Window root_window,
               Window bar_window,
               GC gc,
               Properties* prop,
               int x,
               int y)
      : Module(dpy, root_window, bar_window, gc, prop, x, y) {}


void XTitle::Update() {
  unsigned long atom_len = 0;
  Atom da;
  unsigned char* prop_ret = nullptr;
  int di;
  unsigned long remain;

  if (XGetWindowProperty(dpy_, root_window_, prop_->net[atom::NET_ACTIVE_WINDOW], 0, sizeof(Atom),
        False, XA_WINDOW, &da, &di, &atom_len, &remain, &prop_ret) == Success &&
      prop_ret) {
    Window* active_window = reinterpret_cast<Window*>(prop_ret);
    ::std::cout << "_NET_ACTIVE_WINDOW: " << *active_window << ::std::endl;

    XTextProperty name;
    if (!XGetTextProperty(dpy_, *active_window, &name, prop_->net[atom::NET_WM_NAME]) || !name.nitems) {
      text_ = "Unknown";
      return;
    }

    text_ = reinterpret_cast<char*>(name.value);
    XFree(name.value);
    ::std::cout << "_NET_ACTIVE_WINDOW._NET_WM_NAME: " << text_ << ::std::endl;
  }
}

}  // namespace excalibar
