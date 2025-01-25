cmake_minimum_required(VERSION 3.14)
project(libESCVP LANGUAGES CXX)

# 選項：是否構建為共享庫
option(libESCVP_BUILD_SHARED "Build shared library" ON)

# 設定庫的名稱和類型
if(libESCVP_BUILD_SHARED)
    set(LIB_TYPE SHARED)  # 動態庫（dll）
else()
    set(LIB_TYPE STATIC)  # 靜態庫
endif()

# 添加庫目標，並將源文件包括進來
add_library(libESCVP ${LIB_TYPE}
        src/ESCVP.cpp
)

# 設置包含目錄，區分開發和安裝接口
target_include_directories(libESCVP
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# 編譯選項與符號定義
if(WIN32)
    target_compile_definitions(libESCVP PRIVATE LIBESCVP_EXPORTS)  # 為 Windows 動態庫設置導出宏
endif()

# 安裝目標
install(TARGETS libESCVP
        EXPORT libESCVPConfig                   # 導出配置
        RUNTIME DESTINATION bin                 # 用於共享庫的 .dll 文件
        LIBRARY DESTINATION lib                 # 用於共享庫的 .lib/.so 文件
        ARCHIVE DESTINATION lib                 # 用於靜態庫的 .lib 文件
        INCLUDES DESTINATION include
)

# 安裝頭文件
install(DIRECTORY include/ DESTINATION include)

# 導出配置，讓用戶能夠使用 find_package 導入此庫
install(EXPORT libESCVPConfig
        NAMESPACE libESCVP::                   # 在 find_package 時使用的命名空間
        DESTINATION lib/cmake/libESCVP         # 安裝的 CMake 配置文件位置
)

# 包含打包目錄
export(TARGETS libESCVP
        NAMESPACE libESCVP::
        FILE "${CMAKE_BINARY_DIR}/libESCVPConfig.cmake"
)
