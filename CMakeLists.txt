cmake_minimum_required(VERSION 3.26)
project(SqlSelectQueryBuilder)
add_executable(SqlSelectQueryBuilder main.cpp sqlSelectQueryBuilder.h sqlSelectQueryBuilder.cpp)

add_subdirectory("C:\\Users\\oo43\\source\\libs\\libpqxx-7.7.5" libpqxx-build)

target_compile_features(SqlSelectQueryBuilder PRIVATE cxx_std_17)

target_link_libraries(SqlSelectQueryBuilder pqxx)