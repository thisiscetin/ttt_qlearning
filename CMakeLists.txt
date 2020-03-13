# cmake_minimum_required(VERSION 3.5)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
# enable_testing()

# project(qlearning)

# include_directories(${CMAKE_CURRENT_SOURCE_DIR}/ext)
# include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

# ADD_EXECUTABLE(tests
  # ${CMAKE_CURRENT_SOURCE_DIR}/test/test_board.cpp
  # ${CMAKE_CURRENT_SOURCE_DIR}/test/test_game.cpp

  # ${CMAKE_CURRENT_SOURCE_DIR}/src/board.cpp
  # ${CMAKE_CURRENT_SOURCE_DIR}/src/game.cpp
# )

# set_target_properties(tests
    # PROPERTIES
    # RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
# )

# target_link_libraries(tests)

cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

project(xox_qlearning)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)

enable_testing()
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)
