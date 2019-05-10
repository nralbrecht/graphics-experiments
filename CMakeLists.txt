cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(graphics-experiments)

# SET OpenGL_GL_PREFERENCE = GLVND
cmake_policy(SET CMP0072 NEW)

add_executable(${PROJECT_NAME}
  src/main.cpp
  src/SfmlHelper.cpp
  
  src/BezierExercise.cpp
  src/CameraExercise.cpp
  src/DelaunayExercise.cpp
  src/TransformationExercise.cpp
  
  src/CubeShape.cpp
  src/MeshShape.cpp
  src/SphereShape.cpp

  src/PlyLoader.cpp
  src/ObjLoader.cpp

  extern/imgui/imgui.cpp
  extern/imgui/imconfig.h
  extern/imgui/imgui_draw.cpp
  extern/imgui/imgui_widgets.cpp
  extern/delabella/delabella.cpp
  extern/imgui-sfml/imgui-SFML.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/extern/imgui>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/extern/tinydir>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/extern/delabella>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/extern/imgui-sfml>
  $<INSTALL_INTERFACE:include>
)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)
find_package(SFML 2 COMPONENTS system window graphics REQUIRED)

target_link_libraries(${PROJECT_NAME}
  GLEW::GLEW
  GLUT::GLUT
  OpenGL::GL
  sfml-system sfml-window sfml-graphics
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources)
