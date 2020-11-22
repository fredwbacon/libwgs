linux {
  WGS_INSTALL_PREFIX  = $$(HOME)/Frameworks/libwgs/$${VERSION}
  WGS_FEATURES_PATH   = $$(QMAKEFEATURES)
}

win32 {
  contains(QMAKE_TARGET.arch,x86_64) {
    WGS_INSTALL_PREFIX   = D:/local/msvc2019_win64
  } else {
    WGS_INSTALL_PREFIX   = D:/local/msvc2019_win32
  }
  WGS_FEATURES_PATH   = $$(QMAKEFEATURES)
}

macx {
  WGS_INSTALL_PREFIX   = $$(HOME)/Developer/libwgs/$${VERSION}
  WGS_FEATURES_PATH    = $$(QMAKEFEATURES)
}


######################################################################
# Install parameters
######################################################################

WGS_INSTALL_DOCS      = $${WGS_INSTALL_PREFIX}/doc
WGS_INSTALL_HEADERS   = $${WGS_INSTALL_PREFIX}/include/libwgs
WGS_INSTALL_LIBS      = $${WGS_INSTALL_PREFIX}/lib

