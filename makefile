NAME     = batterystatus
CC       = gcc
SRC      = ${NAME}.c
OBJ      = ${SRC:.c=.o}

# You may need to change these paths based on your system
X11INC   = /usr/include/X11
X11LIB   = /usr/lib/X11

INCS     = -I${X11INC}
LIBS     = -L${X11LIB} -lX11
CFLAGS   = -std=c99 -pedantic -Wall -Wno-deprecated-declarations -Os ${INCS}
LDFLAGS  = ${LIBS}
BINDIR   = /usr/bin
 
all: options ${NAME}
 
# Print flags and options
options:
	@echo Build options:
	@echo "CC       = ${CC}"
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo ---------

.c.o:
	@echo "Compiling $<"
	@${CC} -c ${CFLAGS} $<

${NAME}: ${OBJ}
	@echo "Linking $@"
	@${CC} -o $@ ${OBJ} ${LDFLAGS}

clean:
	@echo "Cleaning"
	@rm -f ${NAME} ${OBJ}

install: all
	@echo "Copying ${NAME} to ${BINDIR}"
	@cp -f ${NAME} ${BINDIR}

uninstall:
	@echo "Removing ${NAME} from ${BINDIR}"
	@rm ${BINDIR}/${NAME}

