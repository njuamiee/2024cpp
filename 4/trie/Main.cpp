#include "SimpleGTest.h"
#include "trie.h"
#include "trie_store.h"
#include <cassert>
#include <cstdlib>
#include <functional>
#include <optional>

using Integer = std::unique_ptr<uint32_t>;

// === TRIE_TEST_CASES (71%) ===
void TrieTest_ConstructorTest();
void TrieTest_BasicPutTest();
void TrieTest_TrieStructureCheck();
void TrieTest_BasicPutGetTest();
void TrieTest_PutGetOnePath();
void TrieTest_BasicRemoveTest1();
void TrieTest_BasicRemoveTest2();
void TrieTest_RemoveFreeTest();
void TrieTest_MismatchTypeTest();
void TrieTest_CopyOnWriteTest1();
void TrieTest_CopyOnWriteTest2();
void TrieTest_CopyOnWriteTest3();
void TrieTest_MixedTest();
void TrieTest_PointerStability();
void TrieTest_NonCopyableTest();

// === TRIE_STROE_TEST_CASES (29%) ===
void TrieStoreTest_BasicTest();
void TrieStoreTest_GuardTest();
void TrieStoreTest_MixedTest();
void TrieStoreTest_MixedConcurrentTest();
void TrieStoreTest_NonCopyableTest();
void TrieStoreTest_ReadWriteTest();

#define REGISTER_TEST_CASE(name) {#name, name}

int main() {
  std::unordered_map<std::string, std::function<void()>>
      test_functions_by_name = {
          REGISTER_TEST_CASE(TrieTest_ConstructorTest),
          REGISTER_TEST_CASE(TrieTest_BasicPutTest),
          REGISTER_TEST_CASE(TrieTest_TrieStructureCheck),
          REGISTER_TEST_CASE(TrieTest_BasicPutGetTest),
          REGISTER_TEST_CASE(TrieTest_PutGetOnePath),
          REGISTER_TEST_CASE(TrieTest_BasicRemoveTest1),
          REGISTER_TEST_CASE(TrieTest_BasicRemoveTest2),
          REGISTER_TEST_CASE(TrieTest_RemoveFreeTest),
          REGISTER_TEST_CASE(TrieTest_MismatchTypeTest),
          REGISTER_TEST_CASE(TrieTest_CopyOnWriteTest1),
          REGISTER_TEST_CASE(TrieTest_CopyOnWriteTest2),
          REGISTER_TEST_CASE(TrieTest_CopyOnWriteTest3),
          REGISTER_TEST_CASE(TrieTest_MixedTest),
          REGISTER_TEST_CASE(TrieTest_PointerStability),
          REGISTER_TEST_CASE(TrieTest_NonCopyableTest),
          REGISTER_TEST_CASE(TrieStoreTest_BasicTest),
          REGISTER_TEST_CASE(TrieStoreTest_GuardTest),
          REGISTER_TEST_CASE(TrieStoreTest_MixedTest),
          REGISTER_TEST_CASE(TrieStoreTest_MixedConcurrentTest),
          REGISTER_TEST_CASE(TrieStoreTest_NonCopyableTest),
          REGISTER_TEST_CASE(TrieStoreTest_ReadWriteTest),
      };

  std::string test_case_name;
  std::cin >> test_case_name;
  auto it = test_functions_by_name.find(test_case_name);
  assert(it != test_functions_by_name.end());
  auto fn = it->second;
  fn();
  return 0;
}

TEST(TrieTest, ConstructorTest) { auto trie = Trie(); }

TEST(TrieTest, BasicPutTest) {
  auto trie = Trie();
  trie = trie.Put<uint32_t>("test-int", 233);
  trie = trie.Put<uint64_t>("test-int2", 23333333);
  trie = trie.Put<std::string>("test-string", "test");
  trie = trie.Put<std::string>("", "empty-key");
}

