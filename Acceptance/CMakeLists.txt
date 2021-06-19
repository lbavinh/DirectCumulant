cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(AcceptanceCorrection)


# find_package(Git)

list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
find_package(ROOT REQUIRED COMPONENTS MathCore RIO Hist Tree Net EG MathMore)
include(${ROOT_USE_FILE})
add_definitions(${ROOT_CXX_FLAGS})

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall")

set(ACCCOR_INCLUDE_DIRECTORIES
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${ROOT_INLCUDE_DIRS}
)

include_directories(${ACCCOR_INCLUDE_DIRECTORIES})

set(FLOWANA_INCLUDE_LIBRARIES
  ${ROOT_LIBRARIES}
)

set(FlowANA_h_files
  "${CMAKE_CURRENT_SOURCE_DIR}/FlowANA.h"
)

set(FlowANA_cxx_files
  "${CMAKE_CURRENT_SOURCE_DIR}/FlowANA.C"
)

set(FlowANA_LinkDef
	"${CMAKE_CURRENT_SOURCE_DIR}/FlowANA.LinkDef.h"
)

#---Generate dictionary
ROOT_GENERATE_DICTIONARY(G__FlowANA
  ${FlowANA_h_files}
  LINKDEF ${FlowANA_LinkDef}
)

#---Compile library
add_library(FlowANA SHARED ${FlowANA_cxx_files} G__FlowANA.cxx)
target_link_libraries(FlowANA ${FLOWANA_INCLUDE_LIBRARIES})

set(ACCCOR_INCLUDE_LIBRARIES
  FlowANA
  ${ROOT_LIBRARIES}
)

add_executable(AccCor calculateFlow.C)
target_link_libraries(AccCor ${ACCCOR_INCLUDE_LIBRARIES})
