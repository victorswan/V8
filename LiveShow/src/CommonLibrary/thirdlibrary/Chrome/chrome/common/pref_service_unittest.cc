// Copyright (c) 2006-2008 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/file_util.h"
#include "base/path_service.h"
#include "chrome/common/chrome_paths.h"
#include "chrome/common/json_value_serializer.h"
#include "chrome/common/notification_service.h"
#include "chrome/common/notification_types.h"
#include "chrome/common/pref_names.h"
#include "chrome/common/pref_service.h"
#include "chrome/test/data/resource.h"
#include "testing/gtest/include/gtest/gtest.h"

namespace {

class PrefServiceTest : public testing::Test {
protected:
  virtual void SetUp() {
    // Name a subdirectory of the temp directory.
    ASSERT_TRUE(PathService::Get(base::DIR_TEMP, &test_dir_));
    file_util::AppendToPath(&test_dir_, L"PrefServiceTest");

    // Create a fresh, empty copy of this directory.
    file_util::Delete(test_dir_, true);
    CreateDirectory(test_dir_.c_str(), NULL);

    ASSERT_TRUE(PathService::Get(chrome::DIR_TEST_DATA, &data_dir_));
    file_util::AppendToPath(&data_dir_, L"pref_service");
    ASSERT_TRUE(file_util::PathExists(data_dir_));
  }
  virtual void TearDown() {
    // Clean up test directory
    ASSERT_TRUE(file_util::Delete(test_dir_, false));
    ASSERT_FALSE(file_util::PathExists(test_dir_));
  }

  // the path to temporary directory used to contain the test operations
  std::wstring test_dir_;
  // the path to the directory where the test data is stored
  std::wstring data_dir_;
};

class TestPrefObserver : public NotificationObserver {
 public:
  TestPrefObserver(const PrefService* prefs, const std::wstring& pref_name,
      const std::wstring& new_pref_value)
      : observer_fired_(false),
        prefs_(prefs),
        pref_name_(pref_name),
        new_pref_value_(new_pref_value) {
  }
  virtual ~TestPrefObserver() {}

  virtual void Observe(NotificationType type,
                       const NotificationSource& source,
                       const NotificationDetails& details) {
    EXPECT_EQ(type, NOTIFY_PREF_CHANGED);
    PrefService* prefs_in = Source<PrefService>(source).ptr();
    EXPECT_EQ(prefs_in, prefs_);
    std::wstring* pref_name_in = Details<std::wstring>(details).ptr();
    EXPECT_EQ(*pref_name_in, pref_name_);
    EXPECT_EQ(new_pref_value_, prefs_in->GetString(L"homepage"));
    observer_fired_ = true;
  }

  bool observer_fired() { return observer_fired_; }

  void Reset(const std::wstring& new_pref_value) {
    observer_fired_ = false;
    new_pref_value_ = new_pref_value;
  }

 private:
  bool observer_fired_;
  const PrefService* prefs_;
  const std::wstring pref_name_;
  std::wstring new_pref_value_;
};

}  // anonymous namespace

