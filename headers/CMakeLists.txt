cmake_minimum_required(VERSION 2.8.11)

project(Saphray)

set(HEADERS
   ${HEADERS}
   ${CMAKE_CURRENT_SOURCE_DIR}/object.h
   ${CMAKE_CURRENT_SOURCE_DIR}/ray.h
   ${CMAKE_CURRENT_SOURCE_DIR}/color.h
   ${CMAKE_CURRENT_SOURCE_DIR}/camera.h
   ${CMAKE_CURRENT_SOURCE_DIR}/vector.h
   ${CMAKE_CURRENT_SOURCE_DIR}/scene.h
   ${CMAKE_CURRENT_SOURCE_DIR}/point.h
   ${CMAKE_CURRENT_SOURCE_DIR}/light.h
   ${CMAKE_CURRENT_SOURCE_DIR}/camera.h
   PARENT_SCOPE
)
