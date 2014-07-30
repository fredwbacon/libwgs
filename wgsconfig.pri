win32-msvc2012: WGS_INSTALL_PREFIX="C:/local/msvc2012_win32"
win32-msvc2013: WGS_INSTALL_PREFIX="C:/local/msvc2013_win32"

contains(QMAKE_TARGET.arch, x86_64) {
  win32-msvc2012: WGS_INSTALL_PREFIX="C:/local/msvc2012_win64"
  win32-msvc2013: WGS_INSTALL_PREFIX="C:/local/msvc2013_win64"
}

