CMAKE_MINIMUM_REQUIRED (VERSION 3.20)

SET (CMAKE_SYSTEM_NAME             Generic)
SET (CMAKE_SYSTEM_PROCESSOR        i386)
SET (CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

SET (CMAKE_C_COMPILER clang)
SET (CMAKE_C_FLAGS    "-target i386-unknown-none -ffreestanding")

# Somehow this failed by not finding clang, so i'll just comment out
# SET (CMAKE_OBJC_COMPILER clang)
SET (CMAKE_OBJC_FLAGS    "-target i386-unknown-none -ffreestanding")

SET (CMAKE_CXX_COMPILER clang++)
SET (CMAKE_CXX_FLAGS    "-target i386-unknown-none -ffreestanding -fno-exceptions -fno-rtti")

SET (CMAKE_ASM_NASM_COMPILER      nasm)
SET (CMAKE_ASM_NASM_OBJECT_FORMAT elf32)
SET (CMAKE_ASM_NASM_FLAGS         "-f elf32")
