#include "Headers\Entity.h"

ResourceHolder Resourses::res;

Eagle::Eagle() : spritesCount(2)
{
	spr = new sf::Sprite[spritesCount];
	for (size_t i = 0; i < spritesCount; i++)
		spr[i].setTexture(resourses.getTexturePtr(Textures::Eagle)[i]);
	for (size_t i = 0; i < spritesCount; i++){
		spr[i].setPosition(224.f, 418.f);
	}
	for (size_t i = 0; i < spritesCount; i++)
		spr[i].setScale((float)1.7, (float)1.7);
	for (size_t i = 0; i < spritesCount; i++)
		spr[i].setOrigin(spr[i].getLocalBounds().height / 2.f, spr[i].getLocalBounds().width / 2.f);
	HP = 0;
}

Eagle::~Eagle()
{
	delete [] spr;
	//std::cout << "BonusStar deleted" << std::endl;
}

void Eagle::draw(sf::RenderWindow & window)
{
	if (isAlife()){
		window.draw(spr[0]);
	}
	else {
		window.draw(spr[1]);
	}
		
	
}

sf::FloatRect Eagle::getGlobalBounds()
{
	return spr[0].getGlobalBounds();
}

sf::FloatRect	Eagle::getLocalBounds()
{
	return spr[0].getLocalBounds();
}