TEST_F(PrefServiceTest, Basic) {
  PrefService prefs;

  // Test that it fails on nonexistent file.
  std::wstring bogus_input_file = data_dir_;
  file_util::AppendToPath(&bogus_input_file, L"read.txt");
  EXPECT_FALSE(prefs.LoadPersistentPrefs(bogus_input_file));

  // Test that the persistent value can be loaded.
  std::wstring input_file = data_dir_;
  file_util::AppendToPath(&input_file, L"read.json");
  ASSERT_TRUE(file_util::PathExists(input_file));
  ASSERT_TRUE(prefs.LoadPersistentPrefs(input_file));

  // Register test prefs.
  const wchar_t kNewWindowsInTabs[] = L"tabs.new_windows_in_tabs";
  const wchar_t kMaxTabs[] = L"tabs.max_tabs";
  prefs.RegisterStringPref(prefs::kHomePage, L"");
  prefs.RegisterBooleanPref(kNewWindowsInTabs, false);
  prefs.RegisterIntegerPref(kMaxTabs, 0);

  std::wstring microsoft(L"http://www.microsoft.com");
  std::wstring cnn(L"http://www.cnn.com");
  std::wstring homepage(L"http://www.example.com");

  EXPECT_EQ(cnn, prefs.GetString(prefs::kHomePage));

  // Now test that the transient value overrides the persistent value,
  // without actually altering the persistent store.
  EXPECT_TRUE(prefs.transient()->SetString(prefs::kHomePage, microsoft));
  EXPECT_TRUE(prefs.transient()->GetString(prefs::kHomePage, &homepage));
  EXPECT_EQ(microsoft, homepage);

  EXPECT_EQ(microsoft, prefs.GetString(prefs::kHomePage));

  // Test reading some other data types from sub-dictionaries, and
  // writing to the persistent store.
  EXPECT_TRUE(prefs.GetBoolean(kNewWindowsInTabs));
  prefs.SetBoolean(kNewWindowsInTabs, false);
  EXPECT_FALSE(prefs.GetBoolean(kNewWindowsInTabs));

  EXPECT_EQ(20, prefs.GetInteger(kMaxTabs));
  prefs.SetInteger(kMaxTabs, 10);
  EXPECT_EQ(10, prefs.GetInteger(kMaxTabs));

  // Serialize and compare to expected output.
  std::wstring output_file = test_dir_;
  file_util::AppendToPath(&output_file, L"write.json");
  prefs.pref_filename_ = output_file;
  ASSERT_TRUE(prefs.SavePersistentPrefs(NULL));
  std::wstring golden_output_file = data_dir_;
  file_util::AppendToPath(&golden_output_file, L"write.golden.json");
  ASSERT_TRUE(file_util::PathExists(golden_output_file));
  ASSERT_TRUE(file_util::ContentsEqual(golden_output_file, output_file));
}

