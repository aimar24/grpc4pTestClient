cmake_minimum_required(VERSION 3.0.0)
project(testClient VERSION 0.1.0)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include(CTest)
enable_testing()
add_subdirectory(./protos)
add_subdirectory(./grpc4p)

include_directories(
    grpc4p/include/
    grpc4p/3rdparty/Promise/include
)

list(APPEND CMAKE_PREFIX_PATH "/home/aimar/grpcp/grpc/cmake")

include_directories(
    ./grpcp/include/
    ./protos/generated/
    )

add_executable(${PROJECT_NAME} main.cpp)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

find_package(Threads REQUIRED)
#FindThreads(CMAKE_THREAD_PREFER_PTHREAD)
#find_package(Threads CONFIG REQUIRED)
find_package(protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

link_directories(/usr/local/lib/)
target_link_libraries(${PROJECT_NAME} 
Proto
#grpc
grpcPlusPromise
gRPC::grpc++
Threads::Threads
)
