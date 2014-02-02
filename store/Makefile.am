#vim: ts=8:st=8:noexpandtab
# Makefile.am for LevelDBStore.

noinst_LIBRARIES = libleveldb_store.a
libleveldb_store_a_SOURCES = \
  leveldb_store.h leveldb_store.cpp \
  status.h status.cpp

TESTS = leveldb_store_test

check_PROGRAMS = $(TESTS)

LDADD = @top_srcdir@/lib/vobla/vobla/libvobla.la \
	-lgtest_main -lgtest -lgmock

leveldb_store_test_SOURCES = leveldb_store_test.cpp
leveldb_store_test_LDADD = \
  libleveldb_store.a \
  @top_srcdir@/lib/vobla/vobla/libvobla.la \
  -lgtest_main -lgtest -lgmock
