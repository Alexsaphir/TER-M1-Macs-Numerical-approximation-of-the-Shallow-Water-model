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
    solver.cpp \
    solvercoupledlf0.cpp \
    solvercoupledlfsv.cpp \
    solvercoupledlfsv2.cpp \
    cachesolver.cpp \
    solverburger.cpp

HEADERS += \
    grid.h \
    gridflux.h \
    coupledgrid.h \
    gridphysical.h \
    coupledgridphysical.h \
    coupledgridflux.h \
    vectorr2.h \
    solver.h \
    solvercoupledlf0.h \
    solvercoupledlfsv.h \
    solvercoupledlfsv2.h \
    cachesolver.h \
    solverburger.h
