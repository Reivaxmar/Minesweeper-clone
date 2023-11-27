# Minesweeper-clone
This is a work-in-progress minesweeper clone. This project uses the original minesweeper assets extracted from [The Spriters Resource](https://www.spriters-resource.com/pc_computer/minesweeper/).

## How to run
As it is a CMake project it cna work in almost any machine.

To compile it create a build directory
```bash
mkdir build
cd build
```
And run CMake
```bash
cmake ..
# If you're using MinGW on windows, use the -G "MinGW Makefiles" option
# cmake -G "MinGW Makefiles" ..
# If using Visual Studio search for your version
# cmake -G "Visual Studio 17 2022" ..
```

When its done, you should have everything ready to compile, so make the Makefile and run it
```bash
make
# Use mingw32-make.exe if you're using MinGW or open the ".sln" file if in VS
./game
```

Here's all the commands:
- Windows:
    ```bash
    mkdir build
    cd build
    cmake -G "MinGW Makefiles" ..
    mingw32-make
    ```
    If you're using Visual Studio, just open the solution instead of using Make

- Mac OS / Linux
    ```bash
    mkdir build
    cd build
    cmake ..
    make
    ```
