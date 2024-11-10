mkdir build
cd build
cmake ..
make
./powder_toy_test

debug:
cmake -DCMAKE_BUILD_TYPE=Debug ..