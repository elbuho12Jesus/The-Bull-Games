#pragma once
#include "Module.h"
#include <string>





class ModuleTexturas :public Module {
public:
	ModuleTexturas();
	~ModuleTexturas();
	bool Init();
	bool CleanUp();
	unsigned int texture;
	unsigned int Load(const char* path, const std::string& directory);
	void Load_texture_direcX(const char* path, unsigned int textureID);
private:
	
};
