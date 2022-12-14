cmake_minimum_required(VERSION 3.12)

set(LIB_NAME
  Camera
)


set(LIB_INCLUDE_DIR 
  "include/Camera/"
)

set(LIB_HEADER_FILES 
  ${LIB_INCLUDE_DIR}/Camera.hpp
  ${LIB_INCLUDE_DIR}/GrabThread.hpp
)

set(LIB_SOURCE_FILES
src/Camera.cpp
src/GrabThread.cpp
)

set(MODULE_LIBS
    Resolution_${PROJECT_NAME}
)

add_library(${LIB_NAME}
OBJECT
   
  ${LIB_SOURCE_FILES}
   
  ${LIB_HEADER_FILES}
) 

add_dependencies(${LIB_NAME} ${MODULE_LIBS})
target_link_libraries(${LIB_NAME} ${MODULE_LIBS})
target_link_libraries(${LIB_NAME} ${OpenCV_LIBRARIES} ${MODULE_LIBS})

target_include_directories(${LIB_NAME}  PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${LIB_INCLUDE_DIR}>
    $<INSTALL_INTERFACE:${LIB_INCLUDE_DIR}>
    PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
