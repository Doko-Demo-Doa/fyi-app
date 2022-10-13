# FYI sample app

## Requirements

- Qt 5
- cmake
- Proper build tools installed on specific systems
  - Windows: Visual Studio (**NOT** Visual Studio Code, Community Edition is good enough, latest version is fine)
  - Mac: XCode
  - Linux: May vary. On Debian/Ubuntu, it should be `build-essential` package.

## Get the code

## Configure the project using Cmake

The path may vary, but in Windows it should be something like:

```powershell
"C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe" --no-warn-unused-cli -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -S<YOUR-PROJECT-DIR> -B<YOUR-PROJECT-DIR/build> -G "Visual Studio 17 2022" -T host=x86 -A x64
```

e.g:

```powershell
"C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe" --no-warn-unused-cli -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -Sd:/Projects/CPP/fyi-app -Bd:/Projects/CPP/fyi-app/build -G "Visual Studio 17 2022" -T host=x86 -A x64
```
