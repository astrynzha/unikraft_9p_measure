UK_ROOT ?= /home/strynzha/.unikraft/unikraft
UK_LIBS ?= /home/strynzha/.unikraft/libs
LIBS := $(UK_LIBS)/libnewlib

all:
	@$(MAKE) -C $(UK_ROOT) A=$(PWD) L=$(LIBS)

$(MAKECMDGOALS):
	@$(MAKE) -C $(UK_ROOT) A=$(PWD) L=$(LIBS) $(MAKECMDGOALS)