TEST(TrieTest, TrieStructureCheck) {
  auto trie = Trie();
  // Put something
  trie = trie.Put<uint32_t>("test", 233);
  ASSERT_EQ(*trie.Get<uint32_t>("test"), 233);
  // Ensure the trie is the same representation of the writeup
  // (Some students were using '\0' as the terminator in previous semesters)
  auto root = trie.GetRoot();
  ASSERT_EQ(root->children_.size(), 1);
  ASSERT_EQ(root->children_.at('t')->children_.size(), 1);
  ASSERT_EQ(root->children_.at('t')->children_.at('e')->children_.size(), 1);
  ASSERT_EQ(root->children_.at('t')->children_.at('e')->children_.at('s')->children_.size(), 1);
  ASSERT_EQ(root->children_.at('t')->children_.at('e')->children_.at('s')->children_.at('t')->children_.size(), 0);
  ASSERT_TRUE(root->children_.at('t')->children_.at('e')->children_.at('s')->children_.at('t')->is_value_node_);
}

TEST(TrieTest, BasicPutGetTest) {
  auto trie = Trie();
  // Put something
  trie = trie.Put<uint32_t>("test", 233);
  ASSERT_EQ(*trie.Get<uint32_t>("test"), 233);
  // Put something else
  trie = trie.Put<uint32_t>("test", 23333333);
  ASSERT_EQ(*trie.Get<uint32_t>("test"), 23333333);
  // Overwrite with another type
  trie = trie.Put<std::string>("test", "23333333");
  ASSERT_EQ(*trie.Get<std::string>("test"), "23333333");
  // Get something that doesn't exist
  ASSERT_EQ(trie.Get<std::string>("test-2333"), nullptr);
  // Put something at root
  trie = trie.Put<std::string>("", "empty-key");
  ASSERT_EQ(*trie.Get<std::string>(""), "empty-key");
}

TEST(TrieTest, PutGetOnePath) {
  auto trie = Trie();
  trie = trie.Put<uint32_t>("111", 111);
  trie = trie.Put<uint32_t>("11", 11);
  trie = trie.Put<uint32_t>("1111", 1111);
  trie = trie.Put<uint32_t>("11", 22);
  ASSERT_EQ(*trie.Get<uint32_t>("11"), 22);
  ASSERT_EQ(*trie.Get<uint32_t>("111"), 111);
  ASSERT_EQ(*trie.Get<uint32_t>("1111"), 1111);
}

TEST(TrieTest, BasicRemoveTest1) {
  auto trie = Trie();
  // Put something
  trie = trie.Put<uint32_t>("test", 2333);
  ASSERT_EQ(*trie.Get<uint32_t>("test"), 2333);
  trie = trie.Put<uint32_t>("te", 23);
  ASSERT_EQ(*trie.Get<uint32_t>("te"), 23);
  trie = trie.Put<uint32_t>("tes", 233);
  ASSERT_EQ(*trie.Get<uint32_t>("tes"), 233);
  // Delete something
  trie = trie.Remove("test");
  trie = trie.Remove("tes");
  trie = trie.Remove("te");

  ASSERT_EQ(trie.Get<uint32_t>("te"), nullptr);
  ASSERT_EQ(trie.Get<uint32_t>("tes"), nullptr);
  ASSERT_EQ(trie.Get<uint32_t>("test"), nullptr);
}

TEST(TrieTest, BasicRemoveTest2) {
  auto trie = Trie();
  // Put something
  trie = trie.Put<uint32_t>("test", 2333);
  ASSERT_EQ(*trie.Get<uint32_t>("test"), 2333);
  trie = trie.Put<uint32_t>("te", 23);
  ASSERT_EQ(*trie.Get<uint32_t>("te"), 23);
  trie = trie.Put<uint32_t>("tes", 233);
  ASSERT_EQ(*trie.Get<uint32_t>("tes"), 233);
  trie = trie.Put<uint32_t>("", 123);
  ASSERT_EQ(*trie.Get<uint32_t>(""), 123);
  // Delete something
  trie = trie.Remove("");
  trie = trie.Remove("te");
  trie = trie.Remove("tes");
  trie = trie.Remove("test");

  ASSERT_EQ(trie.Get<uint32_t>(""), nullptr);
  ASSERT_EQ(trie.Get<uint32_t>("te"), nullptr);
  ASSERT_EQ(trie.Get<uint32_t>("tes"), nullptr);
  ASSERT_EQ(trie.Get<uint32_t>("test"), nullptr);
}

