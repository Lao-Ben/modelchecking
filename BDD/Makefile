CC= g++

CFLAGS= -Wall -Wextra -pedantic -Wno-long-long -Wno-variadic-macros
CXXFLAGS := -std=c++0x -O3
LDFLAGS := 
BDD= src/Node.o src/BDD.o
MAIN= main.o 
BIN=bdd
TARBALL= bdd
INC_PATH= -I src/

all: $(BIN) demo

check:

$(BIN): $(BDD)
	ar r libbdd.a src/Node.o src/BDD.o
	@echo "The library file named libbdd.a is created"

demo: $(BIN)
	make -C demo/queen
	make -C demo/knight
	make -C demo/graph

%.o: %.cpp
	$(CC) $(INC_PATH) $(CXXFLAGS) -c $< -o $@ $(CFLAGS)

clean:
	@find . -name '*.o' -delete
	@find . -name '*.~' -delete
	@find . -name '#*#' -delete
	@find . -name '.*.swp' -delete
	@find . -name '*.a' -delete
	@echo "cleaned *.o *.a *.~ #*# and .*.swp"

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
