project(ogl CXX C)

cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

# Set application to GUI type for Win32 and MacOS
if(WIN32)
  set(GUI_TYPE WIN32)
endif(WIN32)
if(APPLE)
  set(GUI_TYPE MACOSX_BUNDLE)
endif(APPLE)

# global variables
set(INCLUDE_DIR
  ${CMAKE_SOURCE_DIR}/include
)

set(TARGET_DIR
  ${CMAKE_BINARY_DIR}/target
)

set(LIB_DIR
  ${CMAKE_BINARY_DIR}/lib
)

set(APPLICATION_NAME ${PROJECT_NAME})

# where to look first for cmake modules, before ${CMAKE_ROOT}/Modules/ is checked
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/Modules)

# disallow in-source build
include(MacroEnsureOutOfSourceBuild)
macro_ensure_out_of_source_build("${PROJECT_NAME} requires an out of source build. Please create a separate build directory and run 'cmake /path/to/${PROJECT_NAME} [options]' there.")

# Define output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${TARGET_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LIB_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${LIB_DIR})

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(
  ${INCLUDE_DIR}
  ${SDL2_INCLUDE_DIR}
  ${OPENGL_INCLUDE_DIRS}
)

link_libraries(
  ${SDL2_LIBRARY}
  ${OPENGL_LIBRARIES}
)

set(SOURCES src/main.cpp)
add_executable(${APPLICATION_NAME} ${GUI_TYPE} ${SOURCES})

set_property(TARGET ${APPLICATION_NAME} PROPERTY CXX_STANDARD 11)
set_property(TARGET ${APPLICATION_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
