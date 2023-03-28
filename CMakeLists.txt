cmake_minimum_required(VERSION 3.15)
project(yuvUtils)

set(CMAKE_CXX_STANDARD 14)

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(comm)
include_directories(tools)

add_executable(yuvUtils
        comm/comm.h
        comm/yuvUtils_opt.cpp
        comm/yuvUtils_opt.h
        tools/yuvTools.cpp
        tools/yuvTools.h
        CMakeLists.txt
        main.cpp comm/comm.cpp tools/yuvPlayer.cpp tools/yuvPlayer.h)

target_link_libraries(yuvUtils ${SDL2_LIBRARIES})
install(
	TARGETS ${PROJECT_NAME}
	EXPORT yuvUtils
	DESTINATION ${CMAKE_INSTALL_BINDIR}
)
