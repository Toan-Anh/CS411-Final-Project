#include "Sprite.h"

Sprite::Sprite(string const &name)
{
	_name = name;
	_size = { TextureManager::getWidth(name), TextureManager::getHeight(name) };
	_rect.push_back({ 0, 0 }); // left, top
	_rect.push_back({ _size.x, 0 }); // right, to
	_rect.push_back({ _size.x, _size.y }); // right, bottom
	_rect.push_back({ 0, _size.y }); // left, bottom
}

Sprite::~Sprite()
{
}

void Sprite::ApplyMatrix(Matrix const & matrix)
{
	matrix.TransformPoints(_rect);
}

void Sprite::Update()
{
}

void Sprite::Draw()
{
	TextureManager::BindTexture(_name);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0f, 0.0f); glVertex2d(_rect[0].x, _rect[0].y); // top left
	glTexCoord2d(1.0f, 0.0f); glVertex2d(_rect[1].x, _rect[1].y); // top right
	glTexCoord2d(1.0f, 1.0f); glVertex2d(_rect[2].x, _rect[2].y); // bottom right
	glTexCoord2d(0.0f, 1.0f); glVertex2d(_rect[3].x, _rect[3].y); // bottom left
	glEnd();
}

void Sprite::set_position(Vector2 top_left)
{
	_rect.clear();
	_rect.push_back({ top_left.x, top_left.y }); // left, top
	_rect.push_back({ top_left.x + _size.x, top_left.y }); // right, to
	_rect.push_back({ top_left.x + _size.x, top_left.y + _size.y }); // right, bottom
	_rect.push_back({ top_left.x, top_left.y + _size.y }); // left, bottom
}

Vector2 Sprite::get_position()
{
	return _rect[0];
}