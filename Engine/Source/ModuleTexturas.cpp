#define STB_IMAGE_IMPLEMENTATION
#include "ModuleTexturas.h"
#include "DirectXTex.h"
#include "std/stb_image.h"
#include "glew.h"
#include <iostream>


void Format_direcxtex_to_opengl(DirectX::TexMetadata metadata, GLint& internalFormat, GLenum& format, GLenum& type) {
	switch (metadata.format)
	{
	case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
	case DXGI_FORMAT_R8G8B8A8_UNORM:
		internalFormat = GL_RGBA8;
		format = GL_RGBA;
		type = GL_UNSIGNED_BYTE;
		break;
	case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:
	case DXGI_FORMAT_B8G8R8A8_UNORM:
		internalFormat = GL_RGBA8;
		format = GL_BGRA;
		type = GL_UNSIGNED_BYTE;
		break;
	case DXGI_FORMAT_B5G6R5_UNORM:
		internalFormat = GL_RGB8;
		format = GL_BGR;
		type = GL_UNSIGNED_BYTE;
		break;
	default:
		assert(false && "Unsupported format");
	}
}

ModuleTexturas::ModuleTexturas() {}
ModuleTexturas::~ModuleTexturas() {}
bool ModuleTexturas::Init()
{
	HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	if (FAILED(hr))
	{LOG_ENGINE("ERROR 1") }
	DirectX::TexMetadata info;
	auto image = std::make_unique<DirectX::ScratchImage>();
	HRESULT hr1 = LoadFromWICFile(L"../Test-image-Baboon.ppm", DirectX::WIC_FLAGS_NONE, &info, *image);
	if (FAILED(hr1))
	{
		LOG_ENGINE("ERROR 2")
	}
	else {
		DirectX::ScratchImage destImage;
		DirectX::FlipRotate(image.get()->GetImages(), image.get()->GetImageCount(),info,DirectX::TEX_FR_FLIP_VERTICAL,destImage);
		GLint internalFormat; 
		GLenum format; 
		GLenum type;
		
		
			
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture); 
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		Format_direcxtex_to_opengl(info, internalFormat, format, type);
		glTexImage2D(GL_TEXTURE_2D,0, internalFormat,info.width,info.height,0, format, type,(void*)destImage.GetPixels());
		glGenerateTextureMipmap(texture);
		image.release();
		destImage.Release();
	}
	return true;
}
void ModuleTexturas::Load_texture_direcX(const char* path, unsigned int textureID)
{
	
		DirectX::TexMetadata info;
		const size_t cSize = strlen(path) + 1;
		std::wstring file_name(cSize, L'#');
		size_t res;
		mbstowcs_s(&res, &file_name[0], cSize, path, cSize);
		auto image = std::make_unique<DirectX::ScratchImage>();
		HRESULT hr1 = LoadFromWICFile(&file_name[0], DirectX::WIC_FLAGS_NONE, &info, *image);
		if (FAILED(hr1))
		{
			LOG_ENGINE("ERROR 2")
		}
		else
		{
			DirectX::ScratchImage destImage;
			GLint internalFormat;
			GLenum format;
			GLenum type;
			DirectX::FlipRotate(image.get()->GetImages(), image.get()->GetImageCount(), info, DirectX::TEX_FR_FLIP_VERTICAL, destImage);			
			Format_direcxtex_to_opengl(info, internalFormat, format, type);
			glBindTexture(GL_TEXTURE_2D, textureID);
			glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, info.width, info.height, 0, format, type, destImage.GetPixels());
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
						
			image.release();
			destImage.Release();


		}
	
	
}
bool ModuleTexturas::CleanUp()
{
	return true;
}

unsigned int ModuleTexturas::Load(const char* path, const std::string& directory) {

	std::string filename = std::string(path);
	filename = directory + '/' + filename;
	unsigned int textureID;
	glGenTextures(1, &textureID);

	/*int width, height, nrComponents;*/
	int width, height;
	int internalFormat; 
	unsigned int format; 
	unsigned int type;
	/*unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);*/
	Load_texture_direcX(filename.c_str(), textureID);	
	
	/*if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}*/

	return textureID;
}

