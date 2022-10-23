cmake_minimum_required(VERSION 3.7)

project(breakout LANGUAGES CXX)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(PREBUILT_MODULE_PATH ${CMAKE_BINARY_DIR}/modules)

function(add_module name)
    file(MAKE_DIRECTORY ${PREBUILT_MODULE_PATH})
          if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
            # using Clang
            add_custom_target(${name}.pcm
                    COMMAND
                        ${CMAKE_CXX_COMPILER}
                        -std=c++20
                        -c
                        ${CMAKE_CURRENT_SOURCE_DIR}/${ARGN}
                        -Xclang -emit-module-interface
                        -o ${PREBUILT_MODULE_PATH}/${name}.pcm
                    )
          elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
            # using GCC
            add_custom_target(${name}.pcm
                    COMMAND
                        ${CMAKE_CXX_COMPILER}
                        -std=c++20
                        -fmodules-ts
                        -c
                        ${CMAKE_CURRENT_SOURCE_DIR}/${ARGN}
                        -o ${name}.pcm
                        `sdl2-config --cflags --libs`
                    )
            # g++ -std=c++20 -fmodules-ts -xc++-system-header cstudio
          elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
            # using Visual Studio C++
            add_custom_target(${name}.obj
                    COMMAND
                        ${CMAKE_CXX_COMPILER} /experimental:module
                        /c
                        ${CMAKE_CURRENT_SOURCE_DIR}/${ARGN}
                    )
          endif()
endfunction()

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  # using Clang
  add_compile_options(-fprebuilt-module-path=${PREBUILT_MODULE_PATH})

  add_module(helloworld src/helloworld.cpp)
  add_executable(mainExe src/main.cpp src/helloworld.cpp)

  add_dependencies(main helloworld.pcm)

elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  # using GCC
  add_compile_options(-fmodules-ts)

  add_module(ball src/m_ball.cpp)
  add_module(block src/m_block.cpp)
  add_module(controller src/m_controller.cpp)
  add_module(game src/m_game.cpp)
  add_module(main src/m_main.cpp)
  add_module(paddle src/m_paddle.cpp)
  add_module(renderer src/m_renderer.cpp)

  add_executable(breakout src/main.cpp)

  add_custom_target(ball src/m_ball.cpp)
  add_custom_target(block src/m_block.cpp)
  add_custom_target(controller src/m_controller.cpp)
  add_custom_target(game src/m_game.cpp)
  add_custom_target(main src/m_main.cpp)
  add_custom_target(paddle src/m_paddle.cpp)
  add_custom_target(renderer src/m_renderer.cpp)

  target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})

  target_link_options(breakout PUBLIC "LINKER:ball.pcm")
  target_link_options(breakout PUBLIC "LINKER:block.pcm")
  target_link_options(breakout PUBLIC "LINKER:controller.pcm")
  target_link_options(breakout PUBLIC "LINKER:game.pcm")
  target_link_options(breakout PUBLIC "LINKER:main.pcm")
  target_link_options(breakout PUBLIC "LINKER:paddle.pcm")
  target_link_options(breakout PUBLIC "LINKER:renderer.pcm")
  
  add_dependencies(renderer ball.pcm block.pcm controller.pcm game.pcm main.pcm paddle.pcm breakout renderer.pcm)

  add_dependencies(breakout ball.pcm block.pcm controller.pcm game.pcm main.pcm paddle.pcm breakout renderer.pcm)

elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  # using Visual Studio C++
  add_compile_options(/experimental:module /c)

  add_module(helloworld helloworld.cpp)
  add_executable(mainExe main.cpp)


  add_dependencies(main helloworld.pcm)

endif()