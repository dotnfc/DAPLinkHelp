#DAPLink Experimental_compiler

<hr size='1'>
<br />
# 在 Windows 上简化操作说明
* 备齐 python3.x, keil mdk(argcc, armclang 就有了)，外补 gcc_arm

* 从下面地址获取 gnu-make, cmake

```
  https://cmake.org/download/
  http://gnuwin32.sourceforge.net/packages/make.htm
  https://sourceforge.net/projects/getgnuwin32/files/
``` 
 
* 设置命令行路径
```
set path=D:\arm\cmake\win32\bin;%path%
set path=D:\arm\gnumake\bin;%path%
set path=D:\arm\armgcc9\bin;%path%
set path=d:\arm\MDK5\ARM\ARMCC\bin;%path%
set path=d:\arm\MDK5\ARM\ARMCLANG\bin;%path%
```

 然后参照 下面的官方说明编译、链接即可

<hr size='1'>

<br />
# Warning: Experimental branch (official comments)
<hr size='1'>
This is is an experimental branch:
- It adds support for the GCC (`gcc_arm`) and ARMC6 (`armclang`) compilers.
- It focuses on `progen` support using `make` and `cmake`.
- It will be frequently rebased.

## Setup

DAPLink sources are compiled using `progen` (from [project-generator](https://github.com/project-generator/project_generator)) which can be run on Linux, MacOS and Windows.

Install the necessary tools listed below. Skip any step where a compatible tool already exists.

* Install [Python 3](https://www.python.org/downloads/) . Add to PATH.
* Install [Git](https://git-scm.com/downloads) . Add to PATH.
* Install a compiler:
    * [GNU Arm Embedded Toolchain](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads) . This compiler will be identified as `gcc_arm`.
    * [Arm Compiler 6](https://developer.arm.com/tools-and-software/embedded/arm-compiler) . This compiler will be identified as `armclang`. Only supported on Linux and Windows.
    * [Keil MDK](https://developer.arm.com/tools-and-software/embedded/keil-mdk) or [Arm Compiler 5](https://developer.arm.com/tools-and-software/embedded/arm-compiler/downloads/legacy-compilers#arm-compiler-5). This compiler will be identified as `armcc`. Only supported on Linux and Windows.
* Install `make` (tested with [GNU Make](https://www.gnu.org/software/make)). [CMake](https://cmake.org) can alternatively be used in conjunction with different implementations of `make` as well as [ninja](https://ninja-build.org).
* Install virtualenv in your global Python installation eg: `pip install virtualenv`.

**Step 1.** Initial setup.

Get the sources and create a virtual environment

```
$ git clone https://github.com/ARMmbed/DAPLink
$ cd DAPLink
$ git checkout experimental_compilers
$ virtualenv venv
```

## Activate virtual environment
**Step 2.** Activate the virtual environment and update requirements. This is necessary when you open a new shell. **This should be done every time you pull new changes**

```
$ venv/Scripts/activate   (For Linux)
$ venv/Scripts/activate.bat   (For Windows)
(venv) $ pip install -r requirements.txt
```

## Build
**This should be done every time you pull new changes**

You can use the `progen` command-line tool from project-generator or the `tools/progen_compile.py` wrapper tool.

**Step 4.1.** Using `progen_compile.py`

```
(venv) $ python tools/progen_compile.py [-t <tool>] [--clean] [-v] [--parallel] [<project> [<project> ...]]
```

* `-t <tool>`: choose the toolchain to build. The default is `make_gcc_arm`. Other options tested are `make_gcc_arm`, `make_armclang`, `make_armcc`, `cmake_gcc_arm`, `cmake_armclang`, `cmake_armcc`.
* `--clean`: will clear existing compilation products and force recompilation of all files.
* `-v`: will make compilation process more verbose (typically listing all commands with their arguments)
* `--parallel`: enable parallel compilation within a project (projects are compiled sequentially).
* `<project>`: target project to compile (e.g. `stm32f103xb_bl`, `lpc11u35_if`), if none is specified all (140 to 150) projects will be compiled.

**Step 4.2.** Using `progen` with `make`

The following command combines generation and compilation:

```
(venv) $ progen generate -t make_gcc_arm -p <project> -b
```

Alternatively one can separate those task:
```
(venv) $ progen generate -t make_gcc_arm -p <project>
(venv) $ make -C projectfiles/make_gcc_arm/<project> [<target>] [VERBOSE=1]
```
Where:
* `<project>`: target project to compile (e.g. `stm32f103xb_bl`, `lpc11u35_if`).
* `<target>`: build target, can be `all`, `clean` or `help`.
* `VERBOSE=1`: display additional compilation information.

**Step 4.3.** Using `progen` with `cmake`

The following command combines generation and compilation:

```
(venv) $ progen generate -t cmake_gcc_arm -o generator=<generator> -p <project> -b
```
* `<generator>`: use `CMake` generators among the following options:
    * `make` (`Unix Makefiles`)
    * `mingw-make` (`MinGW Makefiles`)
    * `msys-make` (`MSYS Makefiles`, untested)
    * `ninja` (`Ninja`)
    * `nmake` (`NMake Makefiles`, untested)
* `<project>`: target project to compile (e.g. `stm32f103xb_bl`, `lpc11u35_if`).

# End of warning
<hr size='1'>
<br />
