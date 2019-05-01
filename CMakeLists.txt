cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(graphics-experiments)

# SET OpenGL_GL_PREFERENCE = GLVND
cmake_policy(SET CMP0072 NEW)

add_executable(${PROJECT_NAME}
  src/main.cpp
  src/SfmlHelper.cpp
  src/BezierExcercise.cpp
  src/TransformationExcercise.cpp
  src/CameraExcercise.cpp
  include/imgui-1.69/imgui.cpp
  include/imgui-1.69/imconfig.h
  include/imgui-1.69/imgui_draw.cpp
  include/imgui-1.69/imgui_widgets.cpp
  include/imgui-sfml/imgui-SFML.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/imgui-1.69>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/imgui-sfml>
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
