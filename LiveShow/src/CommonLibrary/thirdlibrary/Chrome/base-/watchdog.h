// Copyright (c) 2006-2008 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// The Watchdog class creates a second thread that can Alarm if a specific
// duration of time passes without proper attention.  The duration of time is
// specified at construction time.  The Watchdog may be used many times by
// simply calling Arm() (to start timing) and Disarm() (to reset the timer).
// The Watchdog is typically used under a debugger, where the stack traces on
// other threads can be examined if/when the Watchdog alarms.

// Some watchdogs will be enabled or disabled via command line switches. To
// facilitate such code, an "enabled" argument for the constuctor can be used
// to permanently disable the watchdog.  Disabled watchdogs don't even spawn
// a second thread, and their methods call (Arm() and Disarm()) return very
// quickly.

#ifndef BASE_WATCHDOG_H__
#define BASE_WATCHDOG_H__

#include <string>

#include "base/condition_variable.h"
#include "base/lock.h"
#include "base/time.h"

class Watchdog {
 public:
  // TODO(JAR)change default arg to required arg after all users have migrated.
  // Constructor specifies how long the Watchdog will wait before alarming.
  Watchdog(const TimeDelta& duration,
           const std::wstring& thread_watched_name,
           bool enabled = true);
  virtual ~Watchdog();

  // Start timing, and alarm when time expires (unless we're disarm()ed.)
  void Arm();  // Arm  starting now.
  void ArmSomeTimeDeltaAgo(const TimeDelta& time_delta);
  void ArmAtStartTime(const TimeTicks start_time);

  // Reset time, and do not set off the alarm.
  void Disarm();

  // Alarm is called if the time expires after an Arm() without someone calling
  // Disarm().  This method can be overridden to create testable classes.
  virtual void Alarm() {
    DLOG(INFO) << "Watchdog alarmed for " << thread_watched_name_;
  }

 private:
  enum State {ARMED, DISARMED, SHUTDOWN };

  // Windows thread start callback
  static DWORD WINAPI ThreadStart(void* pThis);

  // Loop and test function for our watchdog thread.
  unsigned Run();
  void Watchdog::SetThreadName() const;

  Lock lock_;  // Mutex for state_.
  ConditionVariable condition_variable_;
  State state_;
  const TimeDelta duration_;  // How long after start_time_ do we alarm?
  const std::wstring thread_watched_name_;
  HANDLE handle_;  // Handle for watchdog thread.
  DWORD thread_id_;  // Also for watchdog thread.

  TimeTicks start_time_;  // Start of epoch, and alarm after duration_.

  // When the debugger breaks (when we alarm), all the other alarms that are
  // armed will expire (also alarm).  To diminish this effect, we track any
  // delay due to debugger breaks, and we *try* to adjust the effective start
  // time of other alarms to step past the debugging break.
  // Without this safety net, any alarm will typically trigger a host of follow
  // on alarms from callers that specify old times.
  static Lock static_lock_;  // Lock for access of static data...
  // When did we last alarm and get stuck (for a while) in a debugger?
  static TimeTicks last_debugged_alarm_time_;
  // How long did we sit on a break in the debugger?
  static TimeDelta last_debugged_alarm_delay_;


  DISALLOW_EVIL_CONSTRUCTORS(Watchdog);
};

#endif  // BASE_WATCHDOG_H__

