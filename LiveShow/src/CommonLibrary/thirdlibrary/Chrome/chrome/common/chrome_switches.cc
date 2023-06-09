// Copyright (c) 2006-2008 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/common/chrome_switches.h"

#include "base/base_switches.h"

namespace switches {

// Can't find the switch you are looking for? try looking in
// base/base_switches.cc instead.

// Suppresses hang monitor dialogs in renderer processes.
const wchar_t kDisableHangMonitor[]            = L"disable-hang-monitor";

// Completely disables UMA metrics system.
const wchar_t kDisableMetrics[]                = L"disable-metrics";

// Enables the recording of metrics reports but disables reporting.
// In contrast to kDisableMetrics, this executes all the code that a normal
// client would use for reporting, except the report is dropped rather than sent
// to the server. This is useful for finding issues in the metrics code during
// UI and performance tests.
const wchar_t kMetricsRecordingOnly[]       = L"metrics-recording-only";

// Causes the browser process to throw an assertion on startup.
const wchar_t kBrowserAssertTest[]             = L"assert-test";

// Causes the renderer process to throw an assertion on launch.
const wchar_t kRendererAssertTest[]            = L"renderer-assert-test";

// Causes the browser process to crash on startup.
const wchar_t kBrowserCrashTest[]              = L"crash-test";

// Causes the renderer process to crash on launch.
const wchar_t kRendererCrashTest[]             = L"renderer-crash-test";

// Causes the renderer process to display a dialog on launch.
const wchar_t kRendererStartupDialog[]         = L"renderer-startup-dialog";

// Causes the plugin process to display a dialog on launch.
const wchar_t kPluginStartupDialog[]           = L"plugin-startup-dialog";

// Causes the test shell process to display a dialog on launch.
const wchar_t kTestShellStartupDialog[]        = L"testshell-startup-dialog";

// Specifies a command that should be used to launch the plugin process.  Useful
// for running the plugin process through purify or quantify.  Ex:
//   --plugin-launcher="path\to\purify /Run=yes"
const wchar_t kPluginLauncher[]                = L"plugin-launcher";

// The value of this switch tells the child process which
// IPC channel the browser expects to use to communicate with it.
const wchar_t kProcessChannelID[]              = L"channel";

// The value of this switch tells the app to listen for and broadcast
// testing-related messages on IPC channel with the given ID.
const wchar_t kTestingChannelID[]              = L"testing-channel";

// The value of this switch specifies which page will be displayed
// in newly-opened tabs.  We need this for testing purposes so
// that the UI tests don't depend on what comes up for http://google.com.
const wchar_t kHomePage[]                      = L"homepage";

// When this switch is present, the browser will throw up a dialog box
// asking the user to start a renderer process independently rather
// than launching the renderer itself.  (This is useful for debugging.)
const wchar_t kBrowserStartRenderersManually[] = L"start-renderers-manually";

// Causes the process to run as renderer instead of as browser.
const wchar_t kRendererProcess[]               = L"renderer";

// Path to the exe to run for the renderer subprocess
const wchar_t kRendererPath[]                  = L"renderer-path";

// Causes the process to run as plugin host
const wchar_t kPluginProcess[]                 = L"plugin";

// Runs the renderer and plugins in the same process as the browser
const wchar_t kSingleProcess[]                 = L"single-process";

// Runs each set of script-connected tabs (i.e., a BrowsingInstance) in its own
// renderer process.  We default to using a renderer process for each
// site instance (i.e., group of pages from the same registered domain with
// script connections to each other).
const wchar_t kProcessPerTab[] = L"process-per-tab";

// Runs a single process for each site (i.e., group of pages from the same
// registered domain) the user visits.  We default to using a renderer process
// for each site instance (i.e., group of pages from the same registered
// domain with script connections to each other).
const wchar_t kProcessPerSite[] = L"process-per-site";

// Runs plugins inside the renderer process
const wchar_t kInProcessPlugins[]              = L"in-process-plugins";

// Runs the renderer outside the sandbox.
const wchar_t kNoSandbox[]                     = L"no-sandbox";

// Runs the plugin processes inside the sandbox.
const wchar_t kSafePlugins[]                   = L"safe-plugins";

// Excludes these plugins from the plugin sandbox.
// This is a comma separated list of plugin dlls name and activex clsid.
const wchar_t kTrustedPlugins[]                = L"trusted-plugins";

// Runs the security test for the sandbox.
const wchar_t kTestSandbox[]                   = L"test-sandbox";

// Specifies the user data directory, which is where the browser will look
// for all of its state.
const wchar_t kUserDataDir[]                   = L"user-data-dir";

// Specifies that the associated value should be launched in "application" mode.
const wchar_t kApp[]                           = L"app";

// Specifies the file that should be uploaded to the provided application. This
// switch is expected to be used with --app option.
const wchar_t kAppUploadFile[]                 = L"upload-file";

// Specifies if the dom_automation_controller_ needs to be bound in the
// renderer. This binding happens on per-frame basis and hence can potentially
// be a performance bottleneck. One should only enable it when automating
// dom based tests.
const wchar_t kDomAutomationController[]       = L"dom-automation";

// Tells the plugin process the path of the plugin to load
const wchar_t kPluginPath[]                    = L"plugin-path";

// A string used to override the default user agent with a custom one.
const wchar_t kUserAgent[]                     = L"user-agent";

// Specifies the flags passed to JS engine
const wchar_t kJavaScriptFlags[]               = L"js-flags";

// The GeoID we should use.  This is normally obtained from the operating system
// during first run and cached in the preferences afterwards.  This is a numeric
// value; see http://msdn.microsoft.com/en-us/library/ms776390.aspx .
const wchar_t kGeoID[]                         = L"geoid";

// The language file that we want to try to open.  Of the form
// language[-country] where language is the 2 letter code from ISO-639.
const wchar_t kLang[]                          = L"lang";

// Will add kDebugOnStart to every child processes. If a value is passed, it
// will be used as a filter to determine if the child process should have the
// kDebugOnStart flag passed on or not.
const wchar_t kDebugChildren[]                 = L"debug-children";

// Will add kWaitForDebugger to every child processes. If a value is passed, it
// will be used as a filter to determine if the child process should have the
// kWaitForDebugger flag passed on or not.
const wchar_t kWaitForDebuggerChildren[]       = L"wait-for-debugger-children";

// Will filter log messages to show only the messages that are prefixed
// with the specified value
const wchar_t kLogFilterPrefix[]               = L"log-filter-prefix";

// Force logging to be enabled.  Logging is disabled by default in release
// builds.
const wchar_t kEnableLogging[]                 = L"enable-logging";

// Force logging to be disabled.  Logging is enabled by default in debug
// builds.
const wchar_t kDisableLogging[]                = L"disable-logging";

// Sets the minimum log level. Valid values are from 0 to 3:
// INFO = 0, WARNING = 1, LOG_ERROR = 2, LOG_FATAL = 3.
const wchar_t kLoggingLevel[]                  = L"log-level";

// Dump any accumualted histograms to the log when browser terminates (requires
// logging to be enabled to really do anything).  Used by developers and test
// scripts.
const wchar_t kDumpHistogramsOnExit[]          = L"dump-histograms-on-exit";

// enable remote debug / automation shell on the specified port
const wchar_t kRemoteShellPort[]               = L"remote-shell-port";

// Runs un-installation steps that were done by chrome first-run.
const wchar_t kUninstall[]                     = L"uninstall";

// Number of entries to show in the omnibox popup.
const wchar_t kOmniBoxPopupCount[]             = L"omnibox-popup-count";

// The value of this switch tells the app to listen for and broadcast
// automation-related messages on IPC channel with the given ID.
const wchar_t kAutomationClientChannelID[]        = L"automation-channel";

// Indicates the last session should be restored on startup. This overrides
// the preferences value and is primarily intended for testing.
const wchar_t kRestoreLastSession[] = L"restore-last-session";

// Chrome supports a playback and record mode.  Record mode saves *everything*
// to the cache.  Playback mode reads data exclusively from the cache.  This
// allows us to record a session into the cache and then replay it at will.
const wchar_t kRecordMode[] = L"record-mode";
const wchar_t kPlaybackMode[] = L"playback-mode";

// Don't record/playback events when using record & playback.
const wchar_t kNoEvents[] = L"no-events";

// Make Windows happy by allowing it to show "Enable access to this program"
// checkbox in Add/Remove Programs->Set Program Access and Defaults. This
// only shows an error box because the only way to hide Chrome is by
// uninstalling it.
const wchar_t kHideIcons[] = L"hide-icons";

const wchar_t kShowIcons[] = L"show-icons";

// Make Chrome default browser
const wchar_t kMakeDefaultBrowser[] = L"make-default-browser";

// Use a specified proxy server, overrides system settings. This switch only
// affects HTTP and HTTPS requests.
const wchar_t kProxyServer[] = L"proxy-server";

// Chrome will support prefetching of DNS information.  Until this becomes
// the default, we'll provide a command line switch.
extern const wchar_t kDnsLogDetails[] = L"dns-log-details";
extern const wchar_t kDnsPrefetchDisable[] = L"dns-prefetch-disable";

// Enables support to debug printing subsystem.
const wchar_t kDebugPrint[] = L"debug-print";

// Allow initialization of all activex controls. This is only to help website
// developers test their controls to see if they are compatible in Chrome.
// Note there's a duplicate value in activex_shared.cc (to avoid
// dependency on chrome module). Please change both locations at the same time.
const wchar_t kAllowAllActiveX[] = L"allow-all-activex";

// Browser flag to disable the web inspector for all renderers.
const wchar_t kDisableDevTools[] = L"disable-dev-tools";

// Enable web inspector for all windows, even if they're part of the browser.
// Allows us to use our dev tools to debug browser windows itself.
const wchar_t kAlwaysEnableDevTools[] = L"always-enable-dev-tools";

// Used to set the value of SessionRestore::num_tabs_to_load_. See
// session_restore.h for details.
const wchar_t kTabCountToLoadOnSessionRestore[] =
    L"tab-count-to-load-on-session-restore";

// Enable dynamic loading of the Memory Profiler DLL, which will trace
// all memory allocations during the run.
const wchar_t kMemoryProfiling[] = L"memory-profile";

// Configure Chrome's memory model.
// Does chrome really need multiple memory models?  No.  But we get a lot
// of concerns from individuals about how the changes work on *their*
// system, and we need to be able to experiment with a few choices.
const wchar_t kMemoryModel[] = L"memory-model";

// By default, cookies are not allowed on file://. They are needed in for
// testing, for example page cycler and layout tests.  See bug 1157243.
const wchar_t kEnableFileCookies[] = L"enable-file-cookies";

// Start the browser maximized, regardless of any previous settings.
const wchar_t kStartMaximized[] = L"start-maximized";

// Spawn threads to watch for excessive delays in specified message loops.
// User should set breakpoints on Alarm() to examine problematic thread.
// Usage:   -enable-watchdog=[ui][io]
// Order of the listed sub-arguments does not matter.
const wchar_t kEnableWatchdog[] = L"enable-watchdog";

// Display the First Run experience when the browser is started, regardless of
// whether or not it's actually the first run.
const wchar_t kFirstRun[] = L"first-run";

// Enable histograming of tasks served by MessageLoop. See about:histograms/Loop
// for results, which show frequency of messages on each thread, including APC
// count, object signalling count, etc.
const wchar_t kMessageLoopHistogrammer[] = L"message-loop-histogrammer";

// Perform importing from another browser. The value associated with this
// setting encodes the target browser and what items to import.
const wchar_t kImport[] = L"import";

// Change the DCHECKS to dump memory and continue instead of crashing.
// This is valid only in Release mode when --enable-dcheck is specified.
const wchar_t kSilentDumpOnDCHECK[] = L"silent-dump-on-dcheck";

// Normally when the user attempts to navigate to a page that was the result of
// a post we prompt to make sure they want to. This switch may be used to
// disable that check. This switch is used during automated testing.
const wchar_t kDisablePromptOnRepost[] = L"disable-prompt-on-repost";

// Disable pop-up blocking.
const wchar_t kDisablePopupBlocking[] = L"disable-popup-blocking";

// Don't execute JavaScript (browser JS like the new tab page still runs).
const wchar_t kDisableJavaScript[] = L"disable-javascript";

// Prevent Java from running.
const wchar_t kDisableJava[] = L"disable-java";

// Prevent plugins from running.
const wchar_t kDisablePlugins[] = L"disable-plugins";

// Prevent images from loading.
const wchar_t kDisableImages[] = L"disable-images";

// Use the low fragmentation heap for the CRT.
const wchar_t kUseLowFragHeapCrt[] = L"use-lf-heap";

#ifndef NDEBUG
// Debug only switch to specify which gears plugin dll to load.
const wchar_t kGearsPluginPathOverride[] = L"gears-plugin-path";
#endif

// Switch to load Gears in the renderer process.
const wchar_t kGearsInRenderer[] = L"gears-in-renderer";

// Enable new HTTP stack.
const wchar_t kUseNewHttp[] = L"new-http";

// Enable the fastback page cache.
const wchar_t kEnableFastback[] = L"enable-fastback";

// Allow loading of the javascript debugger UI from the filesystem.
const wchar_t kJavaScriptDebuggerPath[] = L"javascript-debugger-path";

const wchar_t kEnableP13n[] = L"enable-p13n";

// Enable support for SDCH filtering (dictionary based expansion of content).
// Optional argument is *the* only domain name that will have SDCH suppport.
// Default is  "-enable-sdch" to advertise SDCH on all domains.
// Sample usage with argument: "-enable-sdch=.google.com"
// SDCH is currently only supported server-side for searches on google.com.
const wchar_t kSdchFilter[] = L"enable-sdch";

// Enable Greasemonkey script support.
const wchar_t kEnableGreasemonkey[] = L"enable-greasemonkey";

// Causes the browser to launch directly in incognito mode.
const wchar_t kIncognito[] = L"incognito";

// Turn on an experimental implementation of SafeBrowsing which improves
// performance during updates by avoiding the enormous IO from SQLite
// operations.
const wchar_t kUseNewSafeBrowsing[] = L"new-safe-browsing";

}  // namespace switches

