// Copyright (c) 2021 Marco Wang <m.aesophor@gmail.com>
#include "battery.h"

extern "C" {
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
}
#include <algorithm>
#include <iostream>
#include <vector>

namespace excalibar {

Battery::Battery(Display* dpy,
                 Window root_window,
                 Window bar_window,
                 GC gc,
                 Properties* prop,
                 int x,
                 int y)
    : Module(dpy, root_window, bar_window, gc, prop, x, y) {}


void Battery::Update() {
  text_.clear();
  char buf[256];

  int status;
  pid_t pid;
  int p[2] = { 0 };
  pipe(p);

  switch (pid = fork()) {
    case -1:
      ::std::perror("failed to fork child process");
      break;

    case 0: {
      dup2(p[1], fileno(stdout));
      close(p[0]);
      close(p[1]);

      ::std::vector<::std::string> tokens = {"pmset", "-g", "batt"};
      ::std::vector<char*> argv(tokens.size() + 1, nullptr);

      ::std::transform(tokens.begin(), tokens.end(), argv.begin(),
          [](auto& s) { return const_cast<char*>(s.data()); });

      execvp(argv.data()[0], argv.data());
      ::std::perror("failed to exec");
      break;
    }

    default:
      wait(&status);
      read(p[0], buf, sizeof(buf));

      for (int i = 0; i < (int) sizeof(buf); i++) {
        if (buf[i] == '%') {
          text_.push_back(buf[i - 3]);
          text_.push_back(buf[i - 2]);
          text_.push_back(buf[i - 1]);
          text_.push_back(buf[i]);
          break;
        }
      }
      break;
  }

  close(p[0]);
  close(p[1]);
}

}  // namespace excalibar
