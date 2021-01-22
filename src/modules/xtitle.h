// Copyright (c) 2021 Marco Wang <m.aesophor@gmail.com>
#ifndef EXCALIBAR_XTITLE_H_
#define EXCALIBAR_XTITLE_H_

#include "module.h"

namespace excalibar {

class XTitle : public Module {
 public:
  XTitle(Display* dpy,
         Window root_window,
         Window bar_window,
         GC gc,
         Properties* prop,
         int x,
         int y);
  virtual ~XTitle() = default;

  virtual void Update() override;
};

}  // namespace excalibar

#endif  // EXCALIBAR_XTITLE_H_
