// Copyright (c) 2006-2008 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Constants for the names of various preferences, for easier changing.

#ifndef CHROME_COMMON_PREF_NAMES_H_
#define CHROME_COMMON_PREF_NAMES_H_

namespace prefs {

// Profile prefs
extern const wchar_t kHomePageIsNewTabPage[];
extern const wchar_t kHomePage[];
extern const wchar_t kProfileName[];
extern const wchar_t kProfileNickname[];
extern const wchar_t kProfileID[];
extern const wchar_t kRecentlyViewedModelBiasActiveTabHistory[];
extern const wchar_t kRecentlyViewedModelSelectionMode[];
extern const wchar_t kSessionExitedCleanly[];
extern const wchar_t kRestoreOnStartup[];
extern const wchar_t kURLsToRestoreOnStartup[];
extern const wchar_t kApplicationLocale[];
extern const wchar_t kDefaultCharset[];
extern const wchar_t kAcceptLanguages[];
extern const wchar_t kStaticEncodings[];
extern const wchar_t kShowBookmarkBar[];
extern const wchar_t kWebKitStandardFontIsSerif[];
extern const wchar_t kWebKitFixedFontFamily[];
extern const wchar_t kWebKitSerifFontFamily[];
extern const wchar_t kWebKitSansSerifFontFamily[];
extern const wchar_t kWebKitCursiveFontFamily[];
extern const wchar_t kWebKitFantasyFontFamily[];
extern const wchar_t kWebKitDefaultFontSize[];
extern const wchar_t kWebKitDefaultFixedFontSize[];
extern const wchar_t kWebKitMinimumFontSize[];
extern const wchar_t kWebKitMinimumLogicalFontSize[];
extern const wchar_t kWebKitJavascriptEnabled[];
extern const wchar_t kWebKitJavascriptCanOpenWindowsAutomatically[];
extern const wchar_t kWebKitLoadsImagesAutomatically[];
extern const wchar_t kWebKitPluginsEnabled[];
extern const wchar_t kWebKitDomPasteEnabled[];
extern const wchar_t kWebKitShrinksStandaloneImagesToFit[];
extern const wchar_t kWebKitDeveloperExtrasEnabled[];
extern const wchar_t kWebKitUsesUniversalDetector[];
extern const wchar_t kWebKitTextAreasAreResizable[];
extern const wchar_t kWebKitJavaEnabled[];
extern const wchar_t kAlwaysCreateDestinationsTab[];
extern const wchar_t kPasswordManagerEnabled[];
extern const wchar_t kSafeBrowsingEnabled[];
extern const wchar_t kSearchSuggestEnabled[];
extern const wchar_t kCookieBehavior[];
extern const wchar_t kMixedContentFiltering[];
extern const wchar_t kDefaultSearchProviderSearchURL[];
extern const wchar_t kDefaultSearchProviderSuggestURL[];
extern const wchar_t kDefaultSearchProviderName[];
extern const wchar_t kDefaultSearchProviderID[];
extern const wchar_t kBlockPopups[];
extern const wchar_t kPromptForDownload[];
extern const wchar_t kAlternateErrorPagesEnabled[];
extern const wchar_t kDnsPrefetchingEnabled[];
extern const wchar_t kDnsStartupPrefetchList[];
extern const wchar_t kIpcDisabledMessages[];
extern const wchar_t kShowHomeButton[];
extern const wchar_t kRecentlySelectedEncoding[];
extern const wchar_t kDeleteBrowsingHistory[];
extern const wchar_t kDeleteDownloadHistory[];
extern const wchar_t kDeleteCache[];
extern const wchar_t kDeleteCookies[];
extern const wchar_t kDeletePasswords[];

// Local state
extern const wchar_t kAvailableProfiles[];

extern const wchar_t kMetricsClientID[];
extern const wchar_t kMetricsSessionID[];
extern const wchar_t kMetricsIsRecording[];
extern const wchar_t kMetricsClientIDTimestamp[];
extern const wchar_t kMetricsReportingEnabled[];
extern const wchar_t kMetricsInitialLogs[];
extern const wchar_t kMetricsOngoingLogs[];

extern const wchar_t kProfileMetrics[];
extern const wchar_t kProfilePrefix[];

extern const wchar_t kStabilityExitedCleanly[];
extern const wchar_t kStabilitySessionEndCompleted[];
extern const wchar_t kStabilityLaunchCount[];
extern const wchar_t kStabilityCrashCount[];
extern const wchar_t kStabilityIncompleteSessionEndCount[];
extern const wchar_t kStabilityPageLoadCount[];
extern const wchar_t kStabilityRendererCrashCount[];
extern const wchar_t kStabilityLaunchTimeSec[];
extern const wchar_t kStabilityLastTimestampSec[];
extern const wchar_t kStabilityUptimeSec[];
extern const wchar_t kStabilityRendererHangCount[];

extern const wchar_t kStabilityBreakpadRegistrationSuccess[];
extern const wchar_t kStabilityBreakpadRegistrationFail[];
extern const wchar_t kStabilityDebuggerPresent[];
extern const wchar_t kStabilityDebuggerNotPresent[];

extern const wchar_t kSecurityRendererOnSboxDesktop[];
extern const wchar_t kSecurityRendererOnDefaultDesktop[];

extern const wchar_t kStabilityPluginStats[];
extern const wchar_t kStabilityPluginPath[];
extern const wchar_t kStabilityPluginLaunches[];
extern const wchar_t kStabilityPluginInstances[];
extern const wchar_t kStabilityPluginCrashes[];

extern const wchar_t kStartRenderersManually[];
extern const wchar_t kBrowserWindowPlacement[];
extern const wchar_t kTaskManagerWindowPlacement[];
extern const wchar_t kPageInfoWindowPlacement[];
extern const wchar_t kMemoryCacheSize[];

extern const wchar_t kDownloadDefaultDirectory[];
extern const wchar_t kDownloadExtensionsToOpen[];
extern const wchar_t kDownloadDirUpgraded[];

extern const wchar_t kSaveFileDefaultDirectory[];

extern const wchar_t kHungPluginDetectFrequency[];
extern const wchar_t kPluginMessageResponseTimeout[];

extern const wchar_t kSpellCheckDictionary[];

extern const wchar_t kExcludedSchemes[];

extern const wchar_t kSafeBrowsingClientKey[];
extern const wchar_t kSafeBrowsingWrappedKey[];

extern const wchar_t kOptionsWindowLastTabIndex[];
extern const wchar_t kShouldShowFirstRunBubble[];
extern const wchar_t kShouldShowWelcomePage[];

extern const wchar_t kLastKnownGoogleURL[];

extern const wchar_t kGeoIDAtInstall[];

extern const wchar_t kShutdownType[];
extern const wchar_t kShutdownNumProcesses[];
extern const wchar_t kShutdownNumProcessesSlow[];

extern const wchar_t kNumBookmarksOnBookmarkBar[];
extern const wchar_t kNumFoldersOnBookmarkBar[];
extern const wchar_t kNumBookmarksInOtherBookmarkFolder[];
extern const wchar_t kNumFoldersInOtherBookmarkFolder[];

extern const wchar_t kNumKeywords[];
}

#endif  // CHROME_COMMON_PREF_NAMES_H_

