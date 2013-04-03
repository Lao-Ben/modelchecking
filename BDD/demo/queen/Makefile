CC= g++

CFLAGS= -Wall -Wextra -pedantic -Wno-long-long -Wno-variadic-macros -Ofast
CXXFLAGS :=-std=c++0x -O3
LDFLAGS := 
BDD= ../../src/Queens.o
MAIN= main.o 
BIN=queen
TARBALL= bdd
INC_PATH= -I../../include

all: $(BIN)

check:

$(BIN): $(BDD)
	$(CC) $(CFLAGS) $(CXXFLAGS) $(INC_PATH) $(LDFLAGS) $(BDD) -lbdd -o $(BIN) main.cpp
	@echo "The binary file named $(BIN) is created"

main.o:
	cp ../../libbdd.a .
	$(CC) $(INC_PATH) $(CXXFLAGS) $(BDD) -lbdd -c main.cpp -o main.o

%.o: %.cpp
	$(CC) $(INC_PATH) $(CXXFLAGS) -c $< -o $@ $(CFLAGS)

clean:
	@find . -name '*.o' -delete
	@find . -name '*.~' -delete
	@find . -name '#*#' -delete
	@find . -name '.*.swp' -delete
	@echo "cleaned *.o *.~ #*# and .*.swp"

distclean: clean
	@rm -f $(BIN)
	@rm -rf ./doc/html ./doc/latex
	@find . -name "lefebv_f-$(TARBALL).tar.bz2" -delete
	@echo "cleaned *.a *.so doc/html and doc/latex"

dist: distclean
	@tar -cjvf "lefebv_f-$(TARBALL).tar.bz2" ./* \
			--exclude ".git" \
			--exclude "lefebv_f-$(TARBALL).tar.bz2"
cleano:
	@find -name '*.o' -delete
	@echo "Object files deleted"