TEST(TrieTest, RemoveFreeTest) {
  auto trie = Trie();
  trie = trie.Put<uint32_t>("test", 2333);
  trie = trie.Put<uint32_t>("te", 23);
  trie = trie.Put<uint32_t>("tes", 233);
  trie = trie.Remove("tes");
  trie = trie.Remove("test");
  ASSERT_EQ(trie.GetRoot()->children_.at('t')->children_.at('e')->children_.size(), 0);
  trie = trie.Remove("te");
  ASSERT_EQ(trie.GetRoot(), nullptr);
}

TEST(TrieTest, MismatchTypeTest) {
  auto trie = Trie();
  // Put something
  trie = trie.Put<uint32_t>("test", 2333);
  ASSERT_EQ(trie.Get<std::string>("test"), nullptr);
}

TEST(TrieTest, CopyOnWriteTest1) {
  auto empty_trie = Trie();
  // Put something
  auto trie1 = empty_trie.Put<uint32_t>("test", 2333);
  auto trie2 = trie1.Put<uint32_t>("te", 23);
  auto trie3 = trie2.Put<uint32_t>("tes", 233);

  // Delete something
  auto trie4 = trie3.Remove("te");
  auto trie5 = trie3.Remove("tes");
  auto trie6 = trie3.Remove("test");

  // Check each snapshot
  ASSERT_EQ(*trie3.Get<uint32_t>("te"), 23);
  ASSERT_EQ(*trie3.Get<uint32_t>("tes"), 233);
  ASSERT_EQ(*trie3.Get<uint32_t>("test"), 2333);

  ASSERT_EQ(trie4.Get<uint32_t>("te"), nullptr);
  ASSERT_EQ(*trie4.Get<uint32_t>("tes"), 233);
  ASSERT_EQ(*trie4.Get<uint32_t>("test"), 2333);

  ASSERT_EQ(*trie5.Get<uint32_t>("te"), 23);
  ASSERT_EQ(trie5.Get<uint32_t>("tes"), nullptr);
  ASSERT_EQ(*trie5.Get<uint32_t>("test"), 2333);

  ASSERT_EQ(*trie6.Get<uint32_t>("te"), 23);
  ASSERT_EQ(*trie6.Get<uint32_t>("tes"), 233);
  ASSERT_EQ(trie6.Get<uint32_t>("test"), nullptr);
}

TEST(TrieTest, CopyOnWriteTest2) {
  auto empty_trie = Trie();
  // Put something
  auto trie1 = empty_trie.Put<uint32_t>("test", 2333);
  auto trie2 = trie1.Put<uint32_t>("te", 23);
  auto trie3 = trie2.Put<uint32_t>("tes", 233);

  // Override something
  auto trie4 = trie3.Put<std::string>("te", "23");
  auto trie5 = trie3.Put<std::string>("tes", "233");
  auto trie6 = trie3.Put<std::string>("test", "2333");

  // Check each snapshot
  ASSERT_EQ(*trie3.Get<uint32_t>("te"), 23);
  ASSERT_EQ(*trie3.Get<uint32_t>("tes"), 233);
  ASSERT_EQ(*trie3.Get<uint32_t>("test"), 2333);

  ASSERT_EQ(*trie4.Get<std::string>("te"), "23");
  ASSERT_EQ(*trie4.Get<uint32_t>("tes"), 233);
  ASSERT_EQ(*trie4.Get<uint32_t>("test"), 2333);

  ASSERT_EQ(*trie5.Get<uint32_t>("te"), 23);
  ASSERT_EQ(*trie5.Get<std::string>("tes"), "233");
  ASSERT_EQ(*trie5.Get<uint32_t>("test"), 2333);

  ASSERT_EQ(*trie6.Get<uint32_t>("te"), 23);
  ASSERT_EQ(*trie6.Get<uint32_t>("tes"), 233);
  ASSERT_EQ(*trie6.Get<std::string>("test"), "2333");
}

