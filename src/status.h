/*
 * Copyright 2011-2014 (c) Lei Xu <eddyxu@gmail.com>
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

// Copied from https://github.com/vsfs/vobla

#ifndef STORE_STATUS_H_
#define STORE_STATUS_H_

#include <string>

namespace leveldb_store {

/**
 * \class Status "status.h"
 * \brief encapure both error code and error message.
 *
 * It provides more information with passing returning code around.
 * It is prefered to be used as return value.
 *
 * The error code 0 is for successful.
 */
class Status {
 public:
  /// Constructs a Status object from system error. The error message is
  /// obtained from strerror(2).
  static Status system_error(int errnum);

  /// The default constructor builds a success status (error_code == 0)
  Status() = default;

  /// Constructs a Status object with error code and error message.
  Status(int code, const std::string& message);

  /// Copy constructor.
  Status(const Status& rhs);

  /// Move constructor.
  Status(Status&& rhs);

  /// Explicit destructor.
  ~Status();

  /// Assign operation.
  Status& operator=(const Status& rhs);

  /// Move
  Status& operator=(Status&& rhs);

  /// Returns the error code.
  int error() const;

  /// Sets the code and message to a new value.
  void set(int code, const std::string& message);

  /// Sets the new error code.
  void set_error(int code);

  /// Returns the error message.
  const std::string& message() const;

  /// Sets the new error message.
  void set_message(const std::string& message);

  /// Tests whether the error code is zero.
  bool ok() const;

  /// A static Status object to represent the OK status.
  static const Status OK;

  /// Returns true if two status objects have same error numbers and messages.
  bool operator==(const Status &rhs) const;

  /// Returns true if two status objects are not equal.
  bool operator!=(const Status &rhs) const {
    return !(*this == rhs);
  }

 private:
  /// Returning code. 0 for success.
  int code_ = 0;

  /// Error message.
  std::string message_;
};

}  // namespace leveldb_store

#endif  // STORE_STATUS_H_
