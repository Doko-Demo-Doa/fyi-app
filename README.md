# FYI sample app

Simple video app. Used for assessment at FYI.

# Requirements

- Qt 5 or 6. Should be downloaded using [Qt maintenance tool](https://www.qt.io/download)
- cmake
- Proper build tools installed on specific systems
  - **Windows**: [Visual Studio](https://visualstudio.microsoft.com/) (**NOT** Visual Studio Code, Community Edition is more than enough, latest version is fine).
  - **Mac OS**: XCode. Install from AppStore. After installing, run it once to install mandatory components.
  - **Linux**: May vary. On Debian/Ubuntu, it should be `build-essential` package.
- A codec (_MUST_ be installed): Because Qt media backend does not support some video formats (VP9 or H265, which are popular these days). We need to install additional codec (even for end-users). Recommendation is [K-Lite Codec Pack (Basic)](https://codecguide.com/download_k-lite_codec_pack_basic.htm)

# Building

Following guide is for Windows. Mac OS and Linux may differ but not much. The main difference is the build tool we choose (I prefer MSVC over MinGW because Visual Studio is not that bad anymore).

## Install Visual Studio with necessary components

For this app, we choose "Desktop Development with C++" package. It's pretty big (about 6GB) but we need it for Qt to compile and it's much easier than fighting with MinGW command lines. So let's go with it.

![Visual Studio Installer](/images/vs-package.png)

## Get the code

```sh
git clone https://github.com/Doko-Demo-Doa/fyi-app.git
```

### Install Visual Studio

## Make sure `cmake` is in the PATH

- Check the path by using:

```powershell
(gcm cmake).Path
```

if it returns empty string, then add it into your `PATH`. More info can be found [here](https://www.architectryan.com/2018/03/17/add-to-the-path-on-windows-10/) (Windows only). It should come with Visual Studio already if installed. For example:

```powershell
C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe
```

## Make sure Qt is in the PATH too

After Qt installation (using Online Installer or Qt Maintenance Tool). It will be (typically) installed in `C:\Qt` on Windows or `$HOME/Qt` on MacOS. Also after that, install a recent version of Qt 5 or 6 (both should work with this simple app).

![Qt Tool](/images/qt-tool.png)

Note: Be sure to add the `bin` folder. It should be something like this (`C:\Qt\<qt_version>\<compiler_version>\bin`):

e.g:

```
C:\Qt\5.15.2\msvc2019_64\bin
```

You may need to restart any Powershell / Command line / Terminal currently opening to take effect.

## Create the build folder

Note: This also works with PowerShell on Windows

```bash
mkdir build
```

_Reason_: This is just a convention. By default CMake generates a lot of files/folders into working directory.
They should be in a build folder instead and also should be ignored by version control (typically Git).

## Configure the project using Cmake

The path may vary, but in Windows it should be something like (assuming you installed Visual Studio 17, which is 2022):

Following command can be executed in [PowerShell](https://learn.microsoft.com/en-us/powershell/):

```powershell
Set-Location build
cmake --no-warn-unused-cli -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -S<YOUR-PROJECT-DIR> -B<YOUR-PROJECT-DIR/build> -G "Visual Studio 17 2022" -T host=x86 -A x64
```

or even more simple:

```powershell
Set-Location build
cmake ..
Set-Location ..
```

Build files will be generated and the app will be built in `build/Debug/FYIApp.exe`.

For the sake of simplicity, a `debug.ps1` script was pre-made to automatically configure and run the debug app on Windows. Just run this command in project's folder. Build files are located in `build` folder:

```powershell
./debug.ps1
```

If everything was installed correctly. There should be an `exe` file in `build/Debug/`

# Known issues

- Codec should be bundled or embedded in the app (through dynamic or static linking).
- Slider is not quite smooth, it jumps when playing, not actually sliding.
