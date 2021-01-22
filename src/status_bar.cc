// Copyright (c) 2021 Marco Wang <m.aesophor@gmail.com>
#include "status_bar.h"

extern "C" {
#include <X11/Xutil.h>
}
#include <iostream>

#include "modules/clock.h"
#include "modules/battery.h"
#include "modules/xtitle.h"
#include "modules/xworkspaces.h"

namespace excalibar {

StatusBar* StatusBar::GetInstance() {
  Display* dpy = XOpenDisplay(None);
  if (!dpy) {
    return nullptr;
  }

  static StatusBar instance(dpy);
  return &instance;
}

StatusBar::StatusBar(Display* dpy)
    : dpy_(dpy),
      screen_(DefaultScreen(dpy_)),
      bg_color_(AllocateColor("#292d3e")),
      fg_color_(WhitePixel(dpy_, screen_)),
      font_(XLoadQueryFont(dpy_, "-*-fixed-*-*-*-*-12-*-*-*-*-*-*-*")),
      root_window_(DefaultRootWindow(dpy_)),
      bar_window_(XCreateSimpleWindow(dpy_, root_window_, 0, GetDisplayResolution().second - 30, GetDisplayResolution().first, 30, 0, bg_color_, bg_color_)),
      gc_(XCreateGC(dpy_, bar_window_, 0, None)),
      prop_(::std::make_unique<Properties>(dpy_)),
      colors_(),
      modules_() {

  // Set _NET_WM_WINDOW_TYPE to _NET_WM_WINDOW_TYPE_DOCK
  XChangeProperty(dpy, bar_window_, prop_->net[atom::NET_WM_WINDOW_TYPE], XA_ATOM, 32,
      PropModeReplace, (unsigned char*)&prop_->net[atom::NET_WM_WINDOW_TYPE_DOCK], 1);

  // We need to receive root_window_'s PropertyNotify event (XPropertyEvent),
  // e.g., when _NET_ACTIVE_DESKTOP has changed, we need to update the bar accordingly.
  XSelectInput(dpy, root_window_, PropertyChangeMask);
  XSelectInput(dpy, bar_window_, StructureNotifyMask | ExposureMask);

  XMapWindow(dpy_, bar_window_);

  // Wait for the MapNotify event
  XEvent event;
  while (true) {
    XNextEvent(dpy_, &event);
    if (event.type == MapNotify) {
      break;
    }
  }

  XSetForeground(dpy_, gc_, fg_color_);

#define ADD_MODULE(module_class_name, x, y) \
  modules_.push_back(::std::make_unique<module_class_name>( \
        dpy_, root_window_, bar_window_, gc_, prop_.get(), x, y));

  ADD_MODULE(Clock, GetDisplayResolution().first - 100, 20);
  ADD_MODULE(Battery, GetDisplayResolution().first - 175, 20);
  ADD_MODULE(XTitle, 300, 20);
  ADD_MODULE(XWorkspaces, 15, 20);

  XFlush(dpy_);
}

StatusBar::~StatusBar() {
  XCloseDisplay(dpy_);
}

void StatusBar::Run() {
  XEvent event;

  while (true) {
    // Retrieve and dispatch next X event.
    XNextEvent(dpy_, &event);

    switch (event.type) {
      case Expose:
        ::std::cout << "received expose" << ::std::endl;
        Update();
        break;
      case PropertyNotify:
        ::std::cout << "received property notify" << ::std::endl;
        Update();
        break;
      default:
        break;
    }
  }
}

void StatusBar::Update() {
  XClearWindow(dpy_, bar_window_);
  for (auto& m : modules_) {
    m->Update();
    m->Draw();
  }
}


::std::pair<int, int> StatusBar::GetDisplayResolution() const {
  XWindowAttributes attr;
  XGetWindowAttributes(dpy_, root_window_, &attr);
  return {attr.width, attr.height};
}

unsigned long StatusBar::AllocateColor(const ::std::string& color_hex) {
  auto it = colors_.find(color_hex);
  if (it != colors_.end()) {
    return it->second;
  }

  Colormap cmap = DefaultColormap(dpy_, screen_);
  XColor col;

  if (!XAllocNamedColor(dpy_, cmap, color_hex.c_str(), &col, &col)) {
    ::std::cerr << "Unable to use color: " << color_hex << ". Fallback to white" << ::std::endl;
    return XWhitePixel(dpy_, screen_);
  }
  colors_[color_hex] = col.pixel;
  return col.pixel;
}

}  // namespace excalibar
