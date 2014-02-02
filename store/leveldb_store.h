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

#ifndef STORE_LEVELDB_STORE_H_
#define STORE_LEVELDB_STORE_H_

#include <boost/iterator/iterator_facade.hpp>
#include <leveldb/db.h>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include "vobla/status.h"

using vobla::Status;

/**
 * \brief Wrap LevelDB as a Key-value store and provides STL-style iterators
 */
namespace leveldb_store {

/**
 * \class LevelDBStore "store/leveldb_store.h"
 * \brief A Key-Value persistent storage based on LevelDB.
 *
 * You can access the data through the typical K-V DB operations:
 *  - put(key, value)
 *  - get(key, &value)
 *  - remove(key)
 *  - search(prefix)
 */
class LevelDBStore {
  typedef std::pair<std::string, std::string> KeyValuePair;

 public:
  /**
   * \brief Iterator of LevelDBStore.
   */
  class LevelDBStoreIterator : public boost::iterator_facade<
    LevelDBStoreIterator, KeyValuePair, boost::bidirectional_traversal_tag> {
   public:
    LevelDBStoreIterator();

    explicit LevelDBStoreIterator(leveldb::Iterator* iter);

    /// Used in the test case.
    explicit LevelDBStoreIterator(
        std::map<std::string, std::string>::iterator iter);

    /// ++i
    void increment();

    /// --i
    void decrement();

    /**
     * \brief Returns the reference to the key and value.
     *
     * \note In the current implementation, each time calling this function,
     * a new pair of {key, value} string values are created. It might not be
     * efficient.
     */
    reference dereference() const;

    /// it != end()?
    bool equal(LevelDBStoreIterator const& other) const;

    /// Returns the key.
    std::string key() const;

    /// Returns the value.
    std::string value() const;

    /// Returns true if the current position has 'prefix'
    bool starts_with(const std::string& prefix) const;

   private:
    std::unique_ptr<leveldb::Iterator> iter_;

    std::map<std::string, std::string>::iterator test_iter_;

    /// A local copy of key and value on the current iterator position.
    value_type key_and_value_;
  };

  typedef LevelDBStoreIterator iterator;

  enum {
    DEFAULT_BUFSIZE_MB = 128,  // 128 MB
  };

  /**
   * \brief Constructs a LevelDB on the given path.
   * \param path the path of LevelDB.
   * \param bufsize_mb the size of LevelDB's buffer, in metabytes.
   */
  explicit LevelDBStore(const std::string& path,
                        int bufsize_mb = DEFAULT_BUFSIZE_MB);

  virtual ~LevelDBStore() {}

  /// Open an existing store.
  virtual Status open();

  /// Creates a LevelDBStore if it does not exist on disk.
  virtual Status create();

  /// Gets a value buffer with the given key.
  virtual Status get(const std::string& key, std::string* value);

  /// Puts a key-value pair to the leveldb.
  virtual Status put(const std::string& key, const std::string& value);

  /// Returns a key-value pair.
  virtual Status remove(const std::string& key);

  /**
   * \brief Search the leveldb store by prefix.
   * \param prefix the prefix to search the elements.
   * \return the iterator pointed to the first element that has the 'prefix'.
   *
   * It calls Seek() for leveldb's internal iterator.
   *
   * Example:
   * \code{.cpp}
   *   for (auto it = leveldb_store.search(prefix); it.starts_with(perfix);
   *        ++it) {
   *      string key = it->first;
   *      string value = it->second;
   *      process(key, value);
   *   }
   * \endcode
   */
  virtual iterator search(const std::string& prefix);

  /**
   * \brief Returns an iterator referring to the first element in the DB.
   *
   * \note The iterator is for read-only purpose. It does not support change
   * the value in the DB. You should only use the iterator for the sake of
   * scanning the store.
   */
  virtual iterator begin();

  /// Returns an iterator rerfering to the past-the-end element in the DB.
  virtual iterator end();

 protected:
  LevelDBStore() = default;

 private:
  /// Transforms leveldb::Status into vobla::Status.
  Status to_status(const leveldb::Status& l_status) const;

  std::string db_path_;

  /// LevelDB buffer size in MB.
  int bufsize_mb_;

  /// The instance of a LevelDB.
  std::unique_ptr<leveldb::DB> db_;
};

}  // namespace leveldb_store

#endif  // STORE_LEVELDB_STORE_H_
