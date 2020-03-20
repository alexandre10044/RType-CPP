project(RType C CXX)
cmake_minimum_required(VERSION 2.8.12)
set(CMAKE_BUILD_TYPE Debug)
# Global
set(CMAKE_MODULE_PATH "/usr/share/SFML/cmake/Modules")

# CPack packaging
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/COPYING")
set(CPACK_PACKAGE_VERSION_MAJOR "${myproject_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${myproject_VERSION_MINOR}")

# Client
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/rtype/client/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/rtype/client/data)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/rtype/client/engine)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/rtype/client/graphics)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/rtype/network)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/rtype/server/Messages/Attack)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/rtype/server/Messages/Monster)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/rtype/server/Messages/Player)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/rtype/server/Messages/Error)
## Server includes
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/rtype/server/network)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/rtype/server/Messages/Attack)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/rtype/server/Messages/Player)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/rtype/server/Messages/Monsters)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/rtype/server/Messages/Ping)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/rtype/server/Messages/Room)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/rtype/server/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/rtype/server/Log)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/rtype/server/Timer)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/rtype/server/Client)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/rtype/server/Config)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/rtype/server/Monster)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/rtype/server/Attack)

set(EXECUTABLE_NAME "r-type_client")
add_executable(
  ## executable name
  ${EXECUTABLE_NAME}
  ## sources
  ${CMAKE_CURRENT_SOURCE_DIR}/rtype/client/engine/data/serverData.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/rtype/client/engine/game/actions.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/rtype/client/engine/game/callback.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/rtype/client/engine/game/compo.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/rtype/client/engine/game/object.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/rtype/client/engine/graphics/events.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/rtype/client/engine/graphics/help.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/rtype/client/engine/graphics/menu.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/rtype/client/engine/graphics/resources.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/rtype/client/engine/graphics/rooms.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/rtype/client/engine/graphics/settings.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/rtype/client/engine/client.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/rtype/client/engine/data.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/rtype/client/engine/graphics.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/rtype/client/engine.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/rtype/client/game.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/rtype/client/main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/rtype/client/music.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/rtype/client/scroller.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/rtype/network/NetworkManager.cpp
)


add_library(rtypenetwork STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/rtype/network/NetworkManager.cpp
)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED network audio graphics window system)
FIND_PACKAGE ( Threads REQUIRED )
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} stdc++fs ${CMAKE_THREAD_LIBS_INIT} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} rtypenetwork )
endif()

install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)

# Server
add_executable(
    ## Server executable name
    r-type_server
    ## Server sources
    ${CMAKE_CURRENT_SOURCE_DIR}/rtype/server/Main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/rtype/server/Server.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/rtype/server/Client/Client.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/rtype/server/Config/Config.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/rtype/server/Log/Log.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/rtype/server/Timer/Timer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/rtype/server/Attack/Attack.cpp
)
FIND_PACKAGE ( Threads REQUIRED )
TARGET_LINK_LIBRARIES ( r-type_server ${CMAKE_THREAD_LIBS_INIT} rtypenetwork )