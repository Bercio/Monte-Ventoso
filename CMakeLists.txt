cmake_minimum_required(VERSION 3.5)
project(Sistemi_Complessi)
set(CMAKE_CXX_STANDARD 14)
SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -fopenmp")

set(SOURCE_FILES
    cmake-build-debug/CMakeFiles/3.6.2/CompilerIdC/CMakeCCompilerId.c
    cmake-build-debug/CMakeFiles/3.6.2/CompilerIdCXX/CMakeCXXCompilerId.cpp
    cmake-build-debug/CMakeFiles/feature_tests.c
    cmake-build-debug/CMakeFiles/feature_tests.cxx
    genetico.h
        )

include_directories(lib/Snap-3.0/glib-core lib/Snap-3.0/snap-core)
add_library( snap SHARED IMPORTED)
add_subdirectory(tests)
set_target_properties( snap PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/Snap-3.0/snap-core/Snap.o)
add_library(Scimmia genetico.cpp)
target_link_libraries(Scimmia snap rt)
target_include_directories (Scimmia PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
