cmake_minimum_required(VERSION 2.8)

project( OS )
set(WARNING_FLAGS "-Wall -Wextra -Wshadow -pedantic -g")
add_executable( project_1 main.c scheduler.c process.c priority_queue.c)
set_target_properties(project_1 PROPERTIES COMPILE_FLAGS "${WARNING_FLAGS}")
