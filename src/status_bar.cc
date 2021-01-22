// Copyright (c) 2021 Marco Wang <m.aesophor@gmail.com>
#include "status_bar.h"

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
      bg_color_(BlackPixel(dpy_, DefaultScreen(dpy_))),
      fg_color_(WhitePixel(dpy_, DefaultScreen(dpy_))),
      root_window_(DefaultRootWindow(dpy_)),
      bar_window_(XCreateSimpleWindow(dpy_, root_window_, 0, 0, GetDisplayResolution().first, 30, 0, bg_color_, bg_color_)),
      //gc_(XCreateGC(dpy_, bar_window_, 0, None)),
      prop_(::std::make_unique<Properties>(dpy_)) {

  // Set _NET_WM_WINDOW_TYPE to _NET_WM_WINDOW_TYPE_DOCK
  XChangeProperty(dpy, bar_window_, prop_->net[atom::NET_WM_WINDOW_TYPE], XA_ATOM, 32,
      PropModeReplace, (unsigned char*)&prop_->net[atom::NET_WM_WINDOW_TYPE_DOCK], 1);

  // We need to receive root_window_'s PropertyNotify event (XPropertyEvent),
  // e.g., when _NET_ACTIVE_DESKTOP has changed, we need to update the bar accordingly.
  XSelectInput(dpy, root_window_, PropertyChangeMask);
  XSelectInput(dpy, bar_window_, StructureNotifyMask | ExposureMask);

  XMapWindow(dpy_, bar_window_);
  gc_ = XCreateGC(dpy_, bar_window_, 0, None);

  // Wait for the MapNotify event
  XEvent event;
  while (true) {
    XNextEvent(dpy_, &event);
    if (event.type == MapNotify) {
      break;
    }
  }
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
        break;
      case PropertyNotify:
        break;
      default:
        break;
    }
  }
}

::std::pair<int, int> StatusBar::GetDisplayResolution() const {
  XWindowAttributes attr;
  XGetWindowAttributes(dpy_, root_window_, &attr);
  return {attr.width, attr.height};
}

}  // namespace excalibar
