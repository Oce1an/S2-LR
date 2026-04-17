# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "")
  file(REMOVE_RECURSE
  "CMakeFiles\\c_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\c_autogen.dir\\ParseCache.txt"
  "c_autogen"
  )
endif()
