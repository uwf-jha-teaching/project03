#include "../filesystem.hpp"
#include "catch/catch.hpp"

TEST_CASE("Test changing directories") {
  FileSystem fs;
  fs.mkdir("dir");
  CHECK("/root/dir" == fs.cd("dir"));
  CHECK("/root/dir" == fs.pwd());
  CHECK("" == fs.ls());
  CHECK("/root" == fs.cd(".."));
  CHECK("/root" == fs.pwd());
  CHECK("can't change to directory .." == fs.cd(".."));

  fs.touch("file");
  CHECK("file: is not a directory" == fs.cd("file"));
  CHECK("dir2: no such directory" == fs.cd("dir2"));

  fs.cd("dir");
  fs.mkdir("dir2");
  fs.mkdir("dir3");
  CHECK("/root/dir/dir2" == fs.cd("dir2"));
  CHECK("" == fs.ls());
  CHECK("/root/dir" == fs.cd(".."));
  CHECK("/root/dir/dir3" == fs.cd("dir3"));
}

TEST_CASE("Test mv") {
  FileSystem fs;

  fs.touch("file1");
  CHECK("file/dir renamed successfully" == fs.mv("file1", "file2"));
  CHECK("f file2\n" == fs.ls());
  CHECK("file not found" == fs.mv("file3", "file4"));
}
