// Copyright (c) 2006-2008 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_LOCK_IMPL_H_
#define BASE_LOCK_IMPL_H_

#include "build/build_config.h"

#if defined(OS_WIN)
#include <windows.h>
#elif defined(OS_POSIX)
#include <pthread.h>
#endif

#include "base/basictypes.h"

// This class implements the underlying platform-specific spin-lock mechanism
// used for the Lock class.  Most users should not use LockImpl directly, but
// should instead use Lock.
class LockImpl {
 public:
#if defined(OS_WIN)
  typedef CRITICAL_SECTION OSLockType;
#elif defined(OS_POSIX)
  typedef pthread_mutex_t OSLockType;
#endif

  LockImpl();
  ~LockImpl();

  // If the lock is not held, take it and return true.  If the lock is already
  // held by something else, immediately return false.
  bool Try();

  // Take the lock, blocking until it is available if necessary.
  void Lock();

  // Release the lock.  This must only be called by the lock's holder: after
  // a successful call to Try, or a call to Lock.
  void Unlock();

  // Return the native underlying lock.
  // TODO(awalker): refactor lock and condition variables so that this is
  // unnecessary.
  OSLockType* os_lock() { return &os_lock_; }

 private:
  OSLockType os_lock_;

  DISALLOW_COPY_AND_ASSIGN(LockImpl);
};

class AutoLockImpl {
 public:
  AutoLockImpl(LockImpl* lock_impl)
      : lock_impl_(lock_impl) {
    lock_impl_->Lock();
  }

  ~AutoLockImpl() {
    lock_impl_->Unlock();
  }

 private:
  DISALLOW_EVIL_CONSTRUCTORS(AutoLockImpl);

  LockImpl* lock_impl_;
};

#endif  // BASE_LOCK_IMPL_H_

