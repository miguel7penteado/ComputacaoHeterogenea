# Compilador Ambiente Windows Visual Studio 2022 

> Intel IA32 AMD64

Mapeamento de variáveis de ambiente

```cmd
; mkdir c:\1
; mklink /D C:\1\MSVS         C:\progra~1\MICROS~4\2022\PROFES~1
; mklink /D C:\1\MSVCPP       C:\progra~1\MICROS~4\2022\PROFES~1\VC\Tools\MSVC\1441~1.341 
; mklink /D C:\1\CUDA         C:\progra~1\NVIDIA~2\CUDA\v12.0
; mklink /D C:\1\NVIDIA32     C:\Progra~2\NVIDIA~1
; mklink /D C:\1\NVIDIA       C:\Progra~1\NVIDIA~1
; mklink /D C:\1\WIN10SDK32   C:\Progra~2\WI3CF2~1\10
; mklink /D C:\1\DOTNET       C:\Windows\Microsoft.NET\Framework64
; mklink /D C:\1\INTEL32LIB   C:\Progra~2\COMMON~1\Intel\SHARED~1
; mklink /D C:\1\PERL         C:\Progra~1\Perl\5382~1.2
; mklink /D C:\1\CMAKE        C:\Progra~1\CMake
; mklink /D C:\1\WIX          C:\Progra~2\WIXTOO~1.14
; mklink /D C:\1\GIT          C:\Progra~1\Git
; mklink /D C:\1\R            C:\Progra~1\R\R-44~1.1
; mklink /D C:\1\RTOOLS       C:\Progra~1\R\rtools44
; mklink /D C:\1\QGIS         C:\PROGRA~1\QGIS34~1.15
; mklink /D C:\1\WIX314       C:\Progra~2\WIXTOO~1.14
; mklink /D C:\1\NASM         C:\Progra~1\NASM\216~1.03
; mklink /D C:\1\TCL          C:\Progra~1\TCL\861E57~1.11
; mklink /D C:\1\NODE         C:\PROGRA~1\nodejs


Remove-Item $env:USERPROFILE\AppData\Local\Microsoft\WindowsApps\python*.exe

SET PATH=C:\Windows\system32;C:\Windows;C:\Windows\System32\Wbem;C:\Windows\System32\WindowsPowerShell\v1.0\;C:\Windows\System32\OpenSSH\;%USERPROFILE%\AppData\Local\Microsoft\WindowsApps;C:\1\NASM;C:\1\MSVCPP\bin\HostX64\x64;C:\1\MSVS\Common7\IDE\;C:\1\MSVS\Common7\IDE\CommonExtensions\Microsoft\TestWindow;C:\1\MSVS\Common7\IDE\CommonExtensions\Microsoft\TeamFoundation\TEAMEX~1;C:\1\MSVS\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin;C:\1\MSVS\Common7\IDE\CommonExtensions\Microsoft\CMake\Ninja;C:\1\MSVS\Common7\IDE\VC\Linux\bin\ConnectionManagerExe;C:\1\MSVS\Common7\IDE\VC\VCPackages;C:\1\MSVS\Common7\Tools\;C:\1\MSVS\MSBuild\Current\Bin\amd64;C:\1\MSVS\MSBuild\Current\bin\Roslyn;C:\1\MSVS\VC\vcpkg;C:\1\MSVS\TEAMTO~1\DiagnosticsHub\Collector;C:\1\CUDA\bin;C:\1\CUDA\libnvvp;C:\1\NVIDIA32\PhysX\Common;C:\1\NVIDIA\NVIDIA~2;C:\1\NVIDIA\NSIGHT~1.0;C:\1\WIN10SDK32\WINDOW~1;C:\1\WIN10SDK32\bin\10.0.22621.0\x64;C:\1\WIN10SDK32\bin\x64;C:\1\DOTNETv4.0.30319;C:\1\CMAKE\bin;%INTEL_DEV_REDIST%\redist\intel64\compiler;C:\1\PERL\perl\site\bin;C:\1\PERL\perl\bin;C:\1\PERL\c\bin;C:\1\GIT\cmd;C:\1\GIT\mingw64\bin;C:\1\GIT\usr\bin;C:\1\R\bin\x64;C:\1\RTOOLS;C:\Progra~1\ImageMagick-7.1.0-Q16-HDRI;C:\Progra~1\PuTTY;C:\1\QGIS\apps\qt5\bin;C:\1\QGIS\apps\Python312;C:\1\QGIS\apps\Python312\Scripts;C:\1\QGIS\bin;%USERPROFILE%\AppData\Roaming\Python\Python312\Scripts;C:\Progra~1\FFmpeg\bin;C:\Progra~1\Java\jre1.8.0_431\bin;C:\1\WIX314\bin;C:\1\TCL\bin;C:\1\NODE

SET INCLUDE=C:\1\MSVCPP\include;C:\1\MSVCPP\ATLMFC\include;C:\1\MSVS\VC\Auxiliary\VS\include;C:\1\WIN10SDK32\include\10.0.22621.0\ucrt;C:\1\WIN10SDK32\include\10.0.22621.0\um;C:\1\WIN10SDK32\include\10.0.22621.0\shared;C:\1\WIN10SDK32\include\10.0.22621.0\winrt;C:\1\WIN10SDK32\include\10.0.22621.0\cppwinrt;%USERPROFILE%\source\repos\boost
SET LIB=C:\1\MSVCPP\ATLMFC\lib\x64;C:\1\MSVCPP\lib\x64;C:\1\WIN10SDK32\lib\10.0.22621.0\ucrt\x64;C:\1\WIN10SDK32\lib\10.0.22621.0\um\x64;%USERPROFILE%\source\repos\boost\stage\lib
SET LIBPATH=C:\1\MSVCPP\ATLMFC\lib\x64;C:\1\MSVCPP\lib\x64;C:\1\MSVCPP\lib\x86\store\references;C:\1\WIN10SDK32\UnionMetadata\10.0.22621.0;C:\1\WIN10SDK32\References\10.0.22621.0;C:\1\DOTNETv4.0.30319

SET VCIDEInstallDir=C:\1\MSVS\Common7\IDE\VC\
SET VCINSTALLDIR=C:\1\MSVS\VC\
SET VCPKG_ROOT=C:\1\MSVS\VC\vcpkg
SET VCToolsInstallDir=C:\1\MSVCPP\
SET VCToolsRedistDir=C:\1\MSVS\VC\Redist\MSVC\14.40.33807\
SET VCToolsVersion=14.41.34120
SET VisualStudioVersion=17.0
SET VS170COMNTOOLS=C:\1\MSVS\Common7\Tools\
SET VSCMD_ARG_app_plat=Desktop
SET VSCMD_ARG_HOST_ARCH=x64
SET VSCMD_ARG_TGT_ARCH=x64
SET VSCMD_VER=17.11.4
SET VSINSTALLDIR=C:\1\MSVS\
SET WindowsLibPath=C:\1\WIN10SDK32\UnionMetadata\10.0.22621.0;C:\1\WIN10SDK32\References\10.0.22621.0
SET WindowsSdkBinPath=C:\1\WIN10SDK32\bin\
SET WindowsSdkDir=C:\1\WIN10SDK32\
SET WindowsSDKLibVersion=10.0.22621.0\
SET WindowsSdkVerBinPath=C:\1\WIN10SDK32\bin\10.0.22621.0\
SET WindowsSDKVersion=10.0.22621.0\

SET __DOTNET_ADD_64BIT=1
SET __DOTNET_PREFERRED_BITNESS=64
SET __PSLockDownPolicy=0
SET __VSCMD_PREINIT_PATH=C:\Program Files\ImageMagick-7.1.0-Q16-HDRI;C:\1\CUDA\bin;C:\1\CUDA\libnvvp;C:\1\INTEL32LIB\redist\intel64\compiler;C:\Windows\system32;C:\Windows;C:\Windows\System32\Wbem;C:\Windows\System32\WindowsPowerShell\v1.0\;C:\Windows\System32\OpenSSH\;C:\1\NVIDIA32\PhysX\Common;C:\1\NVIDIA\NVIDIA NvDLISR;C:\Program Files\PuTTY\;C:\Program Files\Git\cmd;C:\1\WIN10SDK32\Windows Performance Toolkit\;C:\1\NVIDIA\Nsight Compute 2022.4.0\;C:\Program Files\CMake\bin;%USERPROFILE%\AppData\Local\Microsoft\WindowsApps;

SET INTEL_DEV_REDIST=C:\1\INTEL32LIB
SET MIC_LD_LIBRARY_PATH=%INTEL_DEV_REDIST%\compiler\lib\mic

SET CUDA_PATH=C:\1\CUDA
SET CUDA_PATH_V12_0=C:\1\CUDA
SET CURL_CA_BUNDLE=C:\Program Files\PostgreSQL\15\ssl\certs\ca-bundle.crt

SET JAVA_HOME=C:\Progra~1\Java\jre1.8.0_431

SET PYTHONHOME=C:\1\QGIS\apps\Python312
SET RETICULATE_PYTHON=%PYTHONHOME%
SET PYTHONUTF8=1

SET R_HOME=C:\1\R
SET RTOOLS44_HOME=C:\Program Files\R\rtools44

SET PERL_HOME=C:\1\PERL
SET PERL5LIB=
SET PERLIB=

SET GDAL_DATA=C:\1\QGIS\apps\gdal\share\gdal
SET GDAL_DRIVER_PATH=C:\1\QGIS\apps\gdal\lib\gdalplugins
SET GS_LIB=C:\1\QGIS\apps\gs\lib

#GDAL_DATA=C:\Program Files\PostgreSQL\15\gdal-data
SET POSTGIS_ENABLE_OUTDB_RASTERS=1
SET POSTGIS_GDAL_ENABLED_DRIVERS=ENABLE_ALL
SET PROJ_LIB=C:\Program Files\PostgreSQL\15\share\contrib\postgis-3.4\proj

SET WIX=C:\1\WIX

SET OPENSSL_CONF=C:\Program Files\PostgreSQL\psqlODBC\etc\openssl.cnf
SET OPENSSL_ENGINES=C:\1\QGIS\lib\engines-1_1
SET SSL_CERT_DIR=C:\1\QGIS\apps\openssl\certs
SET SSL_CERT_FILE=C:\1\QGIS\bin\curl-ca-bundle.crt

SET QT_PLUGIN_PATH=C:\1\QGIS\apps\Qt5\plugins
SET OSGEO4W_ROOT=C:\1\QGIS
SET O4W_QT_BINARIES=C:/PROGRA~1/QGIS34~1.13/apps/Qt5/bin
SET O4W_QT_DOC=C:/PROGRA~1/QGIS34~1.13/apps/Qt5/doc
SET O4W_QT_HEADERS=C:/PROGRA~1/QGIS34~1.13/apps/Qt5/include
SET O4W_QT_LIBRARIES=C:/PROGRA~1/QGIS34~1.13/apps/Qt5/lib
SET O4W_QT_PLUGINS=C:/PROGRA~1/QGIS34~1.13/apps/Qt5/plugins
SET O4W_QT_PREFIX=C:/PROGRA~1/QGIS34~1.13/apps/Qt5
SET O4W_QT_TRANSLATIONS=C:/PROGRA~1/QGIS34~1.13/apps/Qt5/translations

SET WXWIN=%USERPROFILE%\source\repos\wxWidgets
SET PGDIR=C:\Progra~1\POSTGR~1\15
SET OPENSSL=%USERPROFILE%\source\repos\openssl\build
SET LIBSSH2DIR=%USERPROFILE%\source\repos\libssh2\build

SET TCLDIR=C:\1\TCL

```
