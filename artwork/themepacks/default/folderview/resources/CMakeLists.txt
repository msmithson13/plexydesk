SET(QT_USE_QTDECLARATIVE ON)

INCLUDE (${QT_USE_FILE})

INCLUDE_DIRECTORIES(
   ${QT_INCLUDES}
)

SET(sourceFiles
	qdeclarativefolderlistmodel.cpp
	plugin.cpp
	support.cpp
)

SET(headerFiles
	qdeclarativefolderlistmodel.h
	support.h
)

SET(QTMOC_SRCS
   qdeclarativefolderlistmodel.h
   support.h
   plugin.h
)
qt4_wrap_cpp(QT_MOC_SRCS ${QTMOC_SRCS})

SET(sourceFiles
   ${QTMOC_SRCS}
   ${sourceFiles}
   ${headerFiles}
)

SET(libs
   ${PLEXY_CORE_LIBRARY}
)

add_library (foldersupport  SHARED ${sourceFiles} ${QT_MOC_SRCS})
#IF(MINGW)
#    SET_TARGET_PROPERTIES(desktopview PROPERTIES
#        IMPORT_SUFFIX ".lib"
#        IMPORT_PREFIX ""
#        PREFIX ""
#    )
#ENDIF(MINGW)

TARGET_LINK_LIBRARIES(
   foldersupport
   ${libs}
)

#work around for ubuntu
if (${QT_IMPORTS_DIR})
  SET(QT_IMPORTS_DIR ${CMAKE_INSTALL_PREFIX}/lib/qt4/imports/)
ENDIF(${QT_IMPORTS_DIR})

#INSTALL (TARGETS foldersupport DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/qt4/imports/Plexy/FolderSupport/)
#INSTALL (FILES ${CMAKE_CURRENT_SOURCE_DIR}/qmldir  DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/qt4/imports/Plexy/FolderSupport/)

INSTALL (TARGETS foldersupport DESTINATION ${QT_IMPORTS_DIR}/Plexy/FolderSupport/)
INSTALL (FILES ${CMAKE_CURRENT_SOURCE_DIR}/qmldir DESTINATION ${QT_IMPORTS_DIR}/Plexy/FolderSupport/)
