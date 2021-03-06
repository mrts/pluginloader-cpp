CMAKE_MINIMUM_REQUIRED (VERSION 2.6)
SET (CMAKE_BACKWARDS_COMPATIBILITY 2.6)

PROJECT(pluginloader.test)

ADD_DEFINITIONS(-DUNICODE -D_UNICODE -UMBCS -U_MBCS)

FILE (GLOB SRC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
        test/[^.]*.h
        test/[^.]*.cpp)
ADD_EXECUTABLE(${PROJECT_NAME} ${SRC})

# --- libpluginloader

INCLUDE_DIRECTORIES("include")

IF(WIN32)

FILE(GLOB LIBPLUGINLOADER_SRC
	include/[^.]*.h
	src/[^.]*_windows.h
	src/[^.]*.cpp)

ELSE(WIN32)

FILE(GLOB LIBPLUGINLOADER_SRC
	include/[^.]*.h
	src/[^.]*_linux.h
	src/[^.]*.cpp)

ENDIF(WIN32)

ADD_LIBRARY(pluginloader STATIC ${LIBPLUGINLOADER_SRC})

TARGET_LINK_LIBRARIES(${PROJECT_NAME} pluginloader)

# --- platform specifics

IF(WIN32)

  ADD_DEFINITIONS("/W4")

ELSE(WIN32)

  set(CMAKE_CXX_COMPILER clang++)
  ADD_DEFINITIONS("-std=c++11 -Wall -Werror")

  TARGET_LINK_LIBRARIES(${PROJECT_NAME} "dl")

ENDIF(WIN32)
