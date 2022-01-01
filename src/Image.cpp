#include "Image.h"
#include "File.h"
#include <SFML/Graphics.hpp>

Image::Image(void)
{
	create(NULL);
}

Image::Image(File* file)
{
	create(file);
}

Image::Image(String fileName)
{
	create(new File(fileName));
}

void Image::create(File* file)
{
	if ((_file = file) == NULL || !file->exists())
		return;
	_texture = new sf::Texture;
	_texture->loadFromFile(file->path().cpp());
	_sprite = new sf::Sprite(*_texture);
}

void Image::pos(float x, float y)
{
	_sprite->setPosition(x, y);
}

void Image::rect(int x, int y, int w, int h)
{
	_sprite->setTextureRect(sf::IntRect(x, y, w, h));
}
