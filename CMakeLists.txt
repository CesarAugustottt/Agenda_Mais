cmake_minimum_required(VERSION 3.16)
project(Agenda_Mais LANGUAGES CXX)

# Ativa a automação do Qt automaticamente
set(CMAKE_AUTOUX ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Encontra o Qt no seu sistema automaticamente
find_package(Qt6 REQUIRED COMPONENTS Widgets Core Gui)

# Coleta todos os seus arquivos de código (src e interface)
file(GLOB_RECURSE SOURCES 
    "src/*.cpp"
    "src/*.h"
    "interface/*.cpp"
    "interface/*.h"
)

# Cria o executável final apontando para o seu main na subpasta
add_executable(Agenda_Mais ${SOURCES})
# Linca as bibliotecas do Qt
target_link_libraries(Agenda_Mais PRIVATE Qt6::Widgets Qt6::Core Qt6::Gui)