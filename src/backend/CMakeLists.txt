cmake_minimum_required(VERSION 3.16.3)

set(BACKEND_TARGET pdCalcBackend)

set(BACKEND_HEADER
    Stack.h
 )
 
set(BACKEND_SRC
    Stack.cpp
 )
 
add_library(${BACKEND_TARGET} SHARED ${BACKEND_HEADER} ${BACKEND_SRC})
set_target_properties(${BACKEND_TARGET} PROPERTIES VERSION ${VERSION_MAJOR}.${VERSION_MINOR})

if(UNIX)
    target_link_libraries(${BACKEND_TARGET} dl)
elseif(WIN32)
    target_link_libraries(${BACKEND_TARGET} pdCalcUtilities)
endif()
