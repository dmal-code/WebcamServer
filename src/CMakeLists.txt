# Find all the input files
FILE(GLOB_RECURSE inFiles RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

# Create the release executable  
set(targetNameRelease "webcamserver_release")
ADD_EXECUTABLE(${targetNameRelease} ${inFiles})

target_link_libraries(${targetNameRelease} lazarus_shared_release pistache gomp pthread png jpeg xml2 sensors curl cpupower)
set_property(TARGET ${targetNameRelease} PROPERTY COMPILE_FLAGS "-std=c++17 -I ../../src -fopenmp")
set_property(TARGET ${targetNameRelease} PROPERTY LINK_FLAGS "-L/usr/local/lib/lazarus")

# Create the debug executable  
set(targetNameDebug "webcamserver_debug")
ADD_EXECUTABLE(${targetNameDebug} ${inFiles})

target_link_libraries(${targetNameDebug} lazarus_shared_debug pistache gomp pthread png jpeg xml2 sensors curl cpupower)
set_property(TARGET ${targetNameDebug} PROPERTY COMPILE_FLAGS "-std=c++17 -I ../../src -O -ggdb -Wall -fstack-protector-all -fno-omit-frame-pointer -fopenmp")
set_property(TARGET ${targetNameDebug} PROPERTY LINK_FLAGS "-L/usr/local/lib/lazarus")
