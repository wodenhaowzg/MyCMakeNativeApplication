# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.
cmake_minimum_required(VERSION 3.4.1)

# 定义项目名
project("VideoCodec")

# 设置输出目录
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY /Users/wangzhiguo/Downloads/Learns/Projects/Owner/MyCXXApplication/app/libs/armeabi-v7a/)

# 为所有 c/c++ 编译器设置编译选项，可以把公用的选项放到这里，只能设置一次，不能重复设置，后者会覆盖前者
add_compile_options("-frtti -fexceptions")
# 为 c++ 编译器设置编译选项，只能设置一次，不能重复设置，后者会覆盖前者
set(CMAKE_CXX_FLAGS "-std=c++11 -w")
# 为 c 编译器设置编译选项，只能设置一次，不能重复设置，后者会覆盖前者
set(CMAKE_C_FLAGS "-w")
set(CMAKE_ANDROID_NDK /Users/wangzhiguo/Downloads/Learns/Developer-Tools/ndk-versions/android-ndk-r14b)

# 将指定目录中的头文件包含到查找路径中
include_directories("${PROJECT_SOURCE_DIR}/header/base")
#查找当前目录所有源文件 并将名称保存到 DIR_SRCS 变量，不能查找子目录
aux_source_directory(./src NATIVE_DIR_SRCS)

# 从 ndk 中查找库
find_library(log-lib log)
find_library(mediandk-lib mediandk)

# 添加要编译到库
add_library( # Sets the name of the library.
        native-lib
        SHARED
        ${NATIVE_DIR_SRCS})

target_link_libraries( # Specifies the target library.
        native-lib
        ${log-lib}
        ${mediandk-lib})