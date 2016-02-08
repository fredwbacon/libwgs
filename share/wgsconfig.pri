WGS_VERSION=1.3.0

linux {
  WGS_INSTALL_PREFIX  = $$(HOME)/Frameworks/libwgs/$${WGS_VERSION}
  WGS_FEATURES_PATH   = $$(QMAKEFEATURES)
}

win32 {
  WGS_INSTALL_PREFIX  = $$[QT_INSTALL_PREFIX]
  WGS_FEATURES_PATH   = $$[QT_INSTALL_PREFIX]/mkspecs/features
}

macx {
  WGS_INSTALL_PREFIX   = $$(HOME)/Development/libwgs
  WGS_FEATURES_PATH    = $$(QMAKEFEATURES)
}


######################################################################
# Install parameters
######################################################################

WGS_INSTALL_DOCS      = $${WGS_INSTALL_PREFIX}/doc
WGS_INSTALL_HEADERS   = $${WGS_INSTALL_PREFIX}/include/libwgs
WGS_INSTALL_LIBS      = $${WGS_INSTALL_PREFIX}/lib

