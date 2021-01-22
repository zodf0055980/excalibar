// Copyright (c) 2021 Marco Wang <m.aesophor@gmail.com>
#ifndef EXCALIBAR_XWORKSPACES_H_
#define EXCALIBAR_XWORKSPACES_H_

#include "module.h"

namespace excalibar {

class XWorkspaces : public Module {
 public:
  XWorkspaces(Display* dpy,
         Window root_window,
         Window bar_window,
         GC gc,
         Properties* prop,
         int x,
         int y);
  virtual ~XWorkspaces() = default;

  virtual void Update() override;
};

}  // namespace excalibar

#endif  // EXCALIBAR_XWORKSPACES_H_
