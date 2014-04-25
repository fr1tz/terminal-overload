project(pcre)

addStaticLib("${libDir}/pcre")

addDef(PCRE_STATIC)
addDef(HAVE_CONFIG_H)

if(WIN32)
	set_property(TARGET pcre PROPERTY COMPILE_FLAGS       /TP) #/TP = compile as C++
else() # ggc clang
	set_property(TARGET pcre PROPERTY COMPILE_FLAGS       "-x c++") #/TP = compile as C++
endif()
