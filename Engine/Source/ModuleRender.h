#pragma once
#include "Module.h"
#include <string>


class Shader;
class Model;


class ModuleRender : public Module
{
public:
	ModuleRender();
	~ModuleRender();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	void WindowResized(unsigned width, unsigned height);		
	float targetPositionX;
	float targetPositionY;
	float targetPositionZ;
	float postX;
	float postY;
	float postZ;
	float mouseX;
	float mouseY;
	float stepForwardCamara;
	float stepLeftCamara;
	float angleViewX;
	float angleViewY;
	int window_width;
	int window_height;
	bool show_demo_window;
	bool show_another_window;
	bool show_files;
	bool show_importer_window;	
private:		
	Model* ourModel;
	void* context;
	Shader* shader=NULL;			
		
	unsigned int shaderProgram{};
};
