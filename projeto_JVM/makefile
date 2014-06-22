COMPILER = g++
CFLAGS   = -Wextra -g
INCLUDE  = -Iinclude
TARGET   = prog
SOURCES_C   = $(wildcard *.c)
SOURCES_CPP = $(wildcard *.cpp)
SOURCES_ASM = $(wildcard *.asm)
OBJECTS_C   = $(SOURCES_C:.c=.obj)
OBJECTS_CPP = $(SOURCES_CPP:.cpp=.obj)
OBJECTS_ASM = $(SOURCES_ASM:.asm=.obj)
OBJECTS  = $(OBJECTS_ASM) $(OBJECTS_CPP) $(OBJECTS_C)
DEPENDS  = $(OBJECTS_C:.obj=.d) $(OBJECTS_CPP:.obj=.d) $(OBJECTS_ASM:.obj=.d)

REMOVE  = del
#REMOVE  = rm

$(TARGET): $(OBJECTS)
	$(COMPILER) -o $@ $^ 

%.obj: %.c
	$(COMPILER) $(CFLAGS) $(INCLUDE) -o $@ -c $<
	
%.obj: %.cpp
	$(COMPILER) $(CFLAGS) $(INCLUDE) -o $@ -c $<

%.obj: %.asm
	nasm -f win32 -o $@ $<

all: clean $(TARGET)

clean:
	$(REMOVE) -f $(OBJECTS) $(DEPENDS) $(TARGET)
	
test:
	echo $(OBJECTS)
