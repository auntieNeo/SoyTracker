add_executable(soytracker main.cpp moduleEditor.cpp patternEditor.cpp)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
set(SOYTRACKER_LIBS ${SOYTRACKER_LIBS} ${CURSES_LIBRARIES})

target_link_libraries(soytracker milkyplay ${SOYTRACKER_LIBS})
