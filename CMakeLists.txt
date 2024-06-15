cmake_minimum_required(VERSION 3.25.2)
project(project)

set(CMAKE_CXX_STANDARD 14)

# Установка пути к локально распакованному GoogleTest
set(GOOGLETEST_ROOT "${CMAKE_SOURCE_DIR}/external/googletest-1.14.0")

add_subdirectory(${GOOGLETEST_ROOT} googletest)

#было до этого
include(CTest)
enable_testing()

include_directories(.)

add_executable(proj main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
#до этого места

# Add source files and headers
add_executable(
        project
        main.cpp
        dixotomia.cpp
        dixotomia.h
        gold_sechenie.cpp
        gold_sechenie.h
        perebor.cpp
        perebor.h
)

target_include_directories(project PRIVATE ${GTKMM_INCLUDE_DIRS} ${GOOGLETEST_ROOT}/googletest/include)
target_link_directories(project PRIVATE ${GTKMM_LIBRARY_DIRS})
target_link_libraries(project PRIVATE gtest gtest_main ${GTKMM_LIBRARIES})

# Add test files
add_executable(
        AllTests
        main.cpp
        dixotomia.cpp
        dixotomia.h
        gold_sechenie.cpp
        gold_sechenie.h
        perebor.cpp
        perebor.h
        tests/dixotomia_tests.cpp
        tests/gold_sechenie_tests.cpp
        tests/perebor_tests.cpp
)

target_include_directories(AllTests PRIVATE ${GTKMM_INCLUDE_DIRS} ${GOOGLETEST_ROOT}/googletest/include)
target_link_directories(AllTests PRIVATE ${GTKMM_LIBRARY_DIRS})
target_link_libraries(AllTests PRIVATE gtest gmock gtest_main ${GTKMM_LIBRARIES})

# Включение тестирования и добавление тестов
enable_testing()
add_test(NAME AllTests COMMAND AllTests)

