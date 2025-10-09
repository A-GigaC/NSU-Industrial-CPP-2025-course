# Поиск GoogleTest
find_package(GTest REQUIRED)

# Включение директорий для тестов
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${GTEST_INCLUDE_DIRS})

# Связывание тестов с библиотеками
target_link_libraries(test_regex ${GTEST_LIBRARIES} pthread)