include(FindPackageHandleStandardArgs)

if(WIN32)
	find_path( GLEW_INCLUDE_DIR
		NAMES
			GL/glew.h
		PATHS
			${GLEW_LOCATION}/include
			$ENV{GLEW_LOCATION}/include
			$ENV{PROGRAMFILES}/GLEW/include
			${PROJECT_SOURCE_DIR}/extern/glew/include
			${GLEW_LOCATION}
			$ENV{GLEW_LOCATION}
			DOC "The directory where GL/glew.h resides" )

	#find_file( GLEW_SOURCE
	#	NAMES
	#		glew.c
	#	PATHS
	#		${GLEW_LOCATION}/src
	#		$ENV{GLEW_LOCATION}/src
	#		$ENV{PROGRAMFILES}/GLEW/src
	#		$PROJECT_SOURCE_DIR}/extern/glew/src
	#		${GLEW_LOCATION}
	#		DOC "The directory where GL/glew.c resides" )
	find_library( GLEW_LIBRARY
		NAMES
			glew glew32
		PATHS
			${GLEW_LOCATION}/lib
			${GLEW_LOCATION}/lib/x86
			${GLEW_LOCATION}/lib/win32
			${GLEW_LOCATION}/lib/Release/win32
			$ENV{GLEW_LOCATION}/lib
			$ENV{GLEW_LOCATION}/lib/x86
			$ENV{GLEW_LOCATION}/lib/Release/win32
			$ENV{GLEW_LOCATION}/lib/Release MX/win32
			$ENV{GLEW_LOCATION}/lib/x86
			$ENV{GLEW_LOCATION}/lib/win32
			${PROJECT_SOURCE_DIR}/extern/glew/bin
			${PROJECT_SOURCE_DIR}/extern/glew/lib
			${PROJECT_SOURCE_DIR}/extern/glew/lib/x86
			${PROJECT_SOURCE_DIR}/extern/glew/lib/win32
			${GLEW_LOCATION}
			$ENV{GLEW_LOCATION}
			DOC "The GLEW library" )
	endif()

	if(UNIX)
		find_package(PkgConfig)
		if (PKG_CONFIG_FOUND)
			pkg_check_modules(PKG_GLEW QUIET glew)
		endif()
		# Search for library objects in known paths and optional hint from pkg-config
		find_library(GLEW_LIBRARY
			NAMES GLEW
			HINTS ${PKG_GLEW_LIBRARY_DIRS} ${PKG_GLEW_LIBDIR}
			)
# Search for header files in known paths and optional hint from pkg-config
		find_path(GLEW_INCLUDE_DIR
			GL/glew.h
			HINTS ${PKG_GLEW_INCLUDE_DIRS} ${PKG_GLEW_INCLUDEDIR}
			)
	endif()

find_package_handle_standard_args( GLEW DEFAULT_MSG GLEW_INCLUDE_DIR GLEW_LIBRARY )
mark_as_advanced(GLEW FOUND)


		
