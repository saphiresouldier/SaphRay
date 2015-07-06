cmake_minimum_required(VERSION 2.8.11)

project(Saphray)

add_subdirectory("${PROJECT_SOURCE_DIR}/source")
add_subdirectory("${PROJECT_SOURCE_DIR}/headers")

add_executable(Saphray ${SOURCE} ${HEADERS})