TEST_F(PrefServiceTest, Overlay) {
  const std::string transient =
    "{\"bool\":true, \"int\":2, \"real\":2.0, \"string\":\"transient\","
    "\"dictionary\":{\"value\":\"transient\"},"
    "\"list\":[\"transient\"]}";

  std::wstring persistent_string(L"persistent");
  std::wstring transient_string(L"transient");

  PrefService prefs;

  std::wstring persistent_file = data_dir_;
  file_util::AppendToPath(&persistent_file, L"overlay.json");
  EXPECT_TRUE(prefs.LoadPersistentPrefs(persistent_file));

  Value* transient_value;
  {
    JSONStringValueSerializer serializer(transient);
    ASSERT_TRUE(serializer.Deserialize(&transient_value));
  }
  prefs.transient()->Set(transient_string, transient_value);

  Value* both_transient_value;
  {
    JSONStringValueSerializer serializer(transient);
    ASSERT_TRUE(serializer.Deserialize(&both_transient_value));
  }
  prefs.transient()->Set(L"both", both_transient_value);

  // Register test prefs
  const wchar_t* kTypes[] = { L"neither.", L"persistent.", L"transient.", L"both." };
  for (size_t i = 0; i < arraysize(kTypes); ++i) {
    wchar_t temp[1024];
    wcscpy_s(temp, kTypes[i]);
    wcscat_s(temp, L"bool");
    prefs.RegisterBooleanPref(temp, false);

    wcscpy_s(temp, kTypes[i]);
    wcscat_s(temp, L"int");
    prefs.RegisterIntegerPref(temp, 0);

    wcscpy_s(temp, kTypes[i]);
    wcscat_s(temp, L"real");
    prefs.RegisterRealPref(temp, 0.0);

    wcscpy_s(temp, kTypes[i]);
    wcscat_s(temp, L"string");
    prefs.RegisterStringPref(temp, L"");

    wcscpy_s(temp, kTypes[i]);
    wcscat_s(temp, L"list");
    prefs.RegisterListPref(temp);

    wcscpy_s(temp, kTypes[i]);
    wcscat_s(temp, L"dictionary");
    prefs.RegisterDictionaryPref(temp);
  }

  ASSERT_FALSE(prefs.GetBoolean(L"neither.bool"));
  ASSERT_FALSE(prefs.GetBoolean(L"persistent.bool"));
  ASSERT_TRUE(prefs.GetBoolean(L"transient.bool"));
  ASSERT_TRUE(prefs.GetBoolean(L"both.bool"));

  ASSERT_EQ(0, prefs.GetInteger(L"neither.int"));
  ASSERT_EQ(1, prefs.GetInteger(L"persistent.int"));
  ASSERT_EQ(2, prefs.GetInteger(L"transient.int"));
  ASSERT_EQ(2, prefs.GetInteger(L"both.int"));

  ASSERT_EQ(0.0, prefs.GetReal(L"neither.real"));
  ASSERT_EQ(1.0, prefs.GetReal(L"persistent.real"));
  ASSERT_EQ(2.0, prefs.GetReal(L"transient.real"));
  ASSERT_EQ(2.0, prefs.GetReal(L"both.real"));

  ASSERT_EQ(std::wstring(), prefs.GetString(L"neither.string"));
  ASSERT_EQ(persistent_string, prefs.GetString(L"persistent.string"));
  ASSERT_EQ(transient_string, prefs.GetString(L"transient.string"));
  ASSERT_EQ(transient_string, prefs.GetString(L"both.string"));

  {
    const DictionaryValue* result_value =
        prefs.GetDictionary(L"neither.dictionary");
    ASSERT_FALSE(result_value);
  }

  {
    const DictionaryValue* result_value =
      prefs.GetDictionary(L"persistent.dictionary");
    ASSERT_TRUE(result_value);
    std::wstring result_string;
    ASSERT_TRUE(result_value->GetString(L"value", &result_string));
    ASSERT_EQ(persistent_string, result_string);
  }

  {
    const DictionaryValue* result_value =
      prefs.GetDictionary(L"transient.dictionary");
    ASSERT_TRUE(result_value);
    std::wstring result_string;
    ASSERT_TRUE(result_value->GetString(L"value", &result_string));
    ASSERT_EQ(transient_string, result_string);
  }

  {
    const DictionaryValue* result_value =
      prefs.GetDictionary(L"both.dictionary");
    ASSERT_TRUE(result_value);
    std::wstring result_string;
    ASSERT_TRUE(result_value->GetString(L"value", &result_string));
    ASSERT_EQ(transient_string, result_string);
  }

  {
    const ListValue* result_value = prefs.GetList(L"neither.list");
    ASSERT_FALSE(result_value);
  }

  {
    const ListValue* result_value = prefs.GetList(L"persistent.list");
    ASSERT_TRUE(result_value);
    Value* member_value;
    ASSERT_TRUE(result_value->Get(0, &member_value));
    ASSERT_TRUE(member_value);
    std::wstring result_string;
    ASSERT_TRUE(member_value->GetAsString(&result_string));
    ASSERT_EQ(persistent_string, result_string);
  }

  {
    const ListValue* result_value = prefs.GetList(L"transient.list");
    ASSERT_TRUE(result_value);
    Value* member_value;
    ASSERT_TRUE(result_value->Get(0, &member_value));
    ASSERT_TRUE(member_value);
    std::wstring result_string;
    ASSERT_TRUE(member_value->GetAsString(&result_string));
    ASSERT_EQ(transient_string, result_string);
  }

  {
    const ListValue* result_value = prefs.GetList(L"both.list");
    ASSERT_TRUE(result_value);
    Value* member_value;
    ASSERT_TRUE(result_value->Get(0, &member_value));
    ASSERT_TRUE(member_value);
    std::wstring result_string;
    ASSERT_TRUE(member_value->GetAsString(&result_string));
    ASSERT_EQ(transient_string, result_string);
  }
}

