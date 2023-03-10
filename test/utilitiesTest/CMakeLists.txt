cmake_minimum_required(VERSION 3.16.3)

#if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /ifcSearchDir \"${PROJECT_BINARY_DIR}/src/utilities\" ")
#endif()

set(UTILITIES_TEST_TARGET pdCalcUtilitiesTest)

set(UTILITIES_TEST_HEADER
    PublisherObserverTest.h
    TokenizerTest.h
    )
set(UTILITIES_TEST_SRC
    PublisherObserverTest.cpp
    TokenizerTest.cpp
)

set(CMAKE_AUTOMOC ON)

find_package(Qt${QT_V} COMPONENTS Test REQUIRED)

add_library(${UTILITIES_TEST_TARGET} SHARED ${UTILITIES_TEST_HEADER} ${UTILITIES_TEST_SRC})
target_include_directories(${UTILITIES_TEST_TARGET} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${UTILITIES_TEST_TARGET} PRIVATE Qt${QT_V}::Test)

if(WIN32)
    target_link_libraries(${UTILITIES_TEST_TARGET} PRIVATE pdCalcUtilities)
endif()

set_target_properties(${UTILITIES_TEST_TARGET} PROPERTIES VERSION ${VERSION_MAJOR}.${VERSION_MINOR})
