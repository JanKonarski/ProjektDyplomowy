cmake_minimum_required(VERSION 3.10)

project(OCLEncrypt)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

find_package(OpenCL REQUIRED)

include_directories(${OPENCL_INCLUDE_DIR})

add_library(OCLEncrypt STATIC
    src/base.cpp
    src/caesar.cpp
    src/ctr.cpp
    src/ctr_encrypt.cpp
    src/ctr_decrypt.cpp
    src/ecb.cpp
    src/utils.cpp
)

set(CAESAR_TEST caesat_test)
add_executable(${CAESAR_TEST} example/caesar_test.cpp)
set_target_properties(${CAESAR_TEST} PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(${CAESAR_TEST} OCLEncrypt OpenCL::OpenCL)

set(ECB_TEST ecb_test)
add_executable(${ECB_TEST} example/ecb_test.cpp)
set_target_properties(${ECB_TEST} PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(${ECB_TEST} OCLEncrypt OpenCL::OpenCL)

set(CTR_TEST ctr_test)
add_executable(${CTR_TEST} example/ctr_encrypt_test.cpp)
set_target_properties(${CTR_TEST} PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(${CTR_TEST} OCLEncrypt OpenCL::OpenCL)