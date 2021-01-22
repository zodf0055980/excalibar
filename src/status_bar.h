// Copyright (c) 2021 Marco Wang <m.aesophor@gmail.com>
#ifndef EXCALIBAR_STATUS_BAR_H_
#define EXCALIBAR_STATUS_BAR_H_

extern "C" {
#include <X11/Xlib.h>
}
#include <memory>
#include <utility>

#include "properties.h"

namespace excalibar {

class StatusBar {
 public:
  static StatusBar* GetInstance();
  virtual ~StatusBar();

  void Run();

 private:
  StatusBar(Display* dpy);

  ::std::pair<int, int> GetDisplayResolution() const;

  Display* dpy_;
	int bg_color_;
	int fg_color_;
  Window root_window_;
  Window bar_window_;
	GC gc_;  // graphical context

	::std::unique_ptr<Properties> prop_;
};

}  // namespace excalibar

#endif  // EXCALIBAR_STATUS_BAR_H_
