#!/bin/sh
#  Copyright 2014 (c) Lei Xu <eddyxu@gmail.com>
#
#  Licensed under the Apache License, Version 2.0 (the "License");
#  you may not use this file except in compliance with the License.
#  You may obtain a copy of the License at
#
#  http://www.apache.org/licenses/LICENSE-2.0
#
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.
#
# Regenerate configure and Makefiles

libtoolize
autoheader
aclocal -I m4 --install
autoconf
automake --foreign --add-missing --force-missing --copy

mkdir -p lib
cd lib
if [ ! -f gmock.zip ]; then
	wget -O gmock.zip https://googlemock.googlecode.com/files/gmock-1.7.0.zip
	unzip gmock.zip
	cd gmock-*
	./configure && make
fi
