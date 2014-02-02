#vim: ts=8:st=8:noexpandtab
# Makefile.am for LevelDBStore.

noinst_LIBRARIES = libleveldb_store.a
libleveldb_store_a_SOURCES = \
  leveldb_store.h leveldb_store.cpp \
  status.h status.cpp \
  test_leveldb_store.h test_leveldb_store.cpp

TESTS = leveldb_store_test

check_PROGRAMS = $(TESTS)

leveldb_store_test_SOURCES = leveldb_store_test.cpp
leveldb_store_test_LDADD = \
  libleveldb_store.a \
  -lgtest_main -lgtest -lgmock \
  $(BOOST_FILESYSTEM_LIB) $(BOOST_SYSTEM_LIB)
