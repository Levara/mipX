cmake_minimum_required(VERSION 2.8)

cmake_policy(SET CMP0043 NEW)

set( TARGET_NAME vmxGUI )

PROJECT(TARGET_NAME)

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})


option(MIPX_USE_VTK_WITH_QT "Turn this 'On' in case you have built VTK with Qt support")


if(MIPX_USE_VTK_WITH_QT)
    set(CMAKE_AUTOMOC ON)
    find_package(Qt5Widgets REQUIRED QUIET)
    qt5_wrap_ui(UISrcs ${UI_FILES} )
endif()


include_directories( ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${PROJECT_SOURCE_DIR}/../mxCore
    ${PROJECT_SOURCE_DIR}/../vmxGUI
)

set( ${TARGET_NAME}_SOURCES
    vmxGUIFilesDialog.cpp
#    vmxGUIMainWidget.cpp
    vmxGUIObject.cpp
    vmxGUIInteractorStyleImage.cpp
    vmxGUIInteractorStyleTrackballCamera.cpp
    vmxGUIListWidget.cpp
    vmxGUIMenu.cpp
    vmxGUIMenuBar.cpp
    vmxGUIButtonGroup.cpp
    vmxGUITextInput.cpp
)

set( ${TARGET_NAME}_HEADERS
    vmxGUIClipBoard.h
    vmxGUIEventDetector.h
    vmxGUIFilesDialog.h
#    vmxGUIMainWidget.h
    vmxGUIObject.h
    vmxGUIInteractorStyleImage.h
    vmxGUIInteractorStyleTrackballCamera.h
    vmxGUIListWidget.h
    vmxGUIMenu.h
    vmxGUIMenuBar.h
    vmxGUIButtonGroup.h
    vmxGUITextInput.h
)

set( ${TARGET_NAME}_TEMPLATES
    ${PROJECT_SOURCE_DIR}/../mxCore/mxArray.h
    ${PROJECT_SOURCE_DIR}/../mxCore/mxList.h
    ${PROJECT_SOURCE_DIR}/../mxCore/mxMatrix.h
    ${PROJECT_SOURCE_DIR}/../mxCore/mxRegularGrid.h
)

set( ${TARGET_NAME}_LIBS
    mxCore
)

add_definitions( -DvmxButtonGroup_EXPORTS
    -DvmxGUIClipBoard_EXPORTS
    -DvmxGUIEventDetector_EXPORTS
    -DvmxGUIFilesDialog_EXPORTS
#    -DvmxGUIMainWidget_EXPORTS
    -DvmxGUIObject_EXPORTS
    -DvmxGUIInteractorStyleImage_EXPORTS
    -DvmxGUIInteractorStyleTrackballCamera_EXPORTS
    -DvmxGUIListWidget_EXPORTS
    -DvmxGUIMenu_EXPORTS
    -DvmxGUIMenuBar_EXPORTS
    -DvmxGUITextInput_EXPORTS
)



if(MIPX_USE_VTK_WITH_QT)
    add_library( ${TARGET_NAME} SHARED ${${TARGET_NAME}_SOURCES} ${${TARGET_NAME}_HEADERS} ${${TARGET_NAME}_TEMPLATES} ${UISrcs} ${QT_WRAP})
    qt5_use_modules(${TARGET_NAME} Core Gui)
else()
    add_library( ${TARGET_NAME} SHARED ${${TARGET_NAME}_SOURCES} ${${TARGET_NAME}_HEADERS} ${${TARGET_NAME}_TEMPLATES})
endif()


target_link_libraries(${TARGET_NAME}
    ${VTK_LIBRARIES}
    ${${TARGET_NAME}_LIBS}
)


install( FILES ${${TARGET_NAME}_HEADERS} ${${TARGET_NAME}_TEMPLATES} DESTINATION ${CMAKE_INSTALL_PREFIX}/include )
install( TARGETS ${TARGET_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX}/lib )
install( TARGETS ${TARGET_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX}/bin )
