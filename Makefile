SUBDIRS := $(wildcard */.)

all:
	(cd signals; make)
	(cd shared-mem; make)
	(cd dup; make)

clean:
	(cd signals; make clean)
	(cd shared-mem; make clean)
	(cd dup; make clean)
