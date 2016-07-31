#******************************************************************************#
# BoundingDiameters v0.4
# @author Frank Takes - ftakes@liacs.nl
# @website http://www.liacs.nl/~ftakes/diameter
#*************** consult the README.txt file before using *********************#

CC=g++
CFLAGS=-c -Wall -Wextra -O3 -mcmodel=medium
LDFLAGS=-Wall -Wextra -O3 -mcmodel=medium
HEADERS=graph.h 
SOURCES=main.cc graph.cc bd.cc
OBJECTS=$(SOURCES:.cc=.o)
EXECUTABLE=bd

.PHONY: all clean rebuild tarball

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cc.o:
	$(CC) $(CFLAGS) $< -o $@

clean: 
	rm -f $(EXECUTABLE) $(OBJECTS)

rebuild: clean all   

tarball:
	tar -cvzf bd.tgz $(HEADERS) $(SOURCES) Makefile README


