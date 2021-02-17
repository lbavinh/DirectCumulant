cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(FlowAMPT)


find_package(Git)

list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
find_package(ROOT REQUIRED COMPONENTS MathCore RIO Hist Tree Net EG MathMore)
include(${ROOT_USE_FILE})
add_definitions(${ROOT_CXX_FLAGS})
add_subdirectory(FlowAnalysis)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall")

set(FLOWAMPT_INCLUDE_DIRECTORIES
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/FlowAnalysis
  ${ROOT_INLCUDE_DIRS}
)

include_directories(${FLOWAMPT_INCLUDE_DIRECTORIES})

set(FLOWAMPT_INCLUDE_LIBRARIES
  FlowAnalysis
  ${ROOT_LIBRARIES}
)

add_executable(FlowAMPT main.cpp)
target_link_libraries(FlowAMPT ${FLOWAMPT_INCLUDE_LIBRARIES})
