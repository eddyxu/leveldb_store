/*
 * Copyright 2014 (c) Lei Xu <eddyxu@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef STORE_TEST_LEVELDB_STORE_H_
#define STORE_TEST_LEVELDB_STORE_H_

#include <map>
#include <string>
#include "store/leveldb_store.h"
#include "store/status.h"

namespace leveldb_store {

/**
 * \brief A testing LevelDB that keeps all data in RAM. It should only be used
 * for testing purpose.
 *
 * The difference between using TestLevelDBStore and using MockLevelDBStore is
 * that this class can be a drop-in replacement for LevelDBStore, without
 * checking the method calls. In other word, this class is simpler than
 * MockLevelDBStore to be used in most cases. However, it can not control the
 * behavior of LevelDBStore, e.g., simulate the disk failures of LevelDB, in
 * which case it is preferable to use MockLevelDBStore.
 */
class TestLevelDBStore : public LevelDBStore {
 public:
  typedef std::map<std::string, std::string> MapType;

  /// Constructs a test leveldb store in RAM.
  TestLevelDBStore() = default;

  /// Constructs a test leveldb store with initialized values.
  TestLevelDBStore(const MapType& other);

  ~TestLevelDBStore() = default;

  /// Open a testing LevelDB, always success.
  Status open() { return Status::OK; }

  /// Creates a testing LevelDB, always success.
  Status create() { return Status::OK; }

  /**
   * \brief Gets a value for the given key.
   * \return Status::OK if the key exists. Otherwise returns Status(-ENOENT).
   */
  Status get(const std::string& key, std::string* value);

  /**
   * \brief Puts a (key, value) pair to the system.
   */
  Status put(const std::string& key, const std::string& value);

  /**
   * \brief Removes a key if it exists.
   */
  Status remove(const std::string& key);

  iterator begin();

  iterator end();

  const MapType& store() const;

 private:
  /// The underlying key-value store is a in-ram map.
  MapType store_;
};

}  // namespace leveldb_store

#endif  // STORE_TEST_LEVELDB_STORE_H_
