INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/src)

ADD_EXECUTABLE(game
        ../main.cpp
        board.cpp
        game.cpp
        table.cpp
        trainer.cpp
        )

set_target_properties(game
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
        )

target_link_libraries(game)
