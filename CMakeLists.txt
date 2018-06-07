cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(VER 0.0.1)
if($ENV{TRAVIS_BUILD_NUMBER})
    set(VER 0.0.$ENV{TRAVIS_BUILD_NUMBER})
endif()
project(print_ip VERSION ${VER})

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(${PROJECT_NAME}
    print_ip.h
    main.cpp)

add_executable(test_${PROJECT_NAME}
    test_${PROJECT_NAME}.cpp
    print_ip.h)

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS -Wpedantic -Wall -Wextra)

set_target_properties(test_${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
    COMPILE_OPTIONS -Wpedantic -Wall -Wextra)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT altdaedroth@gmail.com)

include(CPack)

enable_testing()

add_test(test_${PROJECT_NAME} test_${PROJECT_NAME})
