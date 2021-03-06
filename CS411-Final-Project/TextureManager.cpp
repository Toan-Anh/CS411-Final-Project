#include "TextureManager.h"
#include <fstream>
using namespace std;

unordered_map<string, pair<string, bool>> TextureManager::TEXTURE_LIST;
unordered_map<string, Texture> TextureManager::_textures;

void read_file_callback(png_structp png_ptr, png_bytep out, png_size_t count)
{
	png_voidp io_ptr = png_get_io_ptr(png_ptr);

	if (io_ptr == 0)
	{
		return;
	}

	std::ifstream &ifs = *(std::ifstream*)io_ptr;

	ifs.read((char*)out, count);
}

GLuint TextureManager::loadTexture(const string filename, const bool &transparent, int &width, int &height)
{
	//header for testing if it is a png
	png_byte header[8];

	//open file as binary
	ifstream fp(filename.c_str(), ios::binary);
	if (!fp.is_open()) {
		return TEXTURE_LOAD_ERROR;
	}

	//read the header
	fp.read((char*)&header, sizeof(char) * 8);

	//test if png
	int is_png = !png_sig_cmp(header, 0, 8);
	if (!is_png) {
		fp.close();
		return TEXTURE_LOAD_ERROR;
	}

	//create png struct
	png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL,
		NULL, NULL);
	if (!png_ptr) {
		fp.close();
		return (TEXTURE_LOAD_ERROR);
	}

	//create png info struct
	png_infop info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr) {
		png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
		fp.close();
		return (TEXTURE_LOAD_ERROR);
	}

	//create png info struct
	png_infop end_info = png_create_info_struct(png_ptr);
	if (!end_info) {
		png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
		fp.close();
		return (TEXTURE_LOAD_ERROR);
	}

	//png error stuff, not sure libpng man suggests this.
	if (setjmp(png_jmpbuf(png_ptr))) {
		png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
		fp.close();
		return (TEXTURE_LOAD_ERROR);
	}

	//init png reading
	png_set_read_fn(png_ptr, (void*)&fp, read_file_callback);

	//let libpng know you already read the first 8 bytes
	png_set_sig_bytes(png_ptr, 8);

	// read all the info up to the image data
	png_read_info(png_ptr, info_ptr);

	//variables to pass to get info
	int bit_depth, color_type;
	png_uint_32 twidth, theight;

	// get info about png
	png_get_IHDR(png_ptr, info_ptr, &twidth, &theight, &bit_depth, &color_type,
		NULL, NULL, NULL);

	//update width and height based on png info
	width = twidth;
	height = theight;

	// Update the png info struct.
	png_read_update_info(png_ptr, info_ptr);

	// Row size in bytes.
	int rowbytes = png_get_rowbytes(png_ptr, info_ptr);

	// Allocate the image_data as a big block, to be given to opengl
	png_byte *image_data = new png_byte[rowbytes * height];
	if (!image_data) {
		//clean up memory and close stuff
		png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
		fp.close();
		return TEXTURE_LOAD_ERROR;
	}

	//row_pointers is for pointing to image_data for reading the png with libpng
	png_bytep *row_pointers = new png_bytep[height];
	if (!row_pointers) {
		//clean up memory and close stuff
		png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
		delete[] image_data;
		fp.close();
		return TEXTURE_LOAD_ERROR;
	}
	// set the individual row_pointers to point at the correct offsets of image_data
	for (int i = 0; i < height; ++i)
		row_pointers[height - 1 - i] = image_data + i * rowbytes;

	//read the png into image_data through row_pointers
	png_read_image(png_ptr, row_pointers);

	//Now generate the OpenGL texture object
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,
		transparent ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, (GLvoid*)image_data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	//clean up memory and close stuff
	png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
	delete[] image_data;
	delete[] row_pointers;
	fp.close();

	return texture;
}

void TextureManager::Initialize(string const &list_file)
{
	ifstream fin(list_file);
	if (!fin.is_open())
		return;

	string name, path;
	bool trans;
	do
	{
		getline(fin, name);
		getline(fin, path);
		fin >> trans;
		fin.ignore();
		TEXTURE_LIST[name] = { path, trans };
	} while (!fin.eof());
	fin.close();

	for (auto it = TEXTURE_LIST.cbegin(); it != TEXTURE_LIST.cend(); ++it)
	{
		int width, height; // width and height of the image, may ot actually use them
		GLuint handle = loadTexture((*it).second.first, (*it).second.second, width, height);
		_textures[(*it).first] = { handle, width, height };
	}
}

void TextureManager::BindTexture(string const & tex_name)
{
	if (_textures.count(tex_name) != 0)
		glBindTexture(GL_TEXTURE_2D, _textures[tex_name].handle);
}

Texture TextureManager::Texture(string const &tex_name)
{
	if (_textures.count(tex_name) != 0)
		return _textures[tex_name];
}

double TextureManager::getWidth(string const &tex_name)
{
	if (_textures.count(tex_name) != 0)
		return _textures[tex_name].width;
}

double TextureManager::getHeight(string const &tex_name)
{
	if (_textures.count(tex_name) != 0)
		return _textures[tex_name].height;
}