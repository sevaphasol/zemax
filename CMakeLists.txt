cmake_minimum_required( VERSION 3.16 )
project( Zemax LANGUAGES CXX )

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

file( GLOB_RECURSE REACTOR_SOURCES CONFIGURE_DEPENDS
	${CMAKE_CURRENT_SOURCE_DIR}/zemax/*.cpp
)

add_executable( zemax ${REACTOR_SOURCES} )
target_include_directories( zemax PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}
)

add_subdirectory( gfxlib )
target_link_libraries(zemax PRIVATE gfx)

set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}")
install(TARGETS zemax DESTINATION bin)