TEST_F(PrefServiceTest, Observers) {
  PrefService prefs;

  std::wstring input_file = data_dir_;
  file_util::AppendToPath(&input_file, L"read.json");
  EXPECT_TRUE(file_util::PathExists(input_file));
  EXPECT_TRUE(prefs.LoadPersistentPrefs(input_file));

  const wchar_t pref_name[] = L"homepage";
  prefs.RegisterStringPref(pref_name, L"");
  EXPECT_EQ(std::wstring(L"http://www.cnn.com"), prefs.GetString(pref_name));

  const std::wstring new_pref_value(L"http://www.google.com/");
  TestPrefObserver obs(&prefs, pref_name, new_pref_value);
  prefs.AddPrefObserver(pref_name, &obs);
  // This should fire the checks in TestPrefObserver::Observe.
  prefs.SetString(pref_name, new_pref_value);

  // Make sure the tests were actually run.
  EXPECT_TRUE(obs.observer_fired());

  // Now try adding a second pref observer.
  const std::wstring new_pref_value2(L"http://www.youtube.com/");
  obs.Reset(new_pref_value2);
  TestPrefObserver obs2(&prefs, pref_name, new_pref_value2);
  prefs.AddPrefObserver(pref_name, &obs2);
  // This should fire the checks in obs and obs2.
  prefs.SetString(pref_name, new_pref_value2);
  EXPECT_TRUE(obs.observer_fired());
  EXPECT_TRUE(obs2.observer_fired());

  // Make sure obs2 still works after removing obs.
  prefs.RemovePrefObserver(pref_name, &obs);
  obs.Reset(L"");
  obs2.Reset(new_pref_value);
  // This should only fire the observer in obs2.
  prefs.SetString(pref_name, new_pref_value);
  EXPECT_FALSE(obs.observer_fired());
  EXPECT_TRUE(obs2.observer_fired());

  // Ok, clean up.
  prefs.RemovePrefObserver(pref_name, &obs2);
}

TEST_F(PrefServiceTest, LocalizedPrefs) {
  PrefService prefs;
  const wchar_t kBoolean[] = L"boolean";
  const wchar_t kInteger[] = L"integer";
  const wchar_t kString[] = L"string";
  prefs.RegisterLocalizedBooleanPref(kBoolean, IDS_LOCALE_BOOL);
  prefs.RegisterLocalizedIntegerPref(kInteger, IDS_LOCALE_INT);
  prefs.RegisterLocalizedStringPref(kString, IDS_LOCALE_STRING);

  // The locale default should take preference over the user default.
  EXPECT_FALSE(prefs.GetBoolean(kBoolean));
  EXPECT_EQ(1, prefs.GetInteger(kInteger));
  EXPECT_EQ(L"hello", prefs.GetString(kString));

  prefs.SetBoolean(kBoolean, true);
  EXPECT_TRUE(prefs.GetBoolean(kBoolean));
  prefs.SetInteger(kInteger, 5);
  EXPECT_EQ(5, prefs.GetInteger(kInteger));
  prefs.SetString(kString, L"foo");
  EXPECT_EQ(L"foo", prefs.GetString(kString));
}

TEST_F(PrefServiceTest, NoObserverFire) {
  PrefService prefs;

  const wchar_t pref_name[] = L"homepage";
  prefs.RegisterStringPref(pref_name, L"");

  const std::wstring new_pref_value(L"http://www.google.com/");
  TestPrefObserver obs(&prefs, pref_name, new_pref_value);
  prefs.AddPrefObserver(pref_name, &obs);
  // This should fire the checks in TestPrefObserver::Observe.
  prefs.SetString(pref_name, new_pref_value);

  // Make sure the observer was actually fired.
  EXPECT_TRUE(obs.observer_fired());

  // Setting the pref to the same value should not set the pref value a second
  // time.
  obs.Reset(new_pref_value);
  prefs.SetString(pref_name, new_pref_value);
  EXPECT_FALSE(obs.observer_fired());

  // Clearing the pref should cause the pref to fire.
  obs.Reset(L"");
  prefs.ClearPref(pref_name);
  EXPECT_TRUE(obs.observer_fired());

  // Clearing the pref again should not cause the pref to fire.
  obs.Reset(L"");
  prefs.ClearPref(pref_name);
  EXPECT_FALSE(obs.observer_fired());

  // Ok, clean up.
  prefs.RemovePrefObserver(pref_name, &obs);
}

TEST_F(PrefServiceTest, HasPrefPath) {
  PrefService prefs;

  const wchar_t path[] = L"fake.path";

  // Shouldn't initially have a path.
  EXPECT_FALSE(prefs.HasPrefPath(path));

  // Register the path. This doesn't set a value, so the path still shouldn't
  // exist.
  prefs.RegisterStringPref(path, std::wstring());
  EXPECT_FALSE(prefs.HasPrefPath(path));

  // Set a value and make sure we have a path.
  prefs.persistent_->SetString(path, L"blah");
  EXPECT_TRUE(prefs.HasPrefPath(path));
}

