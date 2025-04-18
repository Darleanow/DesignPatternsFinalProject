# TechMa

## Installation Guide

### Prerequisites

- Qt 6.9.0
- Gcc / Clang

### Guide

First, clone the repo:


```bash
git clone https://github.com/username/TechMa.git
```

Then, make a build directory:

```bash
cd DesignPatternsFinalProject
mkdir build && cd build
```

Proceed by generating the makefiles (adapt your Qt path)

```bash
cmake .. \
-DCMAKE_PREFIX_PATH="/home/devel/Qt/6.9.0/gcc_64/lib/cmake" \
-DCMAKE_FIND_ROOT_PATH="/home/devel/Qt/6.9.0/gcc_64" \
-DCMAKE_FIND_ROOT_PATH_MODE_PACKAGE=ONLY
```

Then, build the project:

```bash
cmake --build .
```

You can then run it by entering the following:

```bash
./TechMa
```
