cmake -B .BUILD -S . \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
    -DCMAKE_TOOLCHAIN_FILE=./I386-TOOLCHAIN.CMAKE

cp .BUILD/compile_commands.json .
cmake --build .BUILD
