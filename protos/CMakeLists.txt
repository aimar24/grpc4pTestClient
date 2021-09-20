#
project(Proto)
cmake_minimum_required(VERSION 3.21)

file(GLOB PROTO_FILES ${PROJECT_SOURCE_DIR}/*.proto)

execute_process(COMMAND  which grpc_cpp_plugin OUTPUT_VARIABLE GRPC_CPP_PLUGIN)
string(STRIP ${GRPC_CPP_PLUGIN} GRPC_CPP_PLUGIN)
message(STATUS "MY_VAR=${PROTO_FILES}")
message (STATUS "protoc -I ${PROJECT_SOURCE_DIR}  --grpc_out=${PROJECT_SOURCE_DIR} --plugin=protoc-gen-grpc=${GRPC_CPP_PLUGIN} ${PROTO_FILES}")

make_directory(${PROJECT_SOURCE_DIR}/generated/)
execute_process(COMMAND  protoc -I ${PROJECT_SOURCE_DIR}  --cpp_out=${PROJECT_SOURCE_DIR}/generated/ ${PROTO_FILES})
execute_process(COMMAND  protoc -I ${PROJECT_SOURCE_DIR}  --grpc_out=${PROJECT_SOURCE_DIR}/generated/ --plugin=protoc-gen-grpc=${GRPC_CPP_PLUGIN} ${PROTO_FILES})



file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/generated/*.cc)
file(GLOB HEADER_FILES ${PROJECT_SOURCE_DIR}/generated/*.h)

add_library(${PROJECT_NAME} SHARED
${SRC_FILES}
${HEADER_FILES}
)


#--grpc_out=${PROJECT_SOURCE_DIR} --cpp_out=${PROJECT_SOURCE_DIR}