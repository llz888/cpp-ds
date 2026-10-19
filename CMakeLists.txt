cmake_minimum_required(VERSION 3.16)
project(cpp-ds CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 警告全开（你一直用的 gxx 就是这个）
add_compile_options(-Wall -Wextra -g)

# 想要 ASan/UBSan：加 -DENABLE_SANITIZERS=ON
option(ENABLE_SANITIZERS "开启 ASan/UBSan" OFF)
if(ENABLE_SANITIZERS)
    add_compile_options(-fsanitize=address,undefined)
    add_link_options(-fsanitize=address,undefined)
endif()

find_package(Threads REQUIRED)

# ── 每个容器一个可执行文件 ──
add_executable(myvector_demo  myvector/main.cpp)

add_executable(uniqueptr_demo smartptr/main.cpp)
add_executable(sharedptr_demo smartptr/shared_test.cpp)

add_executable(pool_test      pool/pool_test.cpp)
add_executable(pool_use       pool/pool_use.cpp)

add_executable(queue_test     queue/queue_test.cpp)
target_link_libraries(queue_test PRIVATE Threads::Threads)
add_executable(myvector_test   myvector/myvector_test.cpp)
add_executable(smartptr_test   smartptr/smartptr_test.cpp)
add_executable(threadpool_test threadpool/threadpool_test.cpp)
target_link_libraries(threadpool_test PRIVATE Threads::Threads)