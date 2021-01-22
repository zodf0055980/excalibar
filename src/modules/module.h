// Copyright (c) 2021 Marco Wang <m.aesophor@gmail.com>
#ifndef EXCALIBAR_MODULE_H_
#define EXCALIBAR_MODULE_H_

extern "C" {
#include <X11/Xlib.h>
}
#include <string>

#include "properties.h"

namespace excalibar {

class Module {
 public:
  virtual ~Module() = default;

  virtual void Update() = 0;

  virtual void Draw() const {
    XDrawString(dpy_, bar_window_, gc_, x_, y_, text_.c_str(), text_.size());
  }

 protected:
  Module(Display* dpy,
         Window root_window,
         Window bar_window,
         GC gc,
         Properties* prop,
         int x,
         int y)
      : dpy_(dpy),
        root_window_(root_window),
        bar_window_(bar_window),
        gc_(gc),
        prop_(prop),
        x_(x),
        y_(y),
        text_() {}

  Display* dpy_;
  Window root_window_;
  Window bar_window_;
  GC gc_;
  Properties* prop_;

  int x_;
  int y_;
  ::std::string text_;
};

}  // namespace excalibar

#endif  // EXCALIBAR_MODULE_H_
