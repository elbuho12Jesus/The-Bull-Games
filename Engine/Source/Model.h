#pragma once
#include "Mesh.h"
//#include <string>
//#include <vector>

struct aiScene;

struct aiMaterial;
struct aiNode;
struct aiMesh;
//struct Texture;
//class Mesh;

class Model {

public:	
	// model data 
	std::vector<Texture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
	std::vector<Mesh> meshes;
	std::string directory;	
	Model(const char* file_name);	
	void Load(const char* file_name);
	void processNode(aiNode* node,const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, int type, std::string typeName);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	void Draw(unsigned int &shader_id);
	/*unsigned int Load(const char* path, const std::string& directory);*/
};