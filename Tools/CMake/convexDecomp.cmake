project(convexDecomp)

addStaticLib("${libDir}/convexDecomp")

if(UNIX)
	addDef(LINUX)
endif()
