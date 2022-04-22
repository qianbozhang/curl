#set(HEADERS XXX)
set(SRCS main.cpp)

#library
#add_library(main SHARED ${SRCS})

#exce
add_executable(main ${SRCS})
target_include_directories(main PUBLIC ./)

set_target_properties(main PROPERTIES LINK_FLAGS "-Wl,--no-undefined -g")
TARGET_LINK_LIBRARIES(main curl ssl crypto)