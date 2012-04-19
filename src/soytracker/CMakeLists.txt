add_executable(soytracker main.cpp)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
set(SOYTRACKER_LIBS ${SOYTRACKER_LIBS} ${CURSES_LIBRARIES})
SET_TARGET_PROPERTIES(soytracker PROPERTIES LINK_FLAGS -Wl,-lpanel)

target_link_libraries(soytracker milkyplay ${SOYTRACKER_LIBS})
