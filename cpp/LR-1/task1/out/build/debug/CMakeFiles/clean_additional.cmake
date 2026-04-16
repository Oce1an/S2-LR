# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\car_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\car_autogen.dir\\ParseCache.txt"
  "car_autogen"
  )
endif()
