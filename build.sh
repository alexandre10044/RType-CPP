rm -rf build
mkdir build
cd build
conan install .. --build=missing
cmake .. -G 'Unix Makefiles'
cmake --build .
cp r-type* ../
cd ..
rm ./build -rf