cmake_minimum_required(VERSION 3.12)

#https://stackoverflow.com/questions/34143265/undefined-reference-to-symbol-pthread-createglibc-2-2-5
set(CMAKE_THREAD_LIBS_INIT "-lpthread")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_HAVE_THREADS_LIBRARY 1)
set(CMAKE_USE_WIN32_THREADS_INIT 0)
set(CMAKE_USE_PTHREADS_INIT 1)
set(THREADS_PREFER_PTHREAD_FLAG ON)

project(ELE4205_PROJECT_server)
if(NOT DEFINED CMAKE_MODULE_PATH)
    list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../cmake/)
endif()

if(NOT DEFINED COMMON_DATA_DIR)
    set(COMMON_DATA_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../commun/)
endif()


set(MODULE_NAME ${PROJECT_NAME})
set(MODULE_HEADER_FILES 
    include/ele4205_project/ServerApplication.hpp
)

set(MODULE_SOURCE_FILES
    src/main.cpp
    src/ServerApplication.cpp
)

set(MODULE_LIBS
    Camera
    Morse
    Resolution_${PROJECT_NAME}
    tcpLengthFramer_${PROJECT_NAME}
    TCPServer_${PROJECT_NAME}
    PacketEngine_${PROJECT_NAME}
)


option(USE_CROSS_COMPILE_ODROID_POKY "Use cross compile odroid poky toolchain" ON)

if(${USE_CROSS_COMPILE_ODROID_POKY})
    message(STATUS "USE CROSS COMPILE POKY TOOLCHAIN")
    include(cross-compile)
endif()

add_executable(${MODULE_NAME} ${MODULE_SOURCE_FILES} ${MODULE_HEADER_FILES})

include(unset-opencv-variables)
find_package(OpenCV 3.1 REQUIRED)
if(OpenCV_FOUND)
message( STATUS "OpenCV 3.1 library found in : ${OpenCV_DIR}")
else(OpenCV_FOUND)
message(FATAL ERROR "Librarie OpenCV introuvable!")
endif ()

add_subdirectory(${COMMON_DATA_DIR} commun)
add_subdirectory(modules)

target_link_libraries(${MODULE_NAME} ${OpenCV_LIBRARIES} ${MODULE_LIBS})
target_include_directories(${MODULE_NAME}  PUBLIC ${OpenCV_INCLUDE_DIRS})
target_include_directories(${MODULE_NAME}  PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/ele4205_project>
    $<INSTALL_INTERFACE:include/ele4205_project>
    PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
