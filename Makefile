CC 		= g++
CFLAGS 	= -c -L/usr/local/lib -L/usr/lib64 -I./src/include -std=c++11 -O2

LINKER 	= gcc
BIN 	= 2dlight
LFLAGS 	= -o $(BIN) -lstdc++ -lm -lSDL2 -lGL -lGLEW

HEADERS = \
./src/include/gfx.hpp \
./src/include/shader.hpp \
./src/include/object.hpp \
./src/include/math/math.hpp \
./src/include/math/vec2.hpp \
./src/include/math/vec3.hpp \
./src/include/math/vec4.hpp \
./src/include/math/mat2.hpp \
./src/include/math/mat3.hpp \
./src/include/math/mat4.hpp \
./src/include/math/poly2d.hpp

OBJS 	= \
./obj/main.o \
./obj/sdl_handler.o \
./obj/gl_handler.o \
./obj/shader.o \
./obj/object.o \
./obj/mat3.o \
./obj/mat4.o \
./obj/poly2d.o

default: prepare $(OBJS)
	$(LINKER) $(OBJS) $(LFLAGS)

prepare:
	mkdir -p obj/

run: default
	./$(BIN)

obj/main.o: src/main.cpp $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@

obj/sdl_handler.o: src/sdl_handler.cpp $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@

obj/gl_handler.o: src/gl_handler.cpp $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@

obj/shader.o: src/shader.cpp $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@

obj/object.o: src/object.cpp $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@

obj/mat3.o: src/math/mat3.cpp $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@

obj/mat4.o: src/math/mat4.cpp $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@

obj/poly2d.o: src/math/poly2d.cpp $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@
