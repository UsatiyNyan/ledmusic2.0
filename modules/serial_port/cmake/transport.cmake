function(prepend)
    cmake_parse_arguments(PREPEND "" "TARGET;PREFIX" "FILES" ${ARGN})
    set(list_file_names "")
    foreach (file_name ${PREPEND_FILES})
        list(APPEND list_file_names "${PREPEND_PREFIX}/${file_name}")
    endforeach ()
    set(${PREPEND_TARGET} ${list_file_names} PARENT_SCOPE)
endfunction()

find_package(Protobuf 3.11 REQUIRED)

function(transport_generate_protos)
    cmake_parse_arguments(PB
            ""
            "INPUT_DIR;TARGET"
            ""
            ${ARGN})
    file(GLOB PB_FILES
            RELATIVE ${PB_INPUT_DIR}
            ${PB_INPUT_DIR}/*.proto)
    prepend(TARGET PB_FILES
            PREFIX ${PB_INPUT_DIR}
            FILES ${PB_FILES})


    protobuf_generate_cpp(PB_SRCS PB_HDRS ${PB_FILES})
    add_library(${PB_TARGET} STATIC ${PB_SRCS})
    target_include_directories(${PB_TARGET} PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
    target_link_libraries(${PB_TARGET} PUBLIC protobuf::libprotobuf)
endfunction()
