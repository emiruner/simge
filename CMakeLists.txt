PROJECT(Simge)
ADD_SUBDIRECTORY(src)
FILE(GLOB_RECURSE geomIncludes include/simge/geom/*.hpp)
INSTALL(FILES ${geomIncludes} DESTINATION /include/simge/geom)
FILE(GLOB_RECURSE glutIncludes include/simge/glut/*.hpp)
INSTALL(FILES ${glutIncludes} DESTINATION /include/simge/glut)
FILE(GLOB_RECURSE utilIncludes include/simge/util/*.hpp)
INSTALL(FILES ${utilIncludes} DESTINATION /include/simge/util)
FILE(GLOB_RECURSE algoIncludes include/simge/algo/*.hpp)
INSTALL(FILES ${algoIncludes} DESTINATION /include/simge/algo)


