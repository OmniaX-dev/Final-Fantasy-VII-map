#include <iostream>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include "Image.h"
#include "File.h"
#include "StringTokens.h"

struct Location
{
public:
	int zone;
	String name;
	char type;
	sf::Vector2i coords;
	
	sf::IntRect rect(int c_rad, int ox, int oy)
	{
		return sf::IntRect(coords.x - ox - (c_rad / 2), coords.y - oy - (c_rad / 2), c_rad, c_rad);
	}
};

Image img;
Image marker;
sf::RenderWindow window;
Location* locs = NULL;
int count = 0;
int c_rad = 4;
int m_loc = -1;
bool debug = false;
String filter = "";
bool bs = false;
int bs_time = 1;
int bs_tick = 0;
int offset_x = 0;
int offset_y = 0;
int zone = 0;

float scale = 1.08;

//This is used because I scaled the image but I didn't update the Locations file
const float img_scale = 0.8;

sf::Font font;

void render(void);
void update(void);
void keyPressed(sf::Event* evt);
void keyReleased(sf::Event* evt);

int main(int argc, char** argv)
{
	img.create(new File("res/map.png"));
	marker.create(new File("res/marker.png"));
	int scaled_x = (int)(img.sprite()->getTextureRect().width * scale);
	int scaled_y = (int)(img.sprite()->getTextureRect().height * scale);

	window.create(sf::VideoMode(scaled_x, scaled_y), "Final Fantasy VII Interactive map", sf::Style::Close);
	window.setKeyRepeatEnabled(false);
	window.setFramerateLimit(60);
	
	img.sprite()->scale(scale, scale);
	
	font.loadFromFile("res/arialbi.ttf");
	
	File loc("res/loc.dat");
	StringTokens* tokens = loc.content().tokenize(";", true);
	StringTokens* tokens2 = NULL;
	locs = new Location[tokens->count() - 1];
	int i = 0;
	while (tokens->hasNext())
	{
		String line = tokens->next();
		if (line.trim().equals(""))
			continue;
		if (line == "###") break;
		tokens2 = line.tokenize(":");
		locs[i].zone = tokens2->next().at(1) - '0';
		locs[i].name = tokens2->next();
		String data = tokens2->next();
		delete tokens2;
		tokens2 = data.tokenize(",");
		locs[i].type = tokens2->next().at(0);
		locs[i].coords.x = (int)(tokens2->next().toInt() * scale * img_scale);
		locs[i].coords.y = (int)(tokens2->next().toInt() * scale * img_scale);
		i++;
	}
	count = i;
	
    sf::Event evt;
	while (window.isOpen())
	{
		while (window.pollEvent(evt))
		{
			switch (evt.type)
			{
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::KeyPressed:
                    keyPressed(&evt);
					break;
				case sf::Event::KeyReleased:
                    keyReleased(&evt);
					break;
				case sf::Event::TextEntered:
					if ((evt.text.unicode >= 'A' && evt.text.unicode <= 'Z') || (evt.text.unicode >= 'a' && evt.text.unicode <= 'z') || evt.text.unicode == ' ')
						filter = filter.add((char)(evt.text.unicode)).toLowerCase();
					else if (evt.text.unicode >= '0' && evt.text.unicode <= '5')
						zone = evt.text.unicode - '0';
					break;
				case sf::Event::MouseMoved:
					for (int i = 0; i < count; i++)
					{
						if (locs[i].rect(c_rad * 8, offset_x + (offset_x / 2), offset_y).contains(evt.mouseMove.x, evt.mouseMove.y))
						{
							m_loc = i;
							break;
						}
						m_loc = -1;
					}
					break;
				default:
					break;
			}
		}
		update();
		window.clear(sf::Color::White);
		render();
		window.display();
	}
	return 0;
}

void render(void)
{
	sf::Sprite* spr = img.sprite();
	sf::Sprite& mspr = *marker.sprite();
	window.draw(*spr);
	sf::CircleShape circle;
	circle.setRadius(c_rad);
	circle.setOutlineColor(sf::Color(211, 211, 211));
	circle.setFillColor(sf::Color::Black);
	circle.setOutlineThickness(1);
	Location loc;
	sf::Text text;
	text.setCharacterSize(18);
	text.setFont(font);
	for (int i = 0; i < count; i++)
	{
		loc = locs[i];
		if ((!filter.equals("") && !loc.name.toLowerCase().contains(filter)) || (zone > 0 && zone != loc.zone))
			continue;

		mspr.setPosition(loc.coords.x - 9, loc.coords.y - 10);
		
		//circle.setFillColor(sf::Color(30, 30, 30, 210));
		//circle.setOutlineColor(sf::Color(30, 30, 30, 210));
		//circle.setPosition(loc.coords.x - offset_x - (c_rad / 2) + 2, loc.coords.y - offset_y - (c_rad / 2) + 2);
		//window.draw(circle);
		//circle.setOutlineColor(sf::Color(180, 180, 180, 120));
		//circle.setPosition(loc.coords.x - offset_x - (c_rad / 2), loc.coords.y - offset_y - (c_rad / 2));
		if (i == m_loc)
			mspr.setColor(sf::Color(0, 127, 255, 200));
		else if (loc.type == 'N')
			mspr.setColor(sf::Color(232, 99, 0, 180));
		else if (loc.type == 'S')
			mspr.setColor(sf::Color(255, 255, 0, 180));
		else if (loc.type == 'C')
			mspr.setColor(sf::Color(255, 0, 0, 150));
		//window.draw(circle);
		window.draw(mspr);
		if (debug)
		{
			sf::RectangleShape rect;
			sf::IntRect r = loc.rect(c_rad * 8, offset_x + (offset_x / 2), offset_y);
			rect.setPosition(r.left, r.top);
			rect.setSize(sf::Vector2f(r.width, r.height));
			rect.setFillColor(sf::Color::Transparent);
			rect.setOutlineColor(sf::Color::Red);
			rect.setOutlineThickness(1);
			window.draw(rect);
		}
	}
	
	if ((m_loc != -1 && filter.equals("")) || (m_loc != -1 && !filter.equals("") && locs[m_loc].name.toLowerCase().contains(filter)))
	{
		loc = locs[m_loc];
		text.setString(loc.name.cpp());

		text.setPosition(loc.coords.x - offset_x - (c_rad / 2) + c_rad + 12, loc.coords.y - offset_y - (c_rad / 2) - c_rad - 2);
		text.setColor(sf::Color::Black);
		window.draw(text);
		text.setPosition(loc.coords.x - offset_x - (c_rad / 2) + c_rad + 10, loc.coords.y - offset_y - (c_rad / 2) - c_rad - 4);
		text.setColor(sf::Color::White);
		window.draw(text);
	}
	
	text.setString(filter.cpp());
	text.setPosition(0, 0);
	window.draw(text);
}

void update(void)
{
	if (bs && bs_tick++ >= bs_time)
	{
		filter = filter.substr(0, filter.length() - 1);
		bs_tick = 0;
	}
}

void keyPressed(sf::Event* evt)
{
	if (evt->key.code == sf::Keyboard::BackSpace)
	{
		bs = true;
		filter = filter.substr(0, filter.length() - 1);
		bs_tick = 0;
	}
}

void keyReleased(sf::Event* evt)
{
	if (evt->key.code == sf::Keyboard::BackSpace)
		bs = false;
}
