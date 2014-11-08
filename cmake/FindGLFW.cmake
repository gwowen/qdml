include(FindPackageHandleStandardArgs)

if(WIN32)
	find_path( GLFW_INCLUDE_DIR
		NAMES
			GLFW/glfw3.h
		PATHS
			${GLFW_LOCATION}/include
			$ENV{GLFW_LOCATION}/include
			$ENV{PROGRAMFILES}/GLFW/include
			${PROJECT_SOURCE_DIR}/extern/glfw3/include
			${GLEW_LOCATION}
			$ENV{GLFW_LOCATION}
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
	find_library( GLFW_LIBRARY
		NAMES
			glfw3
		PATHS
			${GLFW_LOCATION}/lib
			${GLFW_LOCATION}/lib/x64
			${GLFW_LOCATION}/lib-msvc110
			${GLFW_LOCATION}/lib-msvc120
			${GLFW_LOCATION}/lib/Release/win32
			$ENV{GLFW_LOCATION}/lib
			$ENV{GLFW_LOCATION}/lib/x64
			#$ENV{GLFW_LOCATION}/lib-msvc110
			$ENV{GLFW_LOCATION}/lib-msvc120
			${PROJECT_SOURCE_DIR}/extern/glfw/bin
			${PROJECT_SOURCE_DIR}/extern/glfw/lib
			$ENV{PROGRAMFILES}/GLFW/lib
			DOC "The GLFW library" )
	endif()
	
	if(UNIX)
		find_path( GLFW_INCLUDE_DIR
			NAMES
				glfw3.h
			PATHS
				${GLFW_LOCATION}/include/GLFW
				$ENV{GLFW_LOCATION}/include/GLFW
				/usr/include
				/usr/local/include
				/sw/include/
				/opt/local/include
				NO_DEFAULT_PATH
				DOC "The directory where GLFW/glfw3.h resides")
		find_library( GLFW_LIBRARY
			NAMES
				glfw3
			PATHS
				${GLFW_LOCATION}/lib
				$ENV{GLFW_LOCATION}/lib
				/usr/lib64
				/usr/lib
				/usr/local/lib64
				/usr/local/lib
				/sw/lib
				/opt/local/lib
				NO_DEFAULT_PATH
				DOC "The GLFW library")
endif()

find_package_handle_standard_args( GLFW DEFAULT_MSG GLFW_INCLUDE_DIR GLFW_LIBRARY ) 
mark_as_advanced(GLEW FOUND)