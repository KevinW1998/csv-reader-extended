include(../cmake/load_catch.cmake)

include_directories (${CMAKE_SOURCE_DIR}/include
                     ${CATCH_INCLUDE_DIR}
                     )

add_executable (CSVReaderExtendedTest 
                TestMain.cpp
                )

set_target_properties(CSVReaderExtendedTest PROPERTIES COMPILE_DEFINITIONS "GSL_THROW_ON_CONTRACT_VIOLATION")                       

add_test (NAME CSVReaderExtendedTestProj COMMAND CSVReaderExtendedTest)
