#需求的最低cmake程序版本
cmake_minimum_required(VERSION 3.12)

#本工程的名字
project(OpenGL_Lecture)

#本工程支持的C++版本
set(CMAKE_CXX_STANDARD 17)

#把需要拷贝的资源路径放到ASSETS里
file(GLOB ASSETS "./assets")
file(COPY ${ASSETS} DESTINATION ${CMAKE_BINARY_DIR})


#往项目中加一个全局的预编译宏
add_definitions(-DDEBUG)

include_directories(
	SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/include
)
#链接阶段
link_directories(
	SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/lib
)

#add_subdirectory(wrapper)
add_subdirectory(application)
add_subdirectory(glframework)
add_subdirectory(character)

#本工程所有cpp文件编译链接，生成exe
add_executable(openglStudy "main.cpp" "glad.c" "Application/Application.h" "Application/Application.cpp"  )

target_link_libraries(openglStudy glfw3.lib app fw character)