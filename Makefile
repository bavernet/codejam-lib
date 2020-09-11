.PHONY: all clean test

all:

clean:
	$(MAKE) clean -C tests

test:
	$(MAKE) clean -C tests
	$(MAKE) -C tests
	tests/testAll
