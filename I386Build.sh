rm .Build/JSK.IMG
rm .Build/Kernel.bin

cmake -B .Build -S . \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
    -DCMAKE_TOOLCHAIN_FILE=./CMake/I386Toolchain.cmake \

cp .Build/compile_commands.json .
cmake --build .Build
