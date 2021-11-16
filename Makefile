HOST_GCC = g++

GCC ?= $(CC)

PLUGIN = must_tail_call_attribute_plugin.so

GCC_PLUGINS_DIR = $(shell $(GCC) -print-file-name=plugin)

PLUGIN_CXXFLAGS = -O2 -Wall -Wextra -I$(GCC_PLUGINS_DIR)/include \
	-fno-rtti -fno-exceptions -fasynchronous-unwind-tables \
	-fPIC -shared

all: $(PLUGIN)

$(PLUGIN): %.so: %.c
	$(HOST_GCC) $(PLUGIN_CXXFLAGS) $< -o $@

clean: $(PLUGIN)
	rm -f  $(PLUGIN)
