#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "Timer.h"
#include "SDL/include/SDL.h"

ModuleInput::ModuleInput():arrows(false)
{  
}

// Destructor
ModuleInput::~ModuleInput()
{}

// Called before render is available
bool ModuleInput::Init()
{
    LOG_ENGINE("Init SDL input event system");
	bool ret = true;
    /*Timer::Start();*/
	SDL_Init(0);

	if(SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
        LOG_ENGINE("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

// Called every draw update
update_status ModuleInput::Update()
{
    SDL_Event sdlEvent;
    /*Timer::Read();*/
    keyboard = SDL_GetKeyboardState(NULL);
    while (SDL_PollEvent(&sdlEvent) != 0)
    {        
        if (sdlEvent.type== SDL_QUIT) {
            return UPDATE_STOP;
        }
        if (sdlEvent.type == SDL_WINDOWEVENT) {
            if (sdlEvent.window.event == SDL_WINDOWEVENT_RESIZED || sdlEvent.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
                App->renderer->WindowResized(sdlEvent.window.data1, sdlEvent.window.data2);
            if (sdlEvent.window.event == SDL_WINDOWEVENT_FOCUS_GAINED) {
                LOG_ENGINE("Window %d gained keyboard focus",
                    sdlEvent.window.windowID)
            }            
        }        
        
        if (sdlEvent.type== SDL_MOUSEMOTION)
        {
            if(arrows)
            {
                
                App->renderer->mouseX = sdlEvent.button.x - mouseX;
                App->renderer->mouseY = sdlEvent.button.y - mouseY;
                //LOG_ENGINE("X %i, Y %i", sdlEvent.button.x-mouseX, sdlEvent.button.y-mouseY)
            }
        }
                if (sdlEvent.type == SDL_MOUSEBUTTONDOWN )
                {         
                    if(sdlEvent.button.button == SDL_BUTTON_RIGHT)
                    {                        
                        arrows = true;
                        mouseX = sdlEvent.button.x;
                        mouseY = sdlEvent.button.y;
                        //LOG_ENGINE("X %i, Y %i", mouseX, mouseY)
                    }                    
                    
                }
                if(sdlEvent.type == SDL_MOUSEBUTTONUP)
                {
                    
                    if(sdlEvent.button.button == SDL_BUTTON_RIGHT)
                    {
                        App->renderer->mouseX = 0.0f;
                        App->renderer->mouseY = 0.0f;
                        arrows = false;
                    }                    
                }
                
        
        if (sdlEvent.type == SDL_KEYDOWN) {
            if (keyboard[SDL_SCANCODE_0])
            {
                /*Timer::Stop();*/
                //LOG_ENGINE("HEEY...");
            }
        }  
        
    }
    if (arrows)
    {
        if (keyboard[SDL_SCANCODE_UP])
        {
            App->renderer->stepForwardCamara += 0.1f;
        }
        if (keyboard[SDL_SCANCODE_DOWN])
        {
            App->renderer->stepForwardCamara-= 0.1f;
        }
        if (keyboard[SDL_SCANCODE_LEFT])
        {
            App->renderer->stepLeftCamara += 0.1f;
        }
        if (keyboard[SDL_SCANCODE_RIGHT])
        {
            App->renderer->stepLeftCamara -= 0.1f;
        }
    }    
    
    return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
    LOG_ENGINE("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}
