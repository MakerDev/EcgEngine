#include "Level.h"
#include "globals.h"

void Level::loadMap(const char* mapname) {

	_map = TMXTiledMap::create(mapname);
	_map->retain();
}

TMXTiledMap* Level::getMap() {
	return _map;
}

Point Level::tileCoordinateToPosition(Point point) {

	float x = floor(point.x * _map->getTileSize().width * SCALE_FACTOR);
	float y = floor(point.y * _map->getTileSize().height * SCALE_FACTOR);

	return Point(x, y);

}

Point Level::tileCoordinateToPosition(Size s, Point point) {
	float x = floor(s.width / 2 * SCALE_FACTOR + point.x * _map->getTileSize().width * SCALE_FACTOR);
	float y = floor(s.height / 2 * SCALE_FACTOR + point.y * _map->getTileSize().height * SCALE_FACTOR);

	return Point(x, y);
}

Point Level::positionToTileCoordinate(Point point) {

	float x = floor(point.x / (_map->getTileSize().width * SCALE_FACTOR));
	float y = floor(point.y / (_map->getTileSize().height * SCALE_FACTOR));

	return Point((int)x, (int)y);
}

vector<Rect> Level::getCollisionTilesX(Point point, int direction) {

	vector<Rect> list;

	TMXLayer* walls = _map->getLayer("walls");

	const int mapheight = (int)_map->getMapSize().height - 1;

	for (int b = -1; b < 2; b++) {

		const Sprite* tile = walls->getTileAt(Point((int)point.x + direction, mapheight - ((int)point.y + b)));

		if (tile != NULL) {

			Rect tileRect = Rect();

			const Point tmp = walls->positionAt(Point((int)point.x + direction, mapheight - ((int)point.y + b)));
			tileRect.setRect(tmp.x * SCALE_FACTOR, tmp.y * SCALE_FACTOR, _map->getTileSize().width * SCALE_FACTOR, _map->getTileSize().height * SCALE_FACTOR);

			list.push_back(tileRect);
		}

	}

	return list;
}

vector<Rect> Level::getCollisionTilesY(Point point, int direction) {
	vector<Rect> list;

	TMXLayer* walls = _map->getLayer("walls");

	int mapheight = (int)_map->getMapSize().height - 1;

	for (int b = -1; b < 2; b++) {

		Sprite* tile = walls->getTileAt(Point((int)point.x + b, mapheight - ((int)point.y + direction)));

		if (tile != NULL) {
			Rect tileRect = Rect();
			
			Point tmp = walls->positionAt(Point((int)point.x + b, mapheight - ((int)point.y + direction)));
			tileRect.setRect(tmp.x * SCALE_FACTOR, tmp.y * SCALE_FACTOR, 
				_map->getTileSize().width * SCALE_FACTOR, _map->getTileSize().height * SCALE_FACTOR);

			list.push_back(tileRect);
		}
	}

	return list;
}

Level::Level(void)
{

}

Level::~Level(void)
{
	_map->release();
}