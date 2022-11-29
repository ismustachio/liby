include_directories(src)
set(NAME graphics)
find_package(Vulkan REQUIRED)
find_package(glfw3 3.3 REQUIRED)
file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true src/*.h src/*.c)



add_library(${NAME} STATIC ${SOURCES})
#target_include_directories(${PROJECT_NAME} PRIVATE /usr/local/include)
target_link_libraries(${NAME} ${Vulkan_LIBRARIES})
target_link_libraries(${NAME} glfw)
target_include_directories(${NAME} PUBLIC ${glfw3_INCLUDE_DIR})
target_include_directories(${NAME} PUBLIC ${Vulkan_INCLUDE_DIR})
#target_link_libraries(${PROJECT_NAME} glslang)
#target_link_libraries(${PROJECT_NAME} SPIRV)
#target_link_libraries(${PROJECT_NAME} shaderc_shared)
#target_include_directories(${PROJECT_NAME} PUBLIC ${glslang_INCLUDE_DIR})

set_target_properties(${NAME} PROPERTIES LINKER_LANGUAGE C)
