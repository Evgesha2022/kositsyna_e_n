add_library(bitsetT bitsetT.h bitsetT.cpp)

add_executable(bitsetT_test bitsetT_test.cpp)

target_link_libraries(bitsetT_test bitsetT)