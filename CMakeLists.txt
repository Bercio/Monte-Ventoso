cmake_minimum_required(VERSION 3.5)
project(Monte_Ventoso)
set(CMAKE_CXX_STANDARD 14) #setto il linguaggio che sto usando
SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -fopenmp -fPIC") #fPIC needed to compile qt
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/lib/qt-5.9.2)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
#find qt
find_package(Qt5 COMPONENTS Core)
include_directories(${Qt5Core_INCLUDE_DIRS})
include_directories(lib/Snap-3.0/glib-core lib/Snap-3.0/snap-core) # includo le cartelle con gli header files
add_library( snap SHARED IMPORTED) #aggiungo una libreria che si chiama snap al progetto
set_target_properties( snap PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/Snap-3.0/snap-core/Snap.o) #la libreria che si chiama snap è già un file binario quindi non andrà mai compilata
add_library(Scimmia scimmia.cpp) #aggiungo una libreria che ho scritto io non .o quindi a una certa và compilata
add_library(Parete parete.cpp)
target_link_libraries(Parete snap rt)
target_link_libraries(Scimmia Parete)
add_library(Evoluzione STATIC evoluzione.cpp)
add_executable(testSpeed testSpeed.cpp) #l'eseguibile è testSpeed
add_executable(logEvol logEvol.cpp)

target_link_libraries(Evoluzione Scimmia ${Qt5Core_LIBRARIES})
target_link_libraries(testSpeed Evoluzione)
target_link_libraries(logEvol Evoluzione)
target_include_directories (Evoluzione PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(qtgrafica)
