cmake_minimum_required(VERSION 3.9)

if(NOT CMAKE_BUILD_TYPE)
    message("-- CMAKE_BUILD_TYPE is not set. Defaulting to Release.")
    # Must be set before a toolchain file is loaded by project() command.
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build type: Debug or Release." FORCE)
endif()

if(NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 14 CACHE STRING "C++ standard version (must be 14 or later)." FORCE)
endif()
if(CMAKE_CXX_STANDARD MATCHES "^(98|11)$")
    message(FATAL_ERROR "CMAKE_CXX_STANDARD must be 14 or later.")
endif()
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Polatory CXX)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include(polatory_common_functions)

find_package(Boost 1.67.0 REQUIRED)

option(USE_PREBUILT_BOOST "Use prebuilt Boost libraries specified manually. This option takes effect only on MSVC.")

if(UNIX)
    if(NOT CMAKE_CXX_COMPILER_ID MATCHES "^(Clang|GNU)$")
        message(FATAL_ERROR "Not supported compiler.")
    endif()

    set(MKL_ROOT /opt/intel/mkl CACHE PATH "Path to mkl")
    set(MKL_INCLUDE_DIR "${MKL_ROOT}/include")
    set(MKL_LIB_DIR "${MKL_ROOT}/lib/intel64")
elseif(MSVC)
    if(NOT CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        message(FATAL_ERROR "Not supported compiler.")
    endif()

    set(_PF86 "ProgramFiles(x86)")
    file(TO_CMAKE_PATH "$ENV{${_PF86}}" _PROG_FILES_X86)

    if("$ENV{APPVEYOR}" STREQUAL "True")
        set(MKL_ROOT "$ENV{CONDA_DIR}/Library")
        set(MKL_DLL_DIR "${MKL_ROOT}/bin")
        set(MKL_INCLUDE_DIR "${MKL_ROOT}/include")
        set(MKL_LIB_DIR "${MKL_ROOT}/lib")
    else()
        set(MKL_ROOT "${_PROG_FILES_X86}/IntelSWTools/compilers_and_libraries/windows/mkl" CACHE PATH "Path to mkl")
        set(MKL_DLL_DIR "${MKL_ROOT}/../redist/intel64/mkl")
        set(MKL_INCLUDE_DIR "${MKL_ROOT}/include")
        set(MKL_LIB_DIR "${MKL_ROOT}/lib/intel64")
    endif()

    set(VCPKG_ROOT "${_VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}")
    set(VCPKG_LIB_DIR "${VCPKG_ROOT}$<$<CONFIG:Debug>:/debug>/lib")
    set(VCPKG_INCLUDE_DIR "${VCPKG_ROOT}/include")

    if(USE_PREBUILT_BOOST)
        if("${Boost_INCLUDE_DIR}" STREQUAL "${VCPKG_INCLUDE_DIR}")
            message(FATAL_ERROR "Boost libraries from vcpkg are detected. Turn off USE_PREBUILT_BOOST.")
        endif()
    endif()

    set(POLATORY_DLLS
        ${MKL_DLL_DIR}/mkl_avx.dll
        ${MKL_DLL_DIR}/mkl_avx2.dll
        ${MKL_DLL_DIR}/mkl_avx512.dll
        ${MKL_DLL_DIR}/mkl_core.dll
        ${MKL_DLL_DIR}/mkl_def.dll
        ${MKL_DLL_DIR}/mkl_mc.dll
        ${MKL_DLL_DIR}/mkl_mc3.dll
        ${MKL_DLL_DIR}/mkl_sequential.dll
    )
else()
    message(FATAL_ERROR "Not supported system.")
endif()

add_subdirectory(benchmark)
add_subdirectory(examples)
add_subdirectory(src)

enable_testing()
add_subdirectory(test)
