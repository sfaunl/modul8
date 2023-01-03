all: x86_release wasm

BUILD_PRE_W = build/wasm
BUILD_PRE_X = build/x86
TEMPLATE_PRE = html_template

EXE = modulator
IMGUI_DIR = src/ui/imgui
IMPLOT_DIR = src/ui/implot
SRC = src/main.cpp \
src/app.cpp \
src/ui/imgui_renderer.cpp \
src/ui/gui.cpp \
src/ui/gui_modulator.cpp \
src/modulation.cpp \
src/modulator/modulator.cpp
SRC += $(IMGUI_DIR)/imgui.cpp $(IMGUI_DIR)/imgui_demo.cpp $(IMGUI_DIR)/imgui_draw.cpp $(IMGUI_DIR)/imgui_tables.cpp $(IMGUI_DIR)/imgui_widgets.cpp
SRC += $(IMGUI_DIR)/backends/imgui_impl_sdl.cpp $(IMGUI_DIR)/backends/imgui_impl_opengl3.cpp
SRC += $(IMPLOT_DIR)/implot.cpp $(IMPLOT_DIR)/implot_items.cpp
OBJS = $(addsuffix .o, $(basename $(notdir $(SOURCES))))

LIBS += $(LINUX_GL_LIBS) -ldl `sdl2-config --libs`
LIBS += -lm -lGL

CXXFLAGS = -std=c++11 -I$(IMGUI_DIR) -I$(IMGUI_DIR)/backends
CXXFLAGS += `sdl2-config --cflags`
CXXFLAGS += -Wall -Wextra -Wformat -Wformat -pedantic
CXXFLAGS += -s -ffunction-sections -fdata-sections
CXXFLAGS += -I$(IMGUI_DIR) -I$(IMGUI_DIR)/backends
CXXFLAGS += -I$(IMPLOT_DIR)
CFLAGS = $(CXXFLAGS)
LDFLAGS = "-Wl,--gc-sections"

x86_debug:
	mkdir -p $(BUILD_PRE_X)
	g++ $(SRC) -g $(CFLAGS) $(X86DEFINES) $(LIBS) -o $(BUILD_PRE_X)/$(EXE) 

x86_release:
	mkdir -p $(BUILD_PRE_X)
	g++ $(SRC) -Oz $(CFLAGS) $(X86DEFINES) $(LIBS) -o $(BUILD_PRE_X)/$(EXE)

wasm:
	mkdir -p $(BUILD_PRE_W)
	cp $(TEMPLATE_PRE)/index.htm $(BUILD_PRE_W)/.
	em++ $(SRC) $(CFLAGS) $(WASMDEFINES) $(LIBS) -Oz -v \
	-s WASM=1 \
	-s USE_SDL=2 \
	-s FILESYSTEM=0 \
	-s ASSERTIONS=1 \
	-s ASYNCIFY \
	-o $(BUILD_PRE_W)/$(EXE).js

clean:
	rm -f $(BUILD_PRE_W)/*
	rm -f $(BUILD_PRE_X)/*
