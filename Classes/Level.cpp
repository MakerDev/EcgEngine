#include "Level.h"
#include "globals.h"

void Level::loadMap(const char* mapname) {

	_map = TMXTiledMap::create(mapname);
	_map->retain();

}

TMXTiledMap* Level::getMap() {
	return _map;
}

Point Level::positionForTileCoordinate(Size s, Point point)
{
	float x = floor(s.width / 2 * SCALE_FACTOR + point.x * _map->getTileSize().width * SCALE_FACTOR);
	float y = floor(s.height / 2 * SCALE_FACTOR + point.y * _map->getTileSize().height * SCALE_FACTOR);

	return Point(x, y);
}

Level::Level(void)
{

}

Level::~Level(void)
{
	_map->release();
}