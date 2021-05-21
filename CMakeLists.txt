cmake_minimum_required(VERSION 3.5)

project(engine)

############################################################
# Set compiler flags
############################################################
set(OWN_GXX_FLAGS " -O3 -Wall -Wextra -std=c++14")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${OWN_GXX_FLAGS} -pg -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${OWN_GXX_FLAGS}")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${OWN_GXX_FLAGS}")

############################################################
# List all sources
############################################################
set(engine_sources l_parser.h l_parser.cc easy_image.cc engine.cc
	ini_configuration.cc vector3d.h vector3d.cc
		EngineModules/AbstractModule.cpp EngineModules/AbstractModule.h EngineModules/_2DLSystemModule.cpp EngineModules/_2DLSystemModule.h
		EngineModules/Point2D.cpp EngineModules/Point2D.h EngineModules/Line2D.cpp EngineModules/Line2D.h EngineModules/Lines2D.cpp
		EngineModules/Lines2D.h EngineModules/_3DLineModule.cpp EngineModules/_3DLineModule.h EngineModules/Face.cpp EngineModules/Face.h
		EngineModules/Figure.cpp EngineModules/Figure.h EngineModules/Figures3D.cpp EngineModules/Figures3D.h EngineModules/MatrixMath.cpp EngineModules/MatrixMath.h EngineModules/_3DLsystem.cpp EngineModules/_3DLsystem.h)

############################################################
# Create an executable
############################################################
set(exe_name "engine")
add_executable( ${exe_name} ${engine_sources} )
install( TARGETS ${exe_name} DESTINATION ${PROJECT_SOURCE_DIR}/ )
