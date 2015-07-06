cmake_minimum_required(VERSION 2.8.11)

project(Saphray)

set(SOURCE
   ${SOURCE}
   ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/object.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/ray.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/vector.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/scene.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/camera.cpp
   PARENT_SCOPE
)
