// Copyright (c) 2016, GSI and The Polatory Authors.

#pragma once

#include <cassert>

namespace polatory {
namespace common {

template <class T>
class uncertain {
  T value;
  bool certain;

public:
  uncertain()
    : value()
    , certain(false) {
  }

  uncertain(T value)
    : value(value)
    , certain(true) {
  }

  bool is_certain() const {
    return certain;
  }

  T get() const {
    assert(is_certain());
    return value;
  }
};

namespace {

uncertain<bool> operator!(uncertain<bool> a) {
  if (a.is_certain()) return !a.get();
  return uncertain<bool>();
}

uncertain<bool> operator&&(uncertain<bool> a, uncertain<bool> b) {
  if (a.is_certain()) {
    if (b.is_certain()) {
      return a.get() && b.get();
    } else if (a.get() == false) {
      return false;
    }
  } else if (b.is_certain()) {
    if (b.get() == false) {
      return false;
    }
  }
  return uncertain<bool>();
}

uncertain<bool> operator||(uncertain<bool> a, uncertain<bool> b) {
  if (a.is_certain()) {
    if (b.is_certain()) {
      return a.get() || b.get();
    } else if (a.get() == true) {
      return true;
    }
  } else if (b.is_certain()) {
    if (b.get() == true) {
      return true;
    }
  }
  return uncertain<bool>();
}

bool certainly(uncertain<bool> a) {
  return a.is_certain() && a.get() == true;
}

bool certainly_not(uncertain<bool> a) {
  return a.is_certain() && a.get() == false;
}

bool possibly(uncertain<bool> a) {
  return !a.is_certain() || a.get() == true;
}

bool possibly_not(uncertain<bool> a) {
  return !a.is_certain() || a.get() == false;
}

} // namespace

} // namespace common
} // namespace polatory
