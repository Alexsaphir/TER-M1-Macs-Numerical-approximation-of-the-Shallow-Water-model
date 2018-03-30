QT += core gui

QMAKE_CXXFLAGS+= -fopenmp
QMAKE_LFLAGS +=  -fopenmp

SOURCES += \
    main.cpp \
    grid.cpp \
    gridflux.cpp \
    coupledgrid.cpp \
    gridphysical.cpp \
    coupledgridphysical.cpp \
    coupledgridflux.cpp \
    vectorr2.cpp \
    solver.cpp

HEADERS += \
    grid.h \
    gridflux.h \
    coupledgrid.h \
    gridphysical.h \
    coupledgridphysical.h \
    coupledgridflux.h \
    vectorr2.h \
    solver.h
