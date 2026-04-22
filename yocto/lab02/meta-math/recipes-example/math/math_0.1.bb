SUMMARY = "My math custom library"
DESCRIPTION = "My math custom library"
LICENSE = "CLOSED"

SRC_URI = "file://math.c  file://math.h"

do_compile(){
    ${CC} ${LDFLAGS} -c ${WORKDIR}/math.c -o ${WORKDIR}/math.o
    ${AR} -rcs ${WORKDIR}/libmath.a ${WORKDIR}/math.o
}

do_install(){
    install -d ${D}${includedir}
    install -m 0755 ${WORKDIR}/math.h ${D}${includedir}
    install -d ${D}${libdir}
    install -m 0755 ${WORKDIR}/libmath.a ${D}${libdir}
}

PROVIDES += "libmath"
PROVIDES += "fady"

# IMAGE_FEATURES:append= " wiston"