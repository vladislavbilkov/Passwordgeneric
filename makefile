CXX = gcc
CXXFLAGS = $$(pkg-config --cflags gtk4) -Wextra -I/path/to/openssl/include

LIBS = $$(pkg-config --libs gtk4) -L/path/to/openssl/lib -lssl -lcrypto

SRC := $(wildcard src/*.c)
OBJ := $(patsubst src/%.c, src/%.o, $(SRC))

src/%.o: src/%.c
	$(CXX) -c $< $(CXXFLAGS) -o $@

compile: $(OBJ)
	mkdir -p bin
	$(CXX) $(LIBS) $(CXXFLAGS) $^ -o bin/$@

clean:
	rm -rf src/*.o bin/