TEST(TrieTest, CopyOnWriteTest3) {
  auto empty_trie = Trie();
  // Put something
  auto trie1 = empty_trie.Put<uint32_t>("test", 2333);
  auto trie2 = trie1.Put<uint32_t>("te", 23);
  auto trie3 = trie2.Put<uint32_t>("", 233);

  // Override something
  auto trie4 = trie3.Put<std::string>("te", "23");
  auto trie5 = trie3.Put<std::string>("", "233");
  auto trie6 = trie3.Put<std::string>("test", "2333");

  // Check each snapshot
  ASSERT_EQ(*trie3.Get<uint32_t>("te"), 23);
  ASSERT_EQ(*trie3.Get<uint32_t>(""), 233);
  ASSERT_EQ(*trie3.Get<uint32_t>("test"), 2333);

  ASSERT_EQ(*trie4.Get<std::string>("te"), "23");
  ASSERT_EQ(*trie4.Get<uint32_t>(""), 233);
  ASSERT_EQ(*trie4.Get<uint32_t>("test"), 2333);

  ASSERT_EQ(*trie5.Get<uint32_t>("te"), 23);
  ASSERT_EQ(*trie5.Get<std::string>(""), "233");
  ASSERT_EQ(*trie5.Get<uint32_t>("test"), 2333);

  ASSERT_EQ(*trie6.Get<uint32_t>("te"), 23);
  ASSERT_EQ(*trie6.Get<uint32_t>(""), 233);
  ASSERT_EQ(*trie6.Get<std::string>("test"), "2333");
}

TEST(TrieTest, MixedTest) {
  auto trie = Trie();
  for (uint32_t i = 0; i < 23333; i++) {
    std::string key = fmt::format("{:#05}", i);
    std::string value = fmt::format("value-{:#08}", i);
    trie = trie.Put<std::string>(key, value);
  }
  auto trie_full = trie;
  for (uint32_t i = 0; i < 23333; i += 2) {
    std::string key = fmt::format("{:#05}", i);
    std::string value = fmt::format("new-value-{:#08}", i);
    trie = trie.Put<std::string>(key, value);
  }
  auto trie_override = trie;
  for (uint32_t i = 0; i < 23333; i += 3) {
    std::string key = fmt::format("{:#05}", i);
    trie = trie.Remove(key);
  }
  auto trie_final = trie;

  // verify trie_full
  for (uint32_t i = 0; i < 23333; i++) {
    std::string key = fmt::format("{:#05}", i);
    std::string value = fmt::format("value-{:#08}", i);
    ASSERT_EQ(*trie_full.Get<std::string>(key), value);
  }

  // verify trie_override
  for (uint32_t i = 0; i < 23333; i++) {
    std::string key = fmt::format("{:#05}", i);
    if (i % 2 == 0) {
      std::string value = fmt::format("new-value-{:#08}", i);
      ASSERT_EQ(*trie_override.Get<std::string>(key), value);
    } else {
      std::string value = fmt::format("value-{:#08}", i);
      ASSERT_EQ(*trie_override.Get<std::string>(key), value);
    }
  }

  // verify final trie
  for (uint32_t i = 0; i < 23333; i++) {
    std::string key = fmt::format("{:#05}", i);
    if (i % 3 == 0) {
      ASSERT_EQ(trie_final.Get<std::string>(key), nullptr);
    } else if (i % 2 == 0) {
      std::string value = fmt::format("new-value-{:#08}", i);
      ASSERT_EQ(*trie_final.Get<std::string>(key), value);
    } else {
      std::string value = fmt::format("value-{:#08}", i);
      ASSERT_EQ(*trie_final.Get<std::string>(key), value);
    }
  }
}

