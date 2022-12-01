cmake_minimum_required(VERSION 3.10)

project(liby-engine VERSION 0.1)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(GLSLC /usr/local/bin/glslc)

if(NOT EXISTS ${PROJECT_BINARY_DIR}/.gitignore)
  file(WRITE ${PROJECT_BINARY_DIR}/.gitignore "*")
endif()

add_subdirectory(math)
add_subdirectory(graphics)


add_executable(${PROJECT_NAME} main.c)
target_link_libraries(${PROJECT_NAME} math)
target_link_libraries(${PROJECT_NAME} graphics)
target_include_directories(${PROJECT_NAME} PRIVATE math/src)
target_include_directories(${PROJECT_NAME} PRIVATE graphics/src)
file(GLOB_RECURSE GLSL_SOURCE_FILES "shaders/*.frag" "shaders/*.vert")
set(SOURCES ${SOURCES})

#add_library(${PROJECT_NAME} STATIC ${SRC})
foreach(GLSL ${GLSL_SOURCE_FILES})
  get_filename_component(FILE_NAME ${GLSL} NAME)
  set(SPIRV "${PROJECT_BINARY_DIR}/shaders/${FILE_NAME}.spv")
  add_custom_command(
    OUTPUT ${SPIRV}
    COMMAND ${CMAKE_COMMAND} -E make_directory "${PROJECT_BINARY_DIR}/shaders/"
    COMMAND ${GLSLC} ${GLSL} -o ${SPIRV}
    DEPENDS ${GLSL})
  list(APPEND SPIRV_BINARY_FILES ${SPIRV})
endforeach(GLSL)

add_custom_target(Shaders DEPENDS ${SPIRV_BINARY_FILES})
add_dependencies(${PROJECT_NAME} Shaders)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E make_directory
  "$<TARGET_FILE_DIR:${PROJECT_NAME}>/shaders/"
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  "${PROJECT_BINARY_DIR}/shaders"
  "$<TARGET_FILE_DIR:${PROJECT_NAME}>/shaders"
)
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE C)
