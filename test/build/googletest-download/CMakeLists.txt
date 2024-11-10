# test/googletest-download/CMakeLists.txt.in
cmake_minimum_required(VERSION 3.10)

project(googletest-download NONE)

include(ExternalProject)
ExternalProject_Add(googletest
  GIT_REPOSITORY    https://github.com/google/googletest.git
  GIT_TAG           release-1.11.0
  SOURCE_DIR        "/home/phil/Desktop/powder_toy_godot/test/build/googletest-src"
  BINARY_DIR        "/home/phil/Desktop/powder_toy_godot/test/build/googletest-build"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
)
