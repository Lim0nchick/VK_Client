cmake_minimum_required(VERSION 3.5.1)

set(SERVICE "VK")

project(VK_Client)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/)

add_library(${PROJECT_NAME} STATIC ${CMAKE_CURRENT_SOURCE_DIR}/sources/client.cpp sources/client.cpp tests/tests.cpp include/VK/client.hpp include/VK/json.hpp)

find_package(OpenSSL REQUIRED)
find_package(CURL REQUIRED)

include_directories(${CURL_INCLUDE_DIR})
include_directories(${json_INCLUDE_DIRS})
set(DEPENDS_LIBRARIES ${OPENSSL_LIBRARIES} ${CURL_LIBRARY})

add_executable(examples ${CMAKE_CURRENT_SOURCE_DIR}/examples/main.cpp)

target_link_libraries(examples ${PROJECT_NAME} ${DEPENDS_LIBRARIES})