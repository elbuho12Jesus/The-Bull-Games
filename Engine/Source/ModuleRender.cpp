#include "ModuleRender.h"
#include "Globals.h"
#include "Shader.h"
#include "Application.h"
#include "ModuleWindow.h"
//#include "ModuleDebugDraw.h"
#include "ModuleTexturas.h"
#include "Model.h"
#include <map>
//#include "Imgui_ModuleResource.h"
//#include "ImportWindow.h"
#include "SDL.h"
#include "glew.h"
#define GLM_FORCE_MESSAGES 
#include <glm.hpp>
#include <vec3.hpp> // glm::vec3
#include <vec4.hpp> // glm::vec4
#include <mat4x4.hpp> // glm::mat4
#include <gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <gtc/type_ptr.hpp>
//#include <ft2build.h>
//#include FT_FREETYPE_H 

#define SHADER_DIR "D:\\Game_UPC\\project0\\Engine\\Source"




float adsolute(float x)
{
	return (x > 0) ? x : -x;
}

ModuleRender::ModuleRender()
{
	postX = 0.0f;
	postY = 0.5f;
	postZ = 10.0f;
	mouseX = 0.0f;
	mouseY = 0.0f;
	targetPositionX = 0.0f;
	targetPositionY = 0.0f;	
	targetPositionZ = 0.0f;
	angleViewX = 0.0f;
	angleViewY = 0.0f;
	stepForwardCamara = 0.0f;
	stepLeftCamara = 0.0f;
	window_width = (int)SCREEN_WIDTH;
	window_height = (int)SCREEN_HEIGHT;
}

// Destructor
ModuleRender::~ModuleRender()
{
	//delete ourModel;
}

// Called before render is available
bool ModuleRender::Init()
{
	const char* glsl_version = "#version 130";
	LOG_ENGINE("Creating Renderer context");
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4); // desired version
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // we want a double buffer
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24); // we want to have a depth buffer with 24 bits
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8); // we want to have a stencil buffer with 8 bits
	
	context = SDL_GL_CreateContext(App->window->window);
	glewInit();
	LOG_ENGINE("Using Glew %s", glewGetString(GLEW_VERSION));
	// Should be 2.0	
	LOG_ENGINE("Vendor: %s", glGetString(GL_VENDOR));
	LOG_ENGINE("Renderer: %s", glGetString(GL_RENDERER));
	LOG_ENGINE("OpenGL version supported %s", glGetString(GL_VERSION));
	LOG_ENGINE("GLSL: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));		
	

	std::string shader_vs = std::string(SHADER_DIR) + "\\Shaders\\VertexShader.vs";
	std::string shader_fs = std::string(SHADER_DIR) + "\\Shaders\\FragmentShader.fs";	

	shader = new Shader((shader_vs).c_str(), (shader_fs).c_str());
	
	//ourModel=new Model("../Game/Assets/baker_house_model/BakerHouse1.fbx");	
	ourModel = new Model("../Game/Assets/bull_fighter/bull_fighter.fbx");
	return true;
}

update_status ModuleRender::PreUpdate()
{
	glViewport(0, 0, (int)SCREEN_WIDTH, (int)SCREEN_HEIGHT);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	/*glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D, App->textures->texture);*/
	return UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleRender::Update(){
	// render the loaded model
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	

	glm::mat4 view;
	view = glm::lookAt(glm::vec3(0.0f, 0.0f, 700.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));

	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.0f), (float)(window_width) / (float)(window_height), 0.1f, 1000.0f);
	
	angleViewX= (mouseX / (float)(10*window_width ));
	angleViewY = (mouseY / (float)(10*window_height));	
	shader->use();
	glUniformMatrix4fv(glGetUniformLocation(shader->ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(glGetUniformLocation(shader->ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(shader->ID, "proj"), 1, GL_FALSE, glm::value_ptr(projection));
	//glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
	ourModel->Draw(shader->ID);	
	//App->debug_draw->Draw(view,projection, (unsigned)SCREEN_WIDTH, (unsigned)SCREEN_HEIGHT);
	
	angleViewX = 0.0f;		
	angleViewY = 0.0f;
	
		
	return UPDATE_CONTINUE;
}

update_status ModuleRender::PostUpdate()
{
	// Update and Render additional Platform Windows
		// (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
		//  For this specific demo app we could also call SDL_GL_MakeCurrent(window, gl_context) directly)
	
	SDL_GL_SwapWindow(App->window->window);
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRender::CleanUp()
{
	LOG_ENGINE("Destroying renderer");

	//Destroy window
	/*
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	*/
	/*
	glDeleteVertexArrays(1, &VAO2);
	glDeleteBuffers(1, &VBO2);
	*/
	delete shader;
	//delete shaderText;
	//glDeleteProgram(shaderProgram);	
	SDL_GL_DeleteContext(context);
	return true;
}

void ModuleRender::WindowResized(unsigned width, unsigned height)
{
}

