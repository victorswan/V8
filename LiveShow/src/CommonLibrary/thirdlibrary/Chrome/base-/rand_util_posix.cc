// Copyright (c) 2008 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/rand_util.h"

#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#include "base/logging.h"

namespace base {

uint64 RandUInt64() {
  uint64 number;

  int urandom_fd = open("/dev/urandom", O_RDONLY);
  CHECK(urandom_fd >= 0);
  ssize_t bytes_read = read(urandom_fd, &number, sizeof(number));
  CHECK(bytes_read == sizeof(number));
  close(urandom_fd);

  return number;
}

}  // namespace base
