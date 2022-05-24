UK_ROOT ?= /home/andrii/.unikraft/unikraft
UK_LIBS ?= /home/andrii/.unikraft/libs
LIBS := $(UK_LIBS)/newlib

all:
	@$(MAKE) -C $(UK_ROOT) A=$(PWD) L=$(LIBS)

$(MAKECMDGOALS):
	@$(MAKE) -C $(UK_ROOT) A=$(PWD) L=$(LIBS) $(MAKECMDGOALS)
