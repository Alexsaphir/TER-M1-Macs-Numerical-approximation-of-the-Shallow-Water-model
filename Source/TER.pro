QT += core gui

QMAKE_CXXFLAGS+= -fopenmp
QMAKE_LFLAGS +=  -fopenmp

SOURCES += \
    main.cpp \
    grid.cpp \
    gridphysical.cpp \
    gridvirtual.cpp \
    solverlaxfriedrichs.cpp \
    solver.cpp \
    solverlaxfriedrichs2s.cpp \
    coupledgrid.cpp \
    gridflux.cpp \
    coupledgridflux.cpp \
    coupledgridphysical.cpp \
    solverlaxfriedrichssource2s.cpp

HEADERS += \
    grid.h \
    gridphysical.h \
    gridvirtual.h \
    solverlaxfriedrichs.h \
    solver.h \
    solverlaxfriedrichs2s.h \
    coupledgrid.h \
    gridflux.h \
    coupledgridflux.h \
    coupledgridphysical.h \
    solverlaxfriedrichssource2s.h
