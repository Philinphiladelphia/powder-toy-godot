# test/CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(powder_toy_test)


# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
                 ${CMAKE_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

# Add the library from the top-level src directory
add_library(powder_toy_interface ${CMAKE_SOURCE_DIR}/../src/powder_toy_interface.cpp)

# Include the top-level src directory
include_directories(${CMAKE_SOURCE_DIR}/../src)
include_directories(${CMAKE_SOURCE_DIR}/../include/powder_toy)
include_directories(${CMAKE_SOURCE_DIR}/../include/json)

# Add the directory containing libpowder.so to the linker search path
link_directories(${CMAKE_SOURCE_DIR}/../lib)

# Create an imported target for the shared library
add_library(libpowder SHARED IMPORTED)
set_target_properties(libpowder PROPERTIES
    IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/../lib/libpowder.so
)

# Now simply link against gtest or gtest_main as needed. Eg
add_executable(powder_toy_test src/powder_toy_test.cpp)
target_link_libraries(powder_toy_test libpowder powder_toy_interface gtest_main jsoncpp) # libpowder
add_test(NAME powder_toy_test COMMAND powder_toy_test)



# right now, it looks like if libpowder is even imported, 
# it instantly runs on startup without allowing anything else. 
# I think maybe it has main() defined somewhere in there even though it's a library.
# Maybe let's try to stop that