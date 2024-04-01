cmake_minimum_required(VERSION 3.22)
project(external_tape_sort)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -g3 -Wextra")

option(BUILD_TEST BOOL ON)
option(BUILD_MAIN BOOL ON)


if(BUILD_TEST) 

  include(FetchContent)
  FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
  )
  FetchContent_MakeAvailable(googletest)
  
  enable_testing()
  
  
  add_executable(
    external_sort_test
    src/external_sort_test.cpp
  )
  
  target_link_libraries(
    external_sort_test
    GTest::gtest_main
  )

  target_include_directories(external_sort_test PUBLIC include)
  
  include(GoogleTest)
  gtest_discover_tests(external_sort_test)  

endif()

if (BUILD_MAIN) 
  add_executable(
    main
    src/main.cpp
    src/external_sort.cpp
    src/tape.cpp
  )

  target_include_directories(main PUBLIC include)


endif()