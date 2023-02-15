cmake_minimum_required(VERSION 3.16.3)

set(DRIVER_TARGET testPdCalc)

add_executable(${DRIVER_TARGET} main.cpp)
set_target_properties(${DRIVER_TARGET} PROPERTIES VERSION ${VERSION_MAJOR}.${VERSION_MINOR})

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set_target_properties(${DRIVER_TARGET} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${LIBRARY_OUTPUT_PATH}/$<CONFIG>")
endif()

set(DRIVER_LIBS pdCalcUtilities
                pdCalcBackend
                pdCalcBackendTest
                pdCalcUtilitiesTest)

find_package(Qt${QT_V} COMPONENTS Core Widgets Test REQUIRED)
link_directories(${CMAKE_BINARY_DIR}/lib)
target_link_libraries(${DRIVER_TARGET} ${DRIVER_LIBS} Qt${QT_V}::Core Qt${QT_V}::Widgets Qt${QT_V}::Test)
