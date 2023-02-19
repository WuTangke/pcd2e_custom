cmake_minimum_required(VERSION 3.16.3)

set(UTILITIES_HEADER Exception.h
               Observer.h
               Publisher.h
               Tokenizer.h
               Utilities.h
               )
			   
set(UTILITIES_SRC
               Observer.cpp
               Publisher.cpp
               Tokenizer.cpp
               )


add_library(pdCalcUtilities SHARED ${UTILITIES_HEADER} ${UTILITIES_SRC})
target_include_directories(pdCalcUtilities INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(pdCalcUtilities PROPERTIES VERSION ${VERSION_MAJOR}.${VERSION_MINOR})
