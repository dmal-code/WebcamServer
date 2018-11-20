cmake_minimum_required(VERSION 3.0.0)

PROJECT(WebcamServer)

# Make sure we know where the executable is
SET(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin" CACHE INTERNAL "")

#define the include directory for SH
include_directories("/usr/local/include/lazarus")

#define the include directory for libXML
include_directories("/usr/include/libxml2")

subdirs(src)
