#pragma once
#include <vector>
#include <string>
#define MAX_BONE_INFLUENCE 4
struct aiMesh;

struct vector3 {
	float x;
	float y;
	float z;
};
struct vector2 {
	float x;
	float y;	
};

struct Vertex {
	vector3 position;
	vector3 normal;
	vector2 texCoords;
	vector3 tangent;
	vector3 bitangent;
	//bone indexes which will influence this vertex
	int m_BoneIDs[MAX_BONE_INFLUENCE];
	//weights from each bone
	float m_Weights[MAX_BONE_INFLUENCE];
};

struct Texture {
	unsigned int id;
	std::string type;
	std::string path;
};

class Mesh {
public:
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
	std::vector<unsigned int> indices;
	std::vector<Vertex> vertices;
	std::vector<Texture> textures;
	

	void LoadVBO();
	void Draw( unsigned int &shader_id);
private:
	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;
};