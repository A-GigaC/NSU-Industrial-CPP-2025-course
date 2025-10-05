# Create build dir
rm -r build
mkdir build
cd build
# Setup depedencies from conan
conan install .. --output-folder=. --build=missing
cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
cmake --build . --target=docs
cmake --build . --target=format
cmake --build .
cmake --install . --prefix ./install
# Run tests
ctest -V -j4