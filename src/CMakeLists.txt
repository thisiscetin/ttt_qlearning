INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/src)

ADD_EXECUTABLE(game
        ../main.cpp
        board.cpp board.h game.cpp game.h table.cpp table.h trainer.cpp trainer.h)

set_target_properties(game
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
        )

target_link_libraries(game)
