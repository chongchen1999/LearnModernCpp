CMake是一个跨平台的构建工具，以下是一些CMake常用命令：

1. **cmake_minimum_required**
    - **语法**：`cmake_minimum_required(VERSION versionNumber [FATAL_ERROR])`
    - **作用**：指定项目所需的CMake最低版本。如果CMake的当前版本低于指定版本，它会产生一个错误并停止处理。例如`cmake_minimum_required(VERSION 3.10)`表示项目至少需要CMake 3.10版本来构建。
    - **示例场景**：当你的CMake脚本使用了特定版本CMake才引入的新特性时，这个命令就很关键。比如在CMake 3.12中新增了对`target_link_options`命令的支持，若项目中用到这个命令，就需要设置最低版本为3.12。

2. **project**
    - **语法**：`project(projectName [LANGUAGES languageName...])`
    - **作用**：设置项目名称，并可以指定项目所使用的编程语言。它会定义一些变量，如`<projectName>_SOURCE_DIR`和`<projectName>_BINARY_DIR`，方便后续引用项目的源文件目录和构建目录。例如`project(MyProject LANGUAGES CXX)`创建了一个名为`MyProject`的项目，且表明主要使用C++语言。
    - **示例场景**：在构建一个包含C和C++源文件的项目时，可以使用`project(MyMixedProject LANGUAGES C C++)`来明确项目名称和涉及的语言。之后CMake可以根据这些信息为不同语言的源文件调用正确的编译器。

3. **add_executable**
    - **语法**：`add_executable(targetName sourceFiles... )`
    - **作用**：从给定的源文件创建一个可执行目标。例如`add_executable(myApp main.cpp utils.cpp)`会创建一个名为`myApp`的可执行文件，它是由`main.cpp`和`utils.cpp`这两个源文件编译链接而成。
    - **示例场景**：构建一个命令行工具或者一个简单的图形界面应用程序时会用到。假设要构建一个简单的命令行文件拷贝工具，`add_executable(fileCopier fileCopier.cpp fileOperations.cpp)`就可以把相关源文件编译成`fileCopier`这个可执行程序。

4. **add_library**
    - **语法**：`add_library(targetName [STATIC | SHARED | MODULE] sourceFiles... )`
    - **作用**：创建一个库目标，可以是静态库、共享库或者模块库。
    - - `STATIC`：创建一个静态库，在链接时，库中的代码会被复制到最终的可执行文件或者其他库中。
    - - `SHARED`：生成一个共享库（在Windows上是DLL，在Linux上是SO文件），可以在运行时被多个可执行文件共享。
    - - `MODULE`：这种类型的库比较特殊，主要用于动态加载（例如通过`dlopen`函数）。例如`add_library(myLib STATIC myLib.cpp helper.cpp)`会创建一个名为`myLib`的静态库。
    - **示例场景**：在开发一个软件库或者在项目中复用代码时会用到。如果要创建一个数学运算库，并且希望在多个项目中复用，就可以使用`add_library(mathLib STATIC mathFunctions.cpp geometryFunctions.cpp)`。

5. **target_link_libraries**
    - **语法**：`target_link_libraries(targetName libraryNames... )`
    - **作用**：将库链接到目标（可执行文件或者其他库）上。例如，在有一个可执行文件`myApp`和一个库`myLib`的情况下，`target_link_libraries(myApp myLib)`会把`myLib`链接到`myApp`上，这样`myApp`就可以调用`myLib`中的函数。
    - **示例场景**：在构建一个图形界面应用程序并使用第三方图形库（如Qt）时，`target_link_libraries(myGuiApp Qt5::Widgets)`就把Qt的Widgets模块链接到`myGuiApp`上，使得程序能够正常显示图形界面。

6. **include_directories**
    - **语法**：`include_directories(directoryNames... )`
    - **作用**：为编译器添加头文件搜索路径。这使得在编译源文件时，编译器能够找到包含的头文件。例如`include_directories(include)`会将`include`目录添加到头文件搜索路径中，这样在源文件中`#include "header.h"`（假设`header.h`在`include`目录下）就能被正确解析。
    - **示例场景**：当项目的头文件组织在一个单独的目录下时，使用这个命令来告诉编译器头文件的位置。比如一个项目的头文件都放在`src/include`目录下，就可以使用`include_directories(src/include)`。

7. **add_subdirectory**
    - **语法**：`add_subdirectory(sourceDir [binaryDir] [EXCLUDE_FROM_ALL])`
    - **作用**：添加一个子目录到构建系统中。CMake会在该子目录中查找CMakeLists.txt文件并处理它。例如，如果项目有一个子目录`lib`，其中包含了一个库的源文件和对应的CMakeLists.txt，`add_subdirectory(lib)`会处理这个子目录下的构建逻辑。
    - **示例场景**：在大型项目中，通常会把不同功能模块或者库的代码放在不同的子目录下。比如一个游戏项目，有音频处理模块放在`audio`子目录、图形渲染模块放在`graphics`子目录，通过`add_subdirectory(audio)`和`add_subdirectory(graphics)`可以分别构建这些模块。

8. **set**
    - **语法**：`set(variableName value [CACHE type DOC string] [FORCE])`
    - **作用**：设置一个CMake变量。这个变量可以在CMake脚本的后续部分或者在生成的构建系统（如Makefile或Visual Studio项目文件）中使用。例如`set(COMPILE_FLAGS "-Wall -Werror")`设置了一个名为`COMPILE_FLAGS`的变量，它可以用于指定编译选项。
    - **示例场景**：可以根据不同的构建配置（如Debug和Release）来设置变量。在Debug模式下，可以设置`set(DEBUG_FLAGS "-g -O0")`，然后在构建脚本中根据构建类型将这些标志添加到编译器选项中。