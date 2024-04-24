# Alternative GNU Make workspace makefile autogenerated by Premake

ifndef config
  config=debug
endif

ifndef verbose
  SILENT = @
endif

ifeq ($(config),debug)
  packer_config = debug
  microui_config = debug
  shaderc_config = debug
  engine_config = debug
  runtime_config = debug
  editor_config = debug

else ifeq ($(config),release)
  packer_config = release
  microui_config = release
  shaderc_config = release
  engine_config = release
  runtime_config = release
  editor_config = release

else ifeq ($(config),dist)
  packer_config = dist
  microui_config = dist
  shaderc_config = dist
  engine_config = dist
  runtime_config = dist
  editor_config = dist

else
  $(error "invalid configuration $(config)")
endif

PROJECTS := packer microui shaderc engine runtime editor

.PHONY: all clean help $(PROJECTS) 

all: $(PROJECTS)

packer:
ifneq (,$(packer_config))
	@echo "==== Building packer ($(packer_config)) ===="
	@${MAKE} --no-print-directory -C packer -f Makefile config=$(packer_config)
endif

microui:
ifneq (,$(microui_config))
	@echo "==== Building microui ($(microui_config)) ===="
	@${MAKE} --no-print-directory -C engine/lib/microui -f Makefile config=$(microui_config)
endif

shaderc:
ifneq (,$(shaderc_config))
	@echo "==== Building shaderc ($(shaderc_config)) ===="
	@${MAKE} --no-print-directory -C engine/lib/shaderc/build -f Makefile config=$(shaderc_config)
endif

engine: microui packer
ifneq (,$(engine_config))
	@echo "==== Building engine ($(engine_config)) ===="
	@${MAKE} --no-print-directory -C engine -f Makefile config=$(engine_config)
endif

runtime: engine
ifneq (,$(runtime_config))
	@echo "==== Building runtime ($(runtime_config)) ===="
	@${MAKE} --no-print-directory -C runtime -f Makefile config=$(runtime_config)
endif

editor: engine
ifneq (,$(editor_config))
	@echo "==== Building editor ($(editor_config)) ===="
	@${MAKE} --no-print-directory -C editor -f Makefile config=$(editor_config)
endif

clean:
	@${MAKE} --no-print-directory -C packer -f Makefile clean
	@${MAKE} --no-print-directory -C engine/lib/microui -f Makefile clean
	@${MAKE} --no-print-directory -C engine/lib/shaderc/build -f Makefile clean
	@${MAKE} --no-print-directory -C engine -f Makefile clean
	@${MAKE} --no-print-directory -C runtime -f Makefile clean
	@${MAKE} --no-print-directory -C editor -f Makefile clean

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
	@echo "   packer"
	@echo "   microui"
	@echo "   shaderc"
	@echo "   engine"
	@echo "   runtime"
	@echo "   editor"
	@echo ""
	@echo "For more information, see https://github.com/premake/premake-core/wiki"