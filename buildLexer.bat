rmdir /s /q build
mkdir build && cd build
cmake .. -G "NMake Makefiles"
cmake --build .
BakScript