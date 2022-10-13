cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(LoginSystem VERSION 1.0.0)

set(SRC_FILES src/manager.cpp src/user.cpp)

# ------ target executable: ${PROJECT_NAME} ------
add_executable(${PROJECT_NAME} src/main.cpp ${SRC_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC inc)

# ------ target executable: tester ------
add_library(mainLib STATIC ${SRC_FILES})
add_executable(tester tests/tests.cpp)
target_link_libraries(tester PRIVATE mainLib gtest_main gmock_main)

# -------- GTest --------
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
    FetchContent_Populate(googletest)
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BUILD_DIR})
endif()