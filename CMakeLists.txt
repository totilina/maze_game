# 添加在文件开头
cmake_minimum_required(VERSION 3.10)
cmake_policy(SET CMP0010 NEW)
project(maze_game)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 添加EasyX配置
set(EASYX_INCLUDE_DIRS "C:/PROGRA~1/mingw64/x86_64-w64-mingw32/include")
set(EASYX_LIBRARIES "C:/PROGRA~1/mingw64/x86_64-w64-mingw32/lib/libeasyx.a")

# 设置 MinGW DLL 路径
set(MINGW_DLL_DIR "C:/PROGRA~1/mingw64/bin")
set(REQUIRED_DLLS
    "${MINGW_DLL_DIR}/libgcc_s_seh-1.dll"
    "${MINGW_DLL_DIR}/libstdc++-6.dll"
    "${MINGW_DLL_DIR}/libwinpthread-1.dll"
)

# 调试信息
message(STATUS "MinGW DLL Directory: ${MINGW_DLL_DIR}")
foreach(DLL ${REQUIRED_DLLS})
    if(EXISTS ${DLL})
        message(STATUS "Found DLL: ${DLL}")
    else()
        message(WARNING "Missing DLL: ${DLL}")
    endif()
endforeach()

# 包含头文件目录
include_directories(${EASYX_INCLUDE_DIRS}
                   ${PROJECT_SOURCE_DIR}/include)

# 收集源文件
file(GLOB_RECURSE SOURCES 
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/*.c")

# 添加 Windows 资源文件
if(WIN32)
    # 设置资源文件路径
    set(RC_FILE "${PROJECT_SOURCE_DIR}/resources/app.rc")
    
    # 确保资源编译器能找到图标文件
    set(CMAKE_RC_FLAGS "${CMAKE_RC_FLAGS} -I${PROJECT_SOURCE_DIR}/resources")
    
    # 添加资源文件到源文件列表
    list(APPEND SOURCES ${RC_FILE})
endif()

# 定义可执行文件
add_executable(${PROJECT_NAME} ${SOURCES})

# 链接库
target_link_libraries(${PROJECT_NAME} PRIVATE
    ${EASYX_LIBRARIES}
    gdi32
    ole32
    uuid
    oleaut32)

# 创建资源目录
set(RESOURCE_DIR "${PROJECT_SOURCE_DIR}/resources")

# 复制依赖文件和资源到构建目录
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    # 复制 MinGW DLL 文件
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${REQUIRED_DLLS}
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
    
    # 复制 EasyX 库
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${EASYX_LIBRARIES}
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
    
    # 复制资源文件
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${RESOURCE_DIR}
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
)

# 安装配置
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib/static)

# 安装 EasyX 库
install(FILES ${EASYX_LIBRARIES}
    DESTINATION bin)

# 安装 MinGW DLL 文件（带权限设置）
install(FILES ${REQUIRED_DLLS}
    DESTINATION bin
    PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
                GROUP_EXECUTE GROUP_READ
                WORLD_EXECUTE WORLD_READ)

# 安装资源文件
install(DIRECTORY ${RESOURCE_DIR}/
    DESTINATION bin
    FILES_MATCHING 
    PATTERN "*.png"
    PATTERN "*.jpg"
    PATTERN "*.jpeg"
    PATTERN "*.ico")

# CPack配置
include(CPack)
set(CPACK_GENERATOR "NSIS")
set(CPACK_PACKAGE_NAME "${PROJECT_NAME}")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "迷宫游戏")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "maze_game")
set(CPACK_NSIS_MODIFY_PATH ON)
set(CPACK_NSIS_ENABLE_UNINSTALL_BEFORE_INSTALL ON)

# 设置安装程序图标
set(CPACK_NSIS_MUI_ICON "${CMAKE_SOURCE_DIR}/resources/icon.ico")
set(CPACK_NSIS_MUI_UNIICON "${CMAKE_SOURCE_DIR}/resources/icon.ico")