CC=g++
CFLAGS=-c -Wall -std=c++0x
LDFLAGS=
INCPATH       = -I. -I-L/tinyxml/ 
LIBS          = $(SUBLIBS) -lGLU -lGL -lglut 

SOURCES       = main.cpp \
		drawer.cpp \
		config.cpp \
		tinyxml/tinystr.cpp \
		tinyxml/tinyxml.cpp \
		tinyxml/tinyxmlerror.cpp \
		tinyxml/tinyxmlparser.cpp \
		scrollbar.cpp \
		tree.cpp \
		scene.cpp \
		coordmap.cpp \
		point.cpp \
		node.cpp \
		inode.cpp \
		color.cpp 

OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=Gl_Tree


all: $(SOURCES) $(EXECUTABLE)


$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) $(LIBS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
