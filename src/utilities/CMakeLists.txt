cmake_minimum_required(VERSION 3.16.3)

set(UTILITIES_HEADER Exception.h
               Observer.h
               Publisher.h
               #Tokenizer.h
               #Utilities.h
               )
			   
set(UTILITIES_SRC Exception.cpp
               Observer.cpp
               Publisher.cpp
               #Tokenizer.cpp
               #Utilities.cpp
               )


add_library(pdCalcUtilities SHARED ${UTILITIES_HEADER} ${UTILITIES_SRC})
set_target_properties(pdCalcUtilities PROPERTIES VERSION ${VERSION_MAJOR}.${VERSION_MINOR})
