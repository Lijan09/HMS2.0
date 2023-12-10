cmake_minimum_required(VERSION 3.8.0)
project(CMakeSFMLProject LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

FetchContent_Declare(SQLLite
    GIT_REPOSITORY https://github.com/SRombauts/SQLiteCpp.git
    GIT_TAG master)
FetchContent_MakeAvailable(SQLLite)


add_executable(CMakeSFMLProject 
    src/code/globals.h 
    src/code/functions.h

    src/code/login/adminLogin.cpp 
    src/code/login/doctorLogin.cpp 
    src/code/login/nurseLogin.cpp 
    src/code/login/patientLogin.cpp 
    src/code/login/receptionLogin.cpp 
    
    src/code/main.cpp 
    src/code/mainPage.cpp 
    src/code/admin.cpp 
    src/code/adminAdd.cpp 
    src/code/doctor.cpp 
    src/code/patientData.cpp 
    src/code/reception.cpp
    src/code/patient.cpp
    src/code/nurse.cpp 
    src/code/list.cpp
)
target_link_libraries(CMakeSFMLProject PRIVATE sfml-graphics SQLiteCpp)
target_compile_features(CMakeSFMLProject PRIVATE cxx_std_20)
if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET CMakeSFMLProject POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:CMakeSFMLProject> $<TARGET_FILE_DIR:CMakeSFMLProject> COMMAND_EXPAND_LISTS)
endif()

install(TARGETS CMakeSFMLProject)