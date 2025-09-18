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

# SqList
add_executable(test_sq_list test/test_sq_list.cpp)
target_link_libraries(test_sq_list gtest_main)
add_test(NAME test_sq_list COMMAND test_sq_list)
target_include_directories(test_sq_list PRIVATE ${PROJECT_SOURCE_DIR}/include)

# LinkList
add_executable(test_link_list test/test_link_list.cpp)
target_link_libraries(test_link_list gtest_main)
add_test(NAME test_link_list COMMAND test_link_list)
target_include_directories(test_link_list PRIVATE ${PROJECT_SOURCE_DIR}/include)

# DLinkList
add_executable(test_dlink_list test/test_dlink_list.cpp)
target_link_libraries(test_dlink_list gtest_main)
add_test(NAME test_dlink_list COMMAND test_dlink_list)
target_include_directories(test_dlink_list PRIVATE ${PROJECT_SOURCE_DIR}/include)

# SLinkList
add_executable(test_slink_list test/test_slink_list.cpp)
target_link_libraries(test_slink_list gtest_main)
add_test(NAME test_slink_list COMMAND test_slink_list)
target_include_directories(test_slink_list PRIVATE ${PROJECT_SOURCE_DIR}/include)

# SqStack
add_executable(test_sq_stack test/test_sq_stack.cpp)
target_link_libraries(test_sq_stack gtest_main)
add_test(NAME test_sq_stack COMMAND test_sq_stack)
target_include_directories(test_sq_stack PRIVATE ${PROJECT_SOURCE_DIR}/include)

# SqQueue
add_executable(test_sq_queue test/test_sq_queue.cpp)
target_link_libraries(test_sq_queue gtest_main)
add_test(NAME test_sq_queue COMMAND test_sq_queue)
target_include_directories(test_sq_queue PRIVATE ${PROJECT_SOURCE_DIR}/include)

# HString
add_executable(test_hstring test/test_hstring.cpp)
target_link_libraries(test_hstring gtest_main)
add_test(NAME test_hstring COMMAND test_hstring)
target_include_directories(test_hstring PRIVATE ${PROJECT_SOURCE_DIR}/include)

# BinaryTree
add_executable(test_binary_tree test/test_binary_tree.cpp)
target_link_libraries(test_binary_tree gtest_main)
add_test(NAME test_binary_tree COMMAND test_binary_tree)
target_include_directories(test_binary_tree PRIVATE ${PROJECT_SOURCE_DIR}/include)

if (CMAKE_VERSION VERSION_GREATER 3.12)
    set_property(TARGET test_sq_list PROPERTY CXX_STANDARD 11)
    set_property(TARGET test_link_list PROPERTY CXX_STANDARD 11)
    set_property(TARGET test_dlink_list PROPERTY CXX_STANDARD 11)
    set_property(TARGET test_slink_list PROPERTY CXX_STANDARD 11)
    set_property(TARGET test_sq_stack PROPERTY CXX_STANDARD 11)
    set_property(TARGET test_sq_queue PROPERTY CXX_STANDARD 11)
    set_property(TARGET test_hstring PROPERTY CXX_STANDARD 11)
    set_property(TARGET test_binary_tree PROPERTY CXX_STANDARD 11)
endif ()