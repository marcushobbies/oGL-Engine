set(TARGET oGL)

add_executable(${TARGET} 
  main.cpp
  tools/Logger.cpp
  shaders/ShaderProgram.cpp
  render/Camera.cpp
  render/Mesh.cpp
  render/Object.cpp
  models/ModelLoader.cpp
  engine/Scene.cpp
  debugGame/DebugScene.cpp
)

target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} GLEW::GLEW)
target_link_libraries(${PROJECT_NAME} OpenGL::GL)
