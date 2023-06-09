// Copyright (c) 2006-2008 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_COMMON_DEBUG_FLAGS_H__
#define CHROME_COMMON_DEBUG_FLAGS_H__

#include <string>

class DebugFlags {
 public:
  enum ChildProcessType {
    RENDERER,
    PLUGIN,
    UNKNOWN
  };

  // Updates the command line arguments with debug-related flags. If debug flags
  // have been used with this process, they will be filtered and added to
  // command_line as needed. is_in_sandbox must be true if the child process will
  // be in a sandbox.
  // Returns true if the caller should "help" the child process by calling the JIT
  // debugger on it. It may only happen if is_in_sandbox is true.
  static bool ProcessDebugFlags(std::wstring* command_line,
                                ChildProcessType type,
                                bool is_in_sandbox);
};

#endif  // CHROME_COMMON_DEBUG_FLAGS_H__

