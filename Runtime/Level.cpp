#include "Level.h"
#include "globals.h"

void Level::loadMap(const char* mapname) {
	map = TMXTiledMap::create(mapname);
	map->retain();
}

TMXTiledMap* Level::getMap() {
	return map;
}

Point Level::tileCoordinateToPosition(Size s, Point point) {
	float x = floor(s.width / 2 * SCALE_FACTOR + point.x * map->getTileSize().width * SCALE_FACTOR);
	float y = floor(s.height / 2 * SCALE_FACTOR + point.y * map->getTileSize().height * SCALE_FACTOR);

	return Point(x, y);
}

vector<Rect> Level::getCollisionTiles(Point point, int fromX, int fromY)
{
	vector<Rect> list;

	TMXLayer* walls = map->getLayer("walls");
	int mapheight = (int)map->getMapSize().height - 1;

	for (int a = fromX; a < 2; a++) {

		for (int b = fromY; b < 2; b++) {

			if (!(a == 0 && b == 0) && a >= 0 && b >= 0) {

				Sprite* tile = walls->getTileAt(Point((int)point.x + a, mapheight - ((int)point.y + b)));

				if (tile != NULL) {
					DrawNode* rectWithBorder = DrawNode::create();

					Vec2 vertices[] =
					{
						Vec2(0, map->getTileSize().height * SCALE_FACTOR),
						Vec2(map->getTileSize().width * SCALE_FACTOR, map->getTileSize().height * SCALE_FACTOR),
						Vec2(map->getTileSize().width * SCALE_FACTOR, 0),
						Vec2(0,0)
					};

					Point tmp = walls->positionAt(Point((int)point.x + a, mapheight - ((int)point.y + b)));
					rectWithBorder->setPosition(tmp.x * SCALE_FACTOR, tmp.y * SCALE_FACTOR);

					Rect tileRect = rectWithBorder->getBoundingBox();

					tileRect.setRect(rectWithBorder->getBoundingBox().getMinX(),
						rectWithBorder->getBoundingBox().getMinY(),
						map->getTileSize().width * SCALE_FACTOR,
						map->getTileSize().height * SCALE_FACTOR);

					list.push_back(tileRect);
				}
			}
		}
	}

	return list;
}

Level::Level(void)
{

}

Level::~Level(void)
{
	map->release();
}