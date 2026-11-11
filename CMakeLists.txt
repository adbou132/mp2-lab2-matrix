cmake_minimum_required(VERSION 3.14)
project(MyProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ==========================================
# 1. ПОДКЛЮЧЕНИЕ GOOGLE TEST
# ==========================================
include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# >>>>>>>>>> ЖЕСТКОЕ УКАЗАНИЕ ПУТЕЙ <<<<<<<<<<
# Добавляем пути глобально, чтобы Visual Studio точно их увидела
include_directories(${googletest_SOURCE_DIR}/googletest/include)
include_directories(${googletest_SOURCE_DIR}/googlemock/include)

# ==========================================
# 2. ОСНОВНАЯ ПРОГРАММА
# ==========================================
file(GLOB APP_SOURCES "samples/*.cpp")
if(APP_SOURCES)
    add_executable(my_app ${APP_SOURCES})
    target_include_directories(my_app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
endif()

# ==========================================
# 3. ТЕСТЫ
# ==========================================
enable_testing()
file(GLOB TEST_SOURCES "test/*.cpp")

if(TEST_SOURCES)
    add_executable(my_tests ${TEST_SOURCES})
    
    # Оставляем для надежности
    target_include_directories(my_tests PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${googletest_SOURCE_DIR}/googletest/include
    )
    
    target_link_libraries(my_tests PRIVATE GTest::gtest)
    
    include(GoogleTest)
    add_test(NAME my_tests COMMAND my_tests)
endif()