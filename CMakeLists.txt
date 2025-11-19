cmake_minimum_required(VERSION 3.10)

set(LAB_NAME "lab6")

project(${LAB_NAME})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Добавление опций компиляции
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=maybe-uninitialized")

# Установка Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.0
  TLS_VERIFY false
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(HEADERS
    # NPC
    include/npc/NPCType.h
    include/npc/NPC.h
    include/npc/Bear.h
    include/npc/Werewolf.h
    include/npc/Bandit.h
    
    # Factory
    include/factory/INPCFactory.h
    include/factory/BearFactory.h
    include/factory/WerewolfFactory.h
    include/factory/BanditFactory.h
    include/factory/NPCFactoryRegistry.h
    
    # Visitor
    include/visitor/INPCVisitor.h
    include/visitor/BattleVisitor.h
    include/visitor/PrintVisitor.h
    
    # Observer
    include/observer/IBattleObserver.h
    include/observer/BattleSubject.h
    include/observer/ConsoleObserver.h
    include/observer/FileObserver.h
    
    # Utils
    include/utils/Point.h
    include/utils/BattleEngine.h
    include/utils/FileManager.h
    
    # Editor
    include/editor/NPCContainer.h
    include/editor/DungeonEditor.h
    include/editor/EditorCLI.h
)

# Собираем все исходники
set(SOURCES
    # NPC
    src/npc/NPCType.cpp
    src/npc/NPC.cpp
    src/npc/Bear.cpp
    src/npc/Werewolf.cpp
    src/npc/Bandit.cpp
    
    # Factory
    src/factory/BearFactory.cpp
    src/factory/WerewolfFactory.cpp
    src/factory/BanditFactory.cpp
    src/factory/NPCFactoryRegistry.cpp
    
    # Visitor
    src/visitor/BattleVisitor.cpp
    src/visitor/PrintVisitor.cpp
    
    # Observer
    src/observer/BattleSubject.cpp
    src/observer/ConsoleObserver.cpp
    src/observer/FileObserver.cpp
    
    # Utils
    src/utils/Point.cpp
    src/utils/BattleEngine.cpp
    src/utils/FileManager.cpp
    
    # Editor
    src/editor/NPCContainer.cpp
    src/editor/DungeonEditor.cpp
    src/editor/EditorCLI.cpp
)

add_library(${LAB_NAME}_lib STATIC ${SOURCES} ${HEADERS})
target_include_directories(${LAB_NAME}_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(${LAB_NAME}_exe main.cpp)
target_link_libraries(${LAB_NAME}_exe PRIVATE ${LAB_NAME}_lib)

# Добавление тестов
enable_testing()

add_executable(run_tests
    test/test_point.cpp
    test/test_npc.cpp
    test/test_factory.cpp
    test/test_container.cpp
    test/test_battle.cpp
    test/test_file_manager.cpp
)
target_link_libraries(run_tests PRIVATE ${LAB_NAME}_lib gtest_main)
