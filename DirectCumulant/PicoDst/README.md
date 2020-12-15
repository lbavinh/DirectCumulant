# PicoDst
Data format fot the Flow Analysis at MPD(NICA)

## Installation

- Get the source code:
```bash
git clone https://devel.mephi.ru/PEParfenov/PicoDst.git
```

- Create build directory and build project:
```bash
cd PicoDst/
mkdir build/
cd build/
cmake ..
make
```
`CMakeLists.txt` file automatically checks if FairRoot is installed.
    - if `FairRoot` is installed both `libPicoDst.so` and `PicoDstConverter` will be compiled
    - if `FairRoot` is not installed only `libPicoDst.so` will be compiled

## Usage

##### PicoDst data format

After installation `setPicoDst.sh` will be generated. This script contains most of the needed information for the system to find PicoDst library.
For comfortable usage of the `PicoDst` package (to automatically load `libPicoDst.so` in every `ROOT` session, export usefull environment variables and aliases in the system), source `setPicoDst.sh`:

```bash
source setPicoDst.sh
```
It also contains usefull aliases for all executables.

##### Basic information about `PicoDst` package: `PicoDst-config`

Like `root-config` command, `PicoDst-config` contains information about version and paths to the source code and build directories. After sourcing `setPicoDst.sh` one can just use the following command in bash:
```bash
PicoDst-config --version --incdir --srcdir --bindir
```

##### Convert `MpdDst` data to `PicoDst`:

If `FairRoot` (and `MpdRoot`) is installed `PicoDstConverter` is compiled. After sourcing `setPicoDst.sh` one can use command:

```bash
PicoDstConverter -i input_mpddst.root -o output_picodst.root
```
