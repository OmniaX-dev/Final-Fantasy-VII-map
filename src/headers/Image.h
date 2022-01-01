#ifndef __IMAGE__H__
#define __IMAGE__H__

#include "fwd_SFML.h"
#include "String.h"

class File;
class Image
{
public:
    Image(void);
    Image(File* file);
    Image(String fileName);
    void create(File* file);
    
    inline sf::Texture* texture(void) {return _texture;}
    inline sf::Sprite* sprite(void) {return _sprite;}
    
    void pos(float x, float y);
    void rect(int x, int y, int w, int h);
    
private:
    sf::Texture* _texture;
    sf::Sprite* _sprite;
    File* _file;
};

#endif