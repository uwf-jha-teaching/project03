#include "../filesystem.hpp"
#include "catch/catch.hpp"

TEST_CASE("Test creating a file system") {
  FileSystem fs;
  CHECK("/root" == fs.pwd());
  CHECK("" == fs.ls());
}

TEST_CASE("Test touch and mkdir") {
  FileSystem fs;
  CHECK("file file1 created successfully" == fs.touch("file1"));
  CHECK("Error: file1 exists" == fs.touch("file1"));
  CHECK("file file2 created successfully" == fs.touch("file2"));
  CHECK("directory dir1 created successfully" == fs.mkdir("dir1"));
  CHECK("Error: dir1 exists" == fs.mkdir("dir1"));
  CHECK("Error: dir1 exists" == fs.touch("dir1"));
  CHECK("f file1\nf file2\nd dir1\n" == fs.ls());
  CHECK("/root" == fs.pwd());
}
