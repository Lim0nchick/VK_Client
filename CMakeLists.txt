cmake_minimum_required(VERSION 3.5.1)

set(SERVICE "VK")

project(VK_Client)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
#set(Boost_INCLUDE_DIRS /usr/local/include/boost_1_62_0/boost/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/)

<<<<<<< HEAD
add_library(${PROJECT_NAME} STATIC ${CMAKE_CURRENT_SOURCE_DIR}/sources/client.cpp sources/client.cpp tests/tests.cpp include/client.hpp)
=======
add_library(${PROJECT_NAME} STATIC ${CMAKE_CURRENT_SOURCE_DIR}/sources/client.cpp sources/client.cpp tests/tests.cpp include/VK/client.hpp)
>>>>>>> 77f10556c6a63f63a3cb59b489af3a596e904884

find_package(OpenSSL REQUIRED)
find_package(CURL REQUIRED)
#find_package(Boost COMPONENTS asio REQUIRED)
include_directories(${CURL_INCLUDE_DIR})
#include_directories(${Boost_INCLUDE_DIRS})
set(DEPENDS_LIBRARIES ${OPENSSL_LIBRARIES} ${CURL_LIBRARY})

add_executable(examples ${CMAKE_CURRENT_SOURCE_DIR}/examples/main.cpp)

<<<<<<< HEAD
target_link_libraries(examples ${PROJECT_NAME} ${DEPENDS_LIBRARIES} )
=======
target_link_libraries(examples ${PROJECT_NAME} ${DEPENDS_LIBRARIES})
>>>>>>> 77f10556c6a63f63a3cb59b489af3a596e904884
