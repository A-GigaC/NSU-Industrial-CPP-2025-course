cmake_minimum_required(VERSION 3.20)
project(RegexInterpreter CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Опции для инструментов качества кода
option(ENABLE_CLANG_TIDY "Enable clang-tidy static analysis" OFF)
option(ENABLE_CLANG_FORMAT "Enable clang-format code formatting" OFF)

# Настройка компилятора
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
endif()

# Загрузка Google Test через FetchContent
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

# Основное приложение
add_executable(lab-2
    src/main.cpp
    src/utils.cpp
    src/regex/AST.cpp
    src/regex/Lexer.cpp
    src/regex/Parser.cpp
    src/regex/Matcher.cpp
)

target_include_directories(lab-2 PUBLIC include)

# Юнит-тесты с CTest
enable_testing()

add_executable(test_regex tests/test_regex.cpp
    src/utils.cpp
    src/regex/AST.cpp
    src/regex/Lexer.cpp
    src/regex/Parser.cpp
    src/regex/Matcher.cpp
)
target_include_directories(test_regex PUBLIC include)

# Связываем тесты с Google Test
target_link_libraries(test_regex GTest::gtest GTest::gtest_main)

# Добавляем тесты в CTest
add_test(NAME Regex_AllTests COMMAND test_regex)
add_test(NAME Regex_BasicMatching COMMAND test_regex --gtest_filter="*Basic*")
add_test(NAME Regex_AdvancedFeatures COMMAND test_regex --gtest_filter="*Advanced*")
add_test(NAME Regex_EdgeCases COMMAND test_regex --gtest_filter="*Edge*")
add_test(NAME Regex_ErrorHandling COMMAND test_regex --gtest_filter="*Error*")

# Настройка clang-format
if(ENABLE_CLANG_FORMAT)
    find_program(CLANG_FORMAT_EXE NAMES clang-format)
    if(CLANG_FORMAT_EXE)
        # Получаем список всех исходных файлов
        file(GLOB_RECURSE ALL_SOURCE_FILES
            ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
            ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.h
        )
        
        # Цель для форматирования кода
        add_custom_target(format
            COMMAND ${CLANG_FORMAT_EXE} -i ${ALL_SOURCE_FILES}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            COMMENT "Formatting source code with clang-format"
        )
        
        # Цель для проверки форматирования
        add_custom_target(check-format
            COMMAND ${CLANG_FORMAT_EXE} --dry-run --Werror ${ALL_SOURCE_FILES}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            COMMENT "Checking code formatting with clang-format"
        )
    else()
        message(WARNING "clang-format not found. Formatting targets will not be available.")
    endif()
endif()

# Настройка clang-tidy
if(ENABLE_CLANG_TIDY)
    find_program(CLANG_TIDY_EXE NAMES clang-tidy)
    if(CLANG_TIDY_EXE)
        # Создаем цель для статического анализа
        add_custom_target(tidy
            COMMAND ${CLANG_TIDY_EXE} ${ALL_SOURCE_FILES}
            -config-file=${CMAKE_CURRENT_SOURCE_DIR}/.clang-tidy
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            COMMENT "Running clang-tidy static analysis"
        )
    else()
        message(WARNING "clang-tidy not found. Tidy target will not be available.")
    endif()
endif()

# Дополнительная цель для запуска всех проверок
add_custom_target(quality-check
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running all tests"
    DEPENDS test_regex
)

# Информационное сообщение о доступных целях
message(STATUS "")
message(STATUS "Available targets:")
message(STATUS "  regex_interpreter - main application")
message(STATUS "  test_regex       - run unit tests")
message(STATUS "  format           - format source code (if clang-format available)")
message(STATUS "  check-format     - check code formatting (if clang-format available)")
message(STATUS "  tidy             - static analysis (if clang-tidy available)")
message(STATUS "  quality-check    - run all tests")
message(STATUS "")
message(STATUS "Configure with -DENABLE_CLANG_FORMAT=ON -DENABLE_CLANG_TIDY=ON to enable code quality tools")