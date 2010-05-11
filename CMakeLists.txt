SET ( EXTENSION_NAME "Extensions_SpinOff")

# Create the extension library
ADD_LIBRARY( ${EXTENSION_NAME}
  Renderers/OpenGL/MRIRenderingView.h
  Renderers/OpenGL/MRIRenderingView.cpp
  Scene/MRINode.h
  Scene/MRINode.cpp
)

TARGET_LINK_LIBRARIES( ${EXTENSION_NAME}
  OpenEngine_Scene
  Extensions_OpenGLRenderer
  Extensions_MeshUtils
)
