# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/StatusBarExample_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/StatusBarExample_autogen.dir/ParseCache.txt"
  "StatusBarExample_autogen"
  )
endif()
