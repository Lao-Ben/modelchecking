CC= g++

CFLAGS= -Wall -Wextra -pedantic -Wno-long-long -Wno-variadic-macros
CXXFLAGS :=-std=c++0x -O3
LDFLAGS := 
BDD= ../../src/GraphColoring.o
MAIN= main.o 
BIN=graphcoloring
TARBALL= bdd
INC_PATH= -I ../../src/

all: $(BIN)

check:

$(BIN): $(BDD) $(MAIN)
	$(CC) $(CFLAGS) $(CXXFLAGS) $(INC_PATH) $(LDFLAGS) $(BDD) $(MAIN) -L ../../ -lbdd -o $(BIN)
	@echo "The binary file named $(BIN) is created"

%.o: %.cc
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
