cmake_minimum_required(VERSION 3.16.3)

set(BACKEND_TARGET pdCalcBackend)

set(BACKEND_HEADER
    Stack.h
    Command.h
    CommandDispatcher.h
    CommandManager.h
    CoreCommands.h
    UserInterface.h
    CommandInterpreter.h
    CommandFactory.h
    StoredProcedure.h
    AppObservers.h
 )
 
set(BACKEND_SRC
    Stack.cpp
    Command.cpp
    CommandDispatcher.cpp
    CommandManager.cpp
    CommandInterpreter.cpp
    CommandFactory.cpp
    StoredProcedure.cpp
    AppObservers.cpp
 )
 
add_library(${BACKEND_TARGET} SHARED ${BACKEND_HEADER} ${BACKEND_SRC})
target_include_directories(${BACKEND_TARGET} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(${BACKEND_TARGET} PROPERTIES VERSION ${VERSION_MAJOR}.${VERSION_MINOR})

if(UNIX)
    target_link_libraries(${BACKEND_TARGET} dl)
elseif(WIN32)
    target_link_libraries(${BACKEND_TARGET} pdCalcUtilities)
endif()
