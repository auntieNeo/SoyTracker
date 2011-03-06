cmake_minimum_required (VERSION 2.6)
project (SoyTracker)
set (SoyTracker_VERSION_MAJOR 0)
set (SoyTracker_VERSION_MINOR 1)

set (PROJECT_SOURCE_DIR src)

include_directories("${PROJECT_SOURCE_DIR}/milkyplay")
add_subdirectory (${PROJECT_SOURCE_DIR}/milkyplay)

add_subdirectory (${PROJECT_SOURCE_DIR}/soytracker)
