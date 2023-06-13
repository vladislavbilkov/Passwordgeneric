CXX = gcc
CXXFLAGS = $$(pkg-config --cflags gtk4)

LIBS = $$(pkg-config --libs gtk4)

SRC := $(wildcard src/*.c)
OBJ := $(patsubst src/%.c, src/%.o, $(SRC))

src/%.o: src/%.c
	$(CXX) -c $< $(CXXFLAGS) -o $@

compile: $(OBJ)
	mkdir -p bin
	$(CXX) $(LIBS) $(CXXFLAGS) $^ -o bin/$@

clean:
	rm -rf src/*.o bin/

