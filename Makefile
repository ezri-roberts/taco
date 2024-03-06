# GNU Make workspace makefile autogenerated by Premake

.NOTPARALLEL:

ifndef config
  config=debug
endif

ifndef verbose
  SILENT = @
endif

ifeq ($(config),debug)
  raylib_config = debug
  taco_config = debug
  sandbox_config = debug
endif
ifeq ($(config),release)
  raylib_config = release
  taco_config = release
  sandbox_config = release
endif
ifeq ($(config),dist)
  raylib_config = dist
  taco_config = dist
  sandbox_config = dist
endif

PROJECTS := raylib taco sandbox

.PHONY: all clean help $(PROJECTS) 

all: $(PROJECTS)

raylib:
ifneq (,$(raylib_config))
	@echo "==== Building raylib ($(raylib_config)) ===="
	@${MAKE} --no-print-directory -C taco/lib/raylib -f Makefile config=$(raylib_config)
endif

taco: raylib
ifneq (,$(taco_config))
	@echo "==== Building taco ($(taco_config)) ===="
	@${MAKE} --no-print-directory -C taco -f Makefile config=$(taco_config)
endif

sandbox: taco
ifneq (,$(sandbox_config))
	@echo "==== Building sandbox ($(sandbox_config)) ===="
	@${MAKE} --no-print-directory -C sandbox -f Makefile config=$(sandbox_config)
endif

clean:
	@${MAKE} --no-print-directory -C taco/lib/raylib -f Makefile clean
	@${MAKE} --no-print-directory -C taco -f Makefile clean
	@${MAKE} --no-print-directory -C sandbox -f Makefile clean

help:
	@echo "Usage: make [config=name] [target]"
	@echo ""
	@echo "CONFIGURATIONS:"
	@echo "  debug"
	@echo "  release"
	@echo "  dist"
	@echo ""
	@echo "TARGETS:"
	@echo "   all (default)"
	@echo "   clean"
	@echo "   raylib"
	@echo "   taco"
	@echo "   sandbox"
	@echo ""
	@echo "For more information, see https://github.com/premake/premake-core/wiki"