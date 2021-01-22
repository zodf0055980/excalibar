// Copyright (c) 2021 Marco Wang <m.aesophor@gmail.com>
#ifndef EXCALIBAR_MODULE_H_
#define EXCALIBAR_MODULE_H_

namespace excalibar {

class Module {
 public:
  virtual ~Module() = default;

 protected:
  Module() = default;
  virtual void update() = 0;
};

}  // namespace excalibar

#endif  // EXCALIBAR_MODULE_H_