TEST(TrieTest, PointerStability) {
  auto trie = Trie();
  trie = trie.Put<uint32_t>("test", 2333);
  auto *ptr_before = trie.Get<std::string>("test");
  trie = trie.Put<uint32_t>("tes", 233);
  trie = trie.Put<uint32_t>("te", 23);
  auto *ptr_after = trie.Get<std::string>("test");
  ASSERT_EQ(reinterpret_cast<uint64_t>(ptr_before), reinterpret_cast<uint64_t>(ptr_after));
}

TEST(TrieTest, NonCopyableTest) {
  auto trie = Trie();
  trie = trie.Put<Integer>("tes", std::make_unique<uint32_t>(233));
  trie = trie.Put<Integer>("te", std::make_unique<uint32_t>(23));
  trie = trie.Put<Integer>("test", std::make_unique<uint32_t>(2333));
  ASSERT_EQ(**trie.Get<Integer>("te"), 23);
  ASSERT_EQ(**trie.Get<Integer>("tes"), 233);
  ASSERT_EQ(**trie.Get<Integer>("test"), 2333);
  trie = trie.Remove("te");
  trie = trie.Remove("tes");
  trie = trie.Remove("test");
  ASSERT_EQ(trie.Get<Integer>("te"), nullptr);
  ASSERT_EQ(trie.Get<Integer>("tes"), nullptr);
  ASSERT_EQ(trie.Get<Integer>("test"), nullptr);
}

TEST(TrieStoreTest, BasicTest) {
  auto store = TrieStore();
  ASSERT_EQ_NO_REPORT(store.Get<uint32_t>("233"), std::nullopt);
  store.Put<uint32_t>("233", 2333);
  {
    auto guard = store.Get<uint32_t>("233");
    ASSERT_EQ(**guard, 2333);
  }
  store.Remove("233");
  {
    auto guard = store.Get<uint32_t>("233");
    ASSERT_EQ_NO_REPORT(guard, std::nullopt);
  }
}

TEST(TrieStoreTest, GuardTest) {
  auto store = TrieStore();
  ASSERT_EQ_NO_REPORT(store.Get<uint32_t>("233"), std::nullopt);

  store.Put<std::string>("233", "2333");
  auto guard = store.Get<std::string>("233");
  ASSERT_EQ(**guard, "2333");

  store.Remove("233");
  {
    auto guard = store.Get<std::string>("233");
    ASSERT_EQ_NO_REPORT(guard, std::nullopt);
  }

  ASSERT_EQ(**guard, "2333");
}

TEST(TrieStoreTest, MixedTest) {
  auto store = TrieStore();
  for (uint32_t i = 0; i < 23333; i++) {
    std::string key = fmt::format("{:#05}", i);
    std::string value = fmt::format("value-{:#08}", i);
    store.Put<std::string>(key, value);
  }
  for (uint32_t i = 0; i < 23333; i += 2) {
    std::string key = fmt::format("{:#05}", i);
    std::string value = fmt::format("new-value-{:#08}", i);
    store.Put<std::string>(key, value);
  }
  for (uint32_t i = 0; i < 23333; i += 3) {
    std::string key = fmt::format("{:#05}", i);
    store.Remove(key);
  }

  // verify final trie
  for (uint32_t i = 0; i < 23333; i++) {
    std::string key = fmt::format("{:#05}", i);
    if (i % 3 == 0) {
      ASSERT_EQ_NO_REPORT(store.Get<std::string>(key), std::nullopt);
    } else if (i % 2 == 0) {
      std::string value = fmt::format("new-value-{:#08}", i);
      auto guard = store.Get<std::string>(key);
      ASSERT_EQ(**guard, value);
    } else {
      std::string value = fmt::format("value-{:#08}", i);
      auto guard = store.Get<std::string>(key);
      ASSERT_EQ(**guard, value);
    }
  }
}

