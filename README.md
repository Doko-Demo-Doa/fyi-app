# FYI sample app

## Requirements

- Qt 5. Should be downloaded using [Qt maintenance tool](https://www.qt.io/download)
- cmake
- Proper build tools installed on specific systems
  - Windows: Visual Studio (**NOT** Visual Studio Code, Community Edition is good enough, latest version is fine)
  - Mac OS: XCode. Install from AppStore
  - Linux: May vary. On Debian/Ubuntu, it should be `build-essential` package.

## Get the code

## Make sure `cmake` is in the PATH

- Check the path by using:

```powershell
(gcm cmake).Path
```

if it returns empty string, then add it into your PATH. It should come with Visual Studio already if installed. For example:

```powershell
C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe
```

## Create the build folder

Note: This also works with PowerShell on Windows

```bash
mkdir build
```

## Configure the project using Cmake

The path may vary, but in Windows it should be something like (assuming you installed Visual Studio 17, which is 2022):

```powershell
cmake --no-warn-unused-cli -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -S<YOUR-PROJECT-DIR> -B<YOUR-PROJECT-DIR/build> -G "Visual Studio 17 2022" -T host=x86 -A x64
```

For the sake of simplicity, a `debug.ps1` script was pre-made to automatically configure and run the debug app on Windows. Just run this command in project's folder. Build files are located in `build` folder:

```powershell
.\debug.ps1
```
