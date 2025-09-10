# CMakeList.txt: algo_ds_lib 的 CMake 项目
# 项目特定的逻辑。
#
cmake_minimum_required(VERSION 3.10)

# 如果支持，请为 MSVC 编译器启用热重载。
if (POLICY CMP0141)
    cmake_policy(SET CMP0141 NEW)
    set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT
            "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>"
    )
endif ()

project(main)

# 递归包含 include 目录下的所有子文件夹
include_directories(${PROJECT_SOURCE_DIR}/src)

# 下载并添加 GoogleTest
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(main
        test/test_sq_list.cpp
        test/test_link_list.cpp
        test/test_dlink_list.cpp
        test/test_slink_list.cpp
        test/test_sq_stack.cpp
)

target_link_libraries(main
        gtest_main
)
target_include_directories(main PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

add_test(NAME main COMMAND main)

target_include_directories(main
        PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
    set_property(TARGET main PROPERTY CXX_STANDARD 20)
endif ()