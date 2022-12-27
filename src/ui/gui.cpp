// Dear ImGui: standalone example application for SDL2 + OpenGL
// (SDL is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan/Metal graphics context creation, etc.)
// If you are new to Dear ImGui, read documentation from the docs/ folder + read the top of imgui.cpp.
// Read online: https://github.com/ocornut/imgui/tree/master/docs


#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/html5.h>
#endif

#include "../app.h"
#include "gui.h"
#include "gui_modulator.h"

int window_width = 1200;
int window_height = 720;

// Init imgui
Gui *gui_init()
{
// get html5 canvas size
#ifdef __EMSCRIPTEN__
    window_width = EM_ASM_INT_V(return window.innerWidth 
        || document.documentElement.clientWidth 
        || document.body.clientWidth
    );
    window_height = EM_ASM_INT_V(return window.innerHeight
        || document.documentElement.clientHeight
        || document.body.clientHeight
    );
    window_width = (window_width * 7) / 8;
    window_height = (window_height * 7) / 8;
#endif
    Gui *gui = new Gui();
    gui->imgui = imgui_renderer_init("Dear ImGui SDL2+OpenGL3 example", window_width, window_height);
    gui->show_demo_window = true;
    gui->show_about_window = false;

    return gui;
}

void render_gui(App *app)
{
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    if (app->gui->show_demo_window)
        ImGui::ShowDemoWindow(&app->gui->show_demo_window);

    gui_modulator_main_window(app);
}

int gui_run(void *userArg)
{
    (void)userArg;
    App *app = (App*)userArg;

    if(app->keepRunning)
    {
        // Input
        if (imgui_renderer_handle_events(app->gui->imgui)) app->keepRunning = 0;

        // GUI
        render_gui(app);

        // Render
        imgui_renderer_render(app->gui->imgui);
        #ifdef __EMSCRIPTEN__
			emscripten_sleep(0);
		#endif
    }
    else
    {
        imgui_renderer_free(app->gui->imgui);
        return 0;
    }
    
    return 1;
}