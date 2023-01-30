cmake_minimum_required(VERSION 3.0.0)
project(paho-mqtt-demo VERSION 0.1.0)

link_directories(${PROJECT_SOURCE_DIR}/lib)
include_directories(${PROJECT_SOURCE_DIR}/include)
add_executable(paho-mqtt-demo main.cpp)
target_link_libraries(${PROJECT_NAME} paho-mqtt3c)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
