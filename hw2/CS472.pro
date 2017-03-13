TEMPLATE = app
TARGET = CS472
QT += widgets opengl 
CONFIG += qt debug_and_release
RESOURCES   = CS472.qrc

Release:OBJECTS_DIR = release/.obj
Release:MOC_DIR     = release/.moc
Debug:OBJECTS_DIR   = debug/.obj
Debug:MOC_DIR       = debug/.moc

INCLUDEPATH     += . geometry camera lighting

win32-msvc2015{
	RC_FILE        += CS472.rc
	LIBS           += -lopengl32
	QMAKE_CXXFLAGS += /MP /Zi
	QMAKE_LFLAGS   += /MACHINE:X64
}

macx{
        QMAKE_SONAME_PREFIX = @executable_path/../Frameworks
        QMAKE_LFLAGS += -Wl,-rpath,@executable_path/../Frameworks
	QMAKE_LFLAGS   -= -mmacosx-version-min=10.8
	QMAKE_LFLAGS   += -mmacosx-version-min=10.9
	QMAKE_CXXFLAGS -= -mmacosx-version-min=10.8
	QMAKE_CXXFLAGS += -mmacosx-version-min=10.9
	QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.9
	ICON = CS472.icns
}

unix:!macx{
	CONFIG += C++11
}

mingw{
	LIBS += -lopengl32
}

# Input
HEADERS +=	MainWindow.h		\
		HW.h			\
		dummy.h			\
		hw0/HW0a.h		\
		hw0/HW0b.h		\
		hw0/HW0c.h		\
		hw1/HW1a.h		\
		hw1/HW1b.h		\
		hw2/HW2a.h		\
		hw2/HW2b.h		\
		geometry/Geometry.h	\
		geometry/Cube.h		\
		geometry/Sphere.h	\
		geometry/Cylinder.h	\
		geometry/Cone.h		\
		geometry/Scene.h	\
		lighting/Light.h	\
		camera/Camera.h
		
SOURCES +=	main.cpp		\ 
		MainWindow.cpp 		\
		HW.cpp			\
		dummy.cpp		\
		hw0/HW0a.cpp		\
		hw0/HW0b.cpp		\
		hw0/HW0c.cpp		\
		hw1/HW1a.cpp		\
		hw1/HW1b.cpp		\
		hw2/HW2a.cpp		\
		hw2/HW2b.cpp		\
		geometry/Cube.cpp	\
		geometry/Sphere.cpp	\
		geometry/Cylinder.cpp	\
		geometry/Cone.cpp	\
		geometry/Scene.cpp	\
		lighting/Light.cpp	\
		camera/Camera.cpp
