#pragma once
/*
 * Adapted from OpenGL Programming Wikibook
 */
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <png.h>
#include <string>
#include <unordered_map>
using namespace std;

#define TEXTURE_LOAD_ERROR 0

struct Texture {
	GLuint handle;
	int width;
	int height;
};

class TextureManager
{
private:
	// Name => { path, isTransparent }
	static unordered_map<string, pair<string, bool>> TEXTURE_LIST;
	static unordered_map<string, Texture> _textures;
	static GLuint loadTexture(const string filename, bool const &transparent, int &width, int &height);
public:
	static void Initialize(string const &list_file);
	static Texture Texture(string const &tex_name);
	static void BindTexture(string const &tex_name);
	static double getWidth(string const &tex_name);
	static double getHeight(string const &tex_name);
};