TEST(TrieStoreTest, MixedConcurrentTest) {
  auto store = TrieStore();

  std::vector<std::thread> threads;

  const int keys_per_thread = 500;

  for (int tid = 0; tid < 2; tid++) {
    std::thread t([&store, tid] {
      for (uint32_t i = 0; i < keys_per_thread; i++) {
        std::string key = fmt::format("{:#05}", i * 2 + tid);
        std::string value = fmt::format("value-{:#08}", i * 2 + tid);
        store.Put<std::string>(key, value);
      }
      for (uint32_t i = 0; i < keys_per_thread; i++) {
        std::string key = fmt::format("{:#05}", i * 2 + tid);
        store.Remove(key);
      }
      for (uint32_t i = 0; i < keys_per_thread; i++) {
        std::string key = fmt::format("{:#05}", i * 2 + tid);
        std::string value = fmt::format("new-value-{:#08}", i * 2 + tid);
        store.Put<std::string>(key, value);
      }
    });
    threads.push_back(std::move(t));
  }

  std::vector<std::thread> read_threads;
  std::shared_ptr<std::atomic_bool> stop = std::make_shared<std::atomic_bool>(false);

  for (int tid = 0; tid < 2; tid++) {
    std::thread t([&store, tid, stop] {
      uint32_t i = 0;
      while (!stop->load()) {
        std::string key = fmt::format("{:#05}", i * 2 + tid);
        store.Get<std::string>(key);
        i = (i + 1) % keys_per_thread;
      }
    });
    read_threads.push_back(std::move(t));
  }

  for (auto &t : threads) {
    t.join();
  }

  stop->store(true);

  for (auto &t : read_threads) {
    t.join();
  }

  // verify final trie
  for (uint32_t i = 0; i < keys_per_thread * 2; i++) {
    std::string key = fmt::format("{:#05}", i);
    std::string value = fmt::format("new-value-{:#08}", i);
    auto guard = store.Get<std::string>(key);
    ASSERT_EQ(**guard, value);
  }
}

TEST(TrieStoreTest, NonCopyableTest) {
  auto store = TrieStore();
  store.Put<Integer>("tes", std::make_unique<uint32_t>(233));
  store.Put<Integer>("te", std::make_unique<uint32_t>(23));
  store.Put<Integer>("test", std::make_unique<uint32_t>(2333));
  ASSERT_EQ(***store.Get<Integer>("te"), 23);
  ASSERT_EQ(***store.Get<Integer>("tes"), 233);
  ASSERT_EQ(***store.Get<Integer>("test"), 2333);
  store.Remove("te");
  store.Remove("tes");
  store.Remove("test");
  ASSERT_EQ_NO_REPORT(store.Get<Integer>("te"), std::nullopt);
  ASSERT_EQ_NO_REPORT(store.Get<Integer>("tes"), std::nullopt);
  ASSERT_EQ_NO_REPORT(store.Get<Integer>("test"), std::nullopt);
}

TEST(TrieStoreTest, ReadWriteTest) {
  auto store = TrieStore();
  store.Put<uint32_t>("a", 1);
  store.Put<uint32_t>("b", 2);
  store.Put<uint32_t>("c", 3);
  std::promise<int> x;

  std::cerr << "[0] begin" << std::endl;

  std::thread t([&store, &x] { store.Put<MoveBlocked>("d", MoveBlocked(x.get_future())); });

  std::cerr << "[1] thread spawn" << std::endl;

  // Loop for enough time to ensure that the thread is blocked on the promise.
  for (int i = 0; i < 100000; i++) {
    {
      auto guard = store.Get<uint32_t>("a");
      ASSERT_EQ(**guard, 1);
    }
    {
      auto guard = store.Get<uint32_t>("b");
      ASSERT_EQ(**guard, 2);
    }
    {
      auto guard = store.Get<uint32_t>("c");
      ASSERT_EQ(**guard, 3);
    }
  }

  std::cerr << "[2] read done" << std::endl;

  x.set_value(233);

  t.join();

  std::cerr << "[3] write complete" << std::endl;

  ASSERT_NE_NO_REPORT(store.Get<MoveBlocked>("d"), std::nullopt);
}