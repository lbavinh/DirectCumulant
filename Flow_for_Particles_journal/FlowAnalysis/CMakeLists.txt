set(FLOWANALYSIS_INCLUDE_DIRECTORIES
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${ROOT_INLCUDE_DIRS}
)

include_directories(${FLOWANALYSIS_INCLUDE_DIRECTORIES})

set(FLOWANALYSIS_INCLUDE_LIBRARIES
  ${ROOT_LIBRARIES}
)

set(FlowAnalysis_h_files
  "${CMAKE_CURRENT_SOURCE_DIR}/QVector.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/FlowAnalysisWithEtaSubEventPlane.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/FlowAnalysisWithThreeEtaSubEventPlane.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/FlowAnalysisWithFHCalEventPlane.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/FlowAnalysisWithLeeYangZeros.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/FlowAnalysisWithScalarProduct.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/FlowAnalysisWithQCumulant.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/FlowAnalysisWithHighOrderQCumulant.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/FlowAnalysisWithQCumulantGenericFramework.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/FlowAnalysisWithLeeYangZerosEventPlane.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/FlowAnalysisWithThreeEtaSubFHCalEventPlane.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/FlowAnalysisWithThreeEtaSubFHCalEventPlaneWRTSecondHarm.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/FlowAnalysisWithFHCalEventPlaneWRTSecondHarm.h"
)

set(FlowAnalysis_cxx_files
  "${CMAKE_CURRENT_SOURCE_DIR}/QVector.cxx"
  "${CMAKE_CURRENT_SOURCE_DIR}/FlowAnalysisWithEtaSubEventPlane.cxx"
  "${CMAKE_CURRENT_SOURCE_DIR}/FlowAnalysisWithThreeEtaSubEventPlane.cxx"
  "${CMAKE_CURRENT_SOURCE_DIR}/FlowAnalysisWithFHCalEventPlane.cxx"
  "${CMAKE_CURRENT_SOURCE_DIR}/FlowAnalysisWithLeeYangZeros.cxx"
  "${CMAKE_CURRENT_SOURCE_DIR}/FlowAnalysisWithScalarProduct.cxx"
  "${CMAKE_CURRENT_SOURCE_DIR}/FlowAnalysisWithQCumulant.cxx"
  "${CMAKE_CURRENT_SOURCE_DIR}/FlowAnalysisWithHighOrderQCumulant.cxx"
  "${CMAKE_CURRENT_SOURCE_DIR}/FlowAnalysisWithQCumulantGenericFramework.cxx"
  "${CMAKE_CURRENT_SOURCE_DIR}/FlowAnalysisWithLeeYangZerosEventPlane.cxx"
  "${CMAKE_CURRENT_SOURCE_DIR}/FlowAnalysisWithThreeEtaSubFHCalEventPlane.cxx"
  "${CMAKE_CURRENT_SOURCE_DIR}/FlowAnalysisWithThreeEtaSubFHCalEventPlaneWRTSecondHarm.cxx"
  "${CMAKE_CURRENT_SOURCE_DIR}/FlowAnalysisWithFHCalEventPlaneWRTSecondHarm.cxx"  
)

set(FlowAnalysis_LinkDef
	"${CMAKE_CURRENT_SOURCE_DIR}/FlowAnalysis.LinkDef.h"
)

#---Generate dictionary
ROOT_GENERATE_DICTIONARY(G__FlowAnalysis
  ${FlowAnalysis_h_files}
  LINKDEF ${FlowAnalysis_LinkDef}
)

#---Compile library
add_library(FlowAnalysis SHARED ${FlowAnalysis_cxx_files} G__FlowAnalysis.cxx)
target_link_libraries(FlowAnalysis ${FLOWANALYSIS_INCLUDE_LIBRARIES})