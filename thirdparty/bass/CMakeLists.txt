add_library(bass INTERFACE)
target_include_directories(bass INTERFACE include)
target_link_libraries(bass INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include/libbass.so)
