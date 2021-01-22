// Copyright (c) 2021 Marco Wang <m.aesophor@gmail.com>
extern "C" {
#include <unistd.h>
}
#include <cstring>
#include <iostream>
#include <memory>

#include "status_bar.h"

namespace {

const char* version() {
  return "Excalibar 0.1.0\n"
      "Copyright (C) 2021 Marco Wang <m.aesophor@gmail.com>\n"
      "This is free software, see the source for copying conditions. There is no\n"
      "warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE";
}

}  // namespace

int main(int argc, char* args[]) {
  if (argc > 1 && (!::std::strcmp(args[1], "-v") || !::std::strcmp(args[1], "--version"))) {
    ::std::cout << ::version() << ::std::endl;
    return EXIT_SUCCESS;
  }

  // StatusBar is a singleton class. If XOpenDisplay() fails during
  // StatusBar::GetInstance(), it will return None (in Xlib, 'None'
  // is the universal null resource ID or atom.)
  ::std::unique_ptr<excalibar::StatusBar> bar(excalibar::StatusBar::GetInstance());

  if (!bar) {
    const char* err_msg = "Failed to open display to X server.";
    ::std::cerr << err_msg << ::std::endl;
    return EXIT_FAILURE;
  }

  try {
    bar->Run();  // enter main event loop

  } catch (const ::std::bad_alloc& ex) {
    static_cast<void>(::std::fputs("Out of memory\n", stderr));
    return EXIT_FAILURE;

  } catch (...) {
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
