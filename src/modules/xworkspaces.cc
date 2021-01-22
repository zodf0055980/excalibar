// Copyright (c) 2021 Marco Wang <m.aesophor@gmail.com>
#include "xworkspaces.h"

extern "C" {
#include <X11/Xutil.h>
}

namespace excalibar {

XWorkspaces::XWorkspaces(Display* dpy,
               Window root_window,
               Window bar_window,
               GC gc,
               Properties* prop,
               int x,
               int y)
      : Module(dpy, root_window, bar_window, gc, prop, x, y) {}


void XWorkspaces::Update() {
  unsigned long atom_len = 0;
  Atom da;
  unsigned char* prop_ret = nullptr;
  int di;
  unsigned long remain;

  int number_of_desktops = 0;
  if (XGetWindowProperty(dpy_, root_window_, prop_->net[atom::NET_NUMBER_OF_DESKTOPS], 0, sizeof(Atom),
        False, XA_CARDINAL, &da, &di, &atom_len, &remain, &prop_ret) == Success &&
      prop_ret) {
    number_of_desktops = *(reinterpret_cast<unsigned long*>(prop_ret));
  }

  int current_desktop = 0;
  if (XGetWindowProperty(dpy_, root_window_, prop_->net[atom::NET_CURRENT_DESKTOP], 0, sizeof(Atom),
        False, XA_CARDINAL, &da, &di, &atom_len, &remain, &prop_ret) == Success &&
      prop_ret) {
    current_desktop = *(reinterpret_cast<unsigned long*>(prop_ret));
  }

  text_.clear();
  for (int i = 0; i < number_of_desktops; i++) {
    if (i == current_desktop) {
      text_ += " [" + ::std::to_string(i+1) + "] ";
    } else {
      text_ += " " + ::std::to_string(i+1) + " ";
    }
  }
}

}  // namespace excalibar
