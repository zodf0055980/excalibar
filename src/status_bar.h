// Copyright (c) 2021 Marco Wang <m.aesophor@gmail.com>
#ifndef EXCALIBAR_STATUS_BAR_H_
#define EXCALIBAR_STATUS_BAR_H_

extern "C" {
#include <X11/Xlib.h>
}
#include <vector>
#include <string>
#include <memory>
#include <utility>
#include <unordered_map>

#include "properties.h"
#include "modules/module.h"

namespace excalibar {

class StatusBar {
 public:
  static StatusBar* GetInstance();
  virtual ~StatusBar();

  void Run();
  
 private:
  StatusBar(Display* dpy);

  void Update();
  ::std::pair<int, int> GetDisplayResolution() const;
  unsigned long AllocateColor(const ::std::string& color_hex);

  Display* dpy_;
  int screen_;
  int bg_color_;
  int fg_color_;
  XFontStruct* font_;
  Window root_window_;
  Window bar_window_;
  GC gc_;  // graphical context

  ::std::unique_ptr<Properties> prop_;
  ::std::unordered_map<::std::string, unsigned long> colors_;
  ::std::vector<::std::unique_ptr<Module>> modules_;
};

}  // namespace excalibar

#endif  // EXCALIBAR_STATUS_BAR_H_
