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
    grid2d.cpp \
    grid2dphysical.cpp \
    grid2dflux.cpp \
    solver2d.cpp \
    solver2dcoupledlfsv.cpp \
    coupledgrid2d.cpp \
    coupledgrid2dflux.cpp \
    coupledgrid2dphysical.cpp \
    solvercoupledlfsv2.cpp

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
    grid2d.h \
    grid2dphysical.h \
    grid2dflux.h \
    solver2d.h \
    solver2dcoupledlfsv.h \
    coupledgrid2d.h \
    coupledgrid2dflux.h \
    coupledgrid2dphysical.h \
    solvercoupledlfsv2.h
