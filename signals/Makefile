SRCS := $(wildcard *.c)

PROGS := $(patsubst %.c,%.out,$(SRCS))

GCC := gcc

all: $(PROGS)

%.out: %.c
	$(GCC) -o $@ $<

clean:
	rm *.out

.PHONY: clean
