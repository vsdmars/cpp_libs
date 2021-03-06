find_package(TBB REQUIRED)
find_package(GTest REQUIRED)
find_package(benchmark REQUIRED) # benchmark::benchmark
include(GoogleTest)

SET(COMPILE_OPTION -g -Wall -Wconversion -Wdouble-promotion -Weffc++ -Wextra -Wfloat-equal -Wformat=2 -Wno-error=unused-variable -Wnull-dereference -Wold-style-cast -Wpedantic -Wshadow -Wuninitialized -Wunreachable-code -Wredundant-move -Wpessimizing-move)

# enable ASAN
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-omit-frame-pointer -fsanitize=address")
set (CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -fno-omit-frame-pointer -fsanitize=address")

# -- ClockLRUCache unit test --
SET(ClockLRUCACHE_TEST_SRC "ClockLRUcacheTest.cc")
SET(ClockLRUCACHE_TEST clock_lruc_test)
add_executable(${ClockLRUCACHE_TEST} ${ClockLRUCACHE_TEST_SRC})

# compile/link options
target_compile_features(${ClockLRUCACHE_TEST} PRIVATE cxx_std_17)
target_compile_options(${ClockLRUCACHE_TEST} PRIVATE ${COMPILE_OPTION})

target_include_directories(${ClockLRUCACHE_TEST} PRIVATE "${CMAKE_SOURCE_DIR}/include" ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${ClockLRUCACHE_TEST} PRIVATE TBB::tbb)
target_link_libraries(${ClockLRUCACHE_TEST} PRIVATE GTest::gtest_main)
# gtest_discover_tests(${LRUCACHE_TESU})
add_test(NAME clock_lrucache_unit_test COMMAND clock_lruc_test)

# -- ClockLRUCache benchmark test --
SET(CLOCKLRUCACHE_BENCH clock_lruc_benchmark)
SET(CLOCKLRUCACHE_BENCH_SRC "clock_lrucache_bench.cc")
add_executable(${CLOCKLRUCACHE_BENCH} ${CLOCKLRUCACHE_BENCH_SRC})

# compile/link options
target_compile_features(${CLOCKLRUCACHE_BENCH} PRIVATE cxx_std_17)
target_compile_options(${CLOCKLRUCACHE_BENCH} PRIVATE ${COMPILE_OPTION})

target_include_directories(${CLOCKLRUCACHE_BENCH} PRIVATE "${CMAKE_SOURCE_DIR}/include" ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${CLOCKLRUCACHE_BENCH} PRIVATE benchmark::benchmark)

# -- LRUCache unit test --
SET(LRUCACHE_TEST_SRC "LRUcacheTest.cc")
SET(LRUCACHE_TEST lruc_test)

add_executable(${LRUCACHE_TEST} ${LRUCACHE_TEST_SRC})

# compile/link options
target_compile_features(${LRUCACHE_TEST} PRIVATE cxx_std_17)
target_compile_options(${LRUCACHE_TEST} PRIVATE ${COMPILE_OPTION})

target_include_directories(${LRUCACHE_TEST} PRIVATE "${CMAKE_SOURCE_DIR}/include" ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${LRUCACHE_TEST} PRIVATE TBB::tbb)
target_link_libraries(${LRUCACHE_TEST} PRIVATE GTest::gtest_main)
# gtest_discover_tests(${LRUCACHE_TESU})
add_test(NAME lrucache_unit_test COMMAND lruc_test)


# -- Scale-LRUCache unit test --
SET(SCALE_LRUCACHE_TEST scale_lruc_test)
SET(SCALE_LRUCACHE_TEST_SRC "ScaleLRUcacheTest.cc")
add_executable(${SCALE_LRUCACHE_TEST} ${SCALE_LRUCACHE_TEST_SRC})

# compile/link options
target_compile_features(${SCALE_LRUCACHE_TEST} PRIVATE cxx_std_17)
target_compile_options(${SCALE_LRUCACHE_TEST} PRIVATE ${COMPILE_OPTION})

target_include_directories(${SCALE_LRUCACHE_TEST} PRIVATE "${CMAKE_SOURCE_DIR}/include" ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${SCALE_LRUCACHE_TEST} PRIVATE TBB::tbb)
target_link_libraries(${SCALE_LRUCACHE_TEST} PRIVATE GTest::gtest_main)
# gtest_discover_tests(${SCALE_LRUCACHE_TEST})
add_test(NAME scale_lrucache_unit_test COMMAND scale_lruc_test)


# -- LRUCache benchmark test --
SET(LRUCACHE_BENCH lruc_benchmark)
SET(LRUCACHE_BENCH_SRC "lrucache_bench.cc")
add_executable(${LRUCACHE_BENCH} ${LRUCACHE_BENCH_SRC})

# compile/link options
target_compile_features(${LRUCACHE_BENCH} PRIVATE cxx_std_17)
target_compile_options(${LRUCACHE_BENCH} PRIVATE ${COMPILE_OPTION})

target_include_directories(${LRUCACHE_BENCH} PRIVATE "${CMAKE_SOURCE_DIR}/include" ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${LRUCACHE_BENCH} PRIVATE TBB::tbb)
target_link_libraries(${LRUCACHE_BENCH} PRIVATE benchmark::benchmark)


# -- ScalableLRUCache benchmark test --
SET(SCALE_LRUCACHE_BENCH scale_lruc_benchmark)
SET(SCALABLE_LRUCACHE_BENCH_SRC "scalable_lrucache_bench.cc")
add_executable(${SCALE_LRUCACHE_BENCH} ${SCALABLE_LRUCACHE_BENCH_SRC})

# compile/link options
target_compile_features(${SCALE_LRUCACHE_BENCH} PRIVATE cxx_std_17)
target_compile_options(${SCALE_LRUCACHE_BENCH} PRIVATE ${COMPILE_OPTION})

target_include_directories(${SCALE_LRUCACHE_BENCH} PRIVATE "${CMAKE_SOURCE_DIR}/include" ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${SCALE_LRUCACHE_BENCH} PRIVATE TBB::tbb)
target_link_libraries(${SCALE_LRUCACHE_BENCH} PRIVATE benchmark::benchmark)


# -- setup binary location --
set_property(TARGET ${ClockLRUCACHE_TEST}
    PROPERTY RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/test_bin")

set_property(TARGET ${CLOCKLRUCACHE_BENCH}
    PROPERTY RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/test_bin")

set_property(TARGET ${LRUCACHE_TEST}
    PROPERTY RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/test_bin")

set_property(TARGET ${SCALE_LRUCACHE_TEST}
    PROPERTY RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/test_bin")

set_property(TARGET ${LRUCACHE_BENCH}
    PROPERTY RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/test_bin")

set_property(TARGET ${SCALE_LRUCACHE_BENCH}
    PROPERTY RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/test_bin")
