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

#include <cstring>
#include <string>
#include <utility>
#include "status.h"

using std::string;

namespace leveldb_store {

const Status Status::OK = Status();

Status Status::system_error(int errnum) {
  return Status(-errnum, strerror(errnum));
}

Status::Status(int code, const string& message) : code_(code),
    message_(message) {
}

Status::Status(const Status& rhs) {
  *this = rhs;
}

Status::Status(Status&& rhs) {
  if (this != &rhs) {
    code_ = rhs.code_;
    rhs.code_ = 0;
    message_ = std::move(rhs.message_);
  }
}

Status::~Status() {
}

Status& Status::operator=(const Status& rhs) {
  code_ = rhs.code_;
  message_ = rhs.message_;
  return *this;
}

Status& Status::operator=(Status&& rhs) {
  if (this != &rhs) {
    code_ = rhs.code_;
    rhs.code_ = 0;
    message_ = std::move(rhs.message_);
  }
  return *this;
}

void Status::set(int code, const string& new_msg) {
  code_ = code;
  message_ = new_msg;
}

void Status::set_error(int code) {
  code_ = code;
}

int Status::error() const {
  return code_;
}

void Status::set_message(const string& new_msg) {
  message_ = new_msg;
}

const string& Status::message() const {
  return message_;
}

bool Status::ok() const {
  return code_ == 0;
}

bool Status::operator==(const Status &rhs) const {
  return code_ == rhs.code_ && message_ == rhs.message_;
}

}  // namespace leveldb_store
