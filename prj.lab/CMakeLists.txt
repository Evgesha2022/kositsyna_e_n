add_subdirectory(rational)

add_subdirectory(complex)

add_subdirectory(bitset)

add_subdirectory(bitsetT)

add_subdirectory(bitsetI)

#add_subdirectory(bitsetD)

add_subdirectory(queue_p)

add_subdirectory(Qu)
 
#add_subdirectory(c_queue_p)

add_subdirectory(main)

include(FetchContent)

FetchContent_Declare(matplotplusplus
        GIT_REPOSITORY https://github.com/alandefreitas/matplotplusplus
        GIT_TAG origin/master) # or whatever tag you want

FetchContent_GetProperties(matplotplusplus)

if(NOT matplotplusplus_POPULATED)
    FetchContent_Populate(matplotplusplus)
    add_subdirectory(${matplotplusplus_SOURCE_DIR} ${matplotplusplus_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

target_link_libraries(main PUBLIC matplot)