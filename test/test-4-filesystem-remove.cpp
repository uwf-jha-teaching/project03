#include "../filesystem.hpp"
#include "catch/catch.hpp"

TEST_CASE("Test rm from empty dir") {
  FileSystem fs;
  CHECK("No such file or directory" == fs.rm("file1"));
}

TEST_CASE("Test rm child that has siblings") {
  FileSystem fs;
  fs.mkdir("dir1");   // dir1 is child
  fs.touch("file1");  // file1 is sibling
  CHECK("dir1 removed successfully" == fs.rm("dir1"));
  CHECK("f file1\n" == fs.ls());
}

TEST_CASE("Test rm of a child dir with files and dirs inside") {
  FileSystem fs;

  fs.mkdir("dir1");
  fs.touch("file1");
  fs.mkdir("dir2");
  fs.cd("dir2");
  CHECK("/root/dir2" == fs.pwd());

  fs.mkdir("dir3");  // going a bit deeper, dir3 is a child
  fs.touch("file3");
  fs.cd("dir3");
  CHECK("/root/dir2/dir3" == fs.pwd());

  fs.touch("file1");
  fs.touch("file2");
  fs.mkdir("dir1");
  fs.cd("..");  // dir3 has some files now. Let's delete it
  CHECK("dir3 removed successfully" == fs.rm("dir3"));
  CHECK("f file3\n" == fs.ls());
}
