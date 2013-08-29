
CMAKE_MINIMUM_REQUIRED( VERSION 2.6 FATAL_ERROR )

#-------------------------------------------------------------------->
# Описание проекта.

PROJECT( logger )

SET( PRJ_VERSION_MAJOR 0 )
SET( PRJ_VERSION_MINOR 4 )
SET( PRJ_VERSION_PATCH 2 )


SET (LIBSRC src/cLogsStream.cpp src/cSyslogStorage.cpp)

if (INSTALL_PATH)
	SET(INSTALL_PATH ${INSTALL_PATH})
else(INSTALL_PATH)
	SET(INSTALL_PATH "/usr/local")
endif(INSTALL_PATH)

MESSAGE("\nINSTALLATION PATH: ${INSTALL_PATH}\n")

SET(INSTALL_LIBS_PATH "${INSTALL_PATH}/lib")
SET(INSTALL_INCLUDE_PATH "${INSTALL_PATH}/include/log")

FILE (GLOB LIBHDR include/log/*.h )
INCLUDE_DIRECTORIES( /usr/local/include/types include )
ADD_LIBRARY (log STATIC ${LIBSRC} )

# Настройка компилятора.
IF( "${CMAKE_COMPILER_IS_GNUCXX}" MATCHES "1" )

	SET( CMAKE_CCXX_FLAGS "-funit-at-a-time --param large-function-growth=5000 --param inline-unit-growth=600 -finline-limit=2000" )
	SET( CMAKE_CCXX_FLAGS "${CMAKE_CCXX_FLAGS} -Wall -pedantic -Wno-long-long -Wno-inline -finline-functions -fno-strict-aliasing" )
	SET( CMAKE_CCXX_FLAGS "${CMAKE_CCXX_FLAGS} -O3 -funroll-loops" )

	SET( CMAKE_CXX_FLAGS "${CMAKE_CCXX_FLAGS}" )
	SET( CMAKE_C_FLAGS   "${CMAKE_CCXX_FLAGS}" )

ENDIF( "${CMAKE_COMPILER_IS_GNUCXX}" MATCHES "1" )

# Установка.

INSTALL ( FILES ${LIBHDR} 
	DESTINATION ${INSTALL_INCLUDE_PATH} )

INSTALL( TARGETS log
	DESTINATION ${INSTALL_LIBS_PATH} )

# Тесты.
#INCLUDE( tests/CMakeLists.txt )

# Конец.

