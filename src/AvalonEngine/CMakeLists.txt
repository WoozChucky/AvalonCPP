cmake_minimum_required(VERSION 3.9)
project(AvalonEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

add_library(AvalonEngine Audio/Audio.h Audio/AudioPlayer.h Audio/DesktopAudioPlayer.cpp Audio/DesktopAudioPlayer.h Audio/NullAudioPlayer.cpp Audio/NullAudioPlayer.h Locator.cpp Locator.h FileSystem/File.h FileSystem/FileSystem.h FileSystem/NullFileSystem.cpp FileSystem/NullFileSystem.h FileSystem/DesktopFileSystem.cpp FileSystem/DesktopFileSystem.h Logger/Logger.cpp Logger/Logger.h EventBus/Subject.h Extensions/VectorExtensions.h UI/Game/Healthbar.cpp UI/Game/Healthbar.h Math/Math.cpp Math/Math.h UI/Engine/Events/EventType.h UI/Engine/Events/MouseEvents.h UI/Engine/MouseCursor.cpp UI/Engine/MouseCursor.h UI/Engine/UIElement.h UI/Engine/Button.cpp UI/Engine/Button.h Entities/Components/GraphicsComponent.h Entities/Components/InputComponent.h Entities/Components/PhysicsComponent.h Entities/Entity.h Entities/Enemy.cpp Entities/Enemy.h Entities/Player.cpp Entities/Player.h Entities/Bullet.cpp Entities/Bullet.h Entities/Components/Graphics/PlayerGraphicsComponent.cpp Entities/Components/Graphics/PlayerGraphicsComponent.h Entities/Components/Graphics/EnemyGraphicsComponent.cpp Entities/Components/Graphics/EnemyGraphicsComponent.h Generators/EntityGenerator.h Core/Levels/Level.cpp Core/Levels/Level.h Core/Levels/Tutorial.cpp Core/Levels/Tutorial.h Core/States/State.cpp Core/States/State.h Core/States/PauseState.cpp Core/States/PauseState.h Core/States/MenuState.cpp Core/States/MenuState.h Core/States/GameState.cpp Core/States/GameState.h Entities/Components/Input/PlayerInputComponent.cpp Entities/Components/Input/PlayerInputComponent.h)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)

if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(AvalonEngine ${SFML_LIBRARIES})
endif()