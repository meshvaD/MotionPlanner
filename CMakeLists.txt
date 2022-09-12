cmake_minimum_required(VERSION 3.0.0)
project(MotionPlanner VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(MotionPlanner main.cpp vector2.cpp link.cpp ik_solver.cpp cspace.cpp animate.cpp path_solver.cpp)

find_package( OpenCV REQUIRED )
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories( ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} )
target_link_libraries(MotionPlanner ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})

include_directories( ${OpenCV_INCLUDE_DIRS} )
target_link_libraries( MotionPlanner ${OpenCV_LIBS} )

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
