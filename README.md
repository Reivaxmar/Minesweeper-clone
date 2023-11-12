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
cmake -G "MinGW Makefiles" ..
```

When its done, you should have everything ready to compile, so make the Makefile and run it
```bash
make
# Use mingw32-make.exe if you're on windows
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
- Mac OS / Linux
```bash
mkdir build
cd build
cmake ..
make
```
