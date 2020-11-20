#pragma once
#include <vector>

#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

class Level : public Node
{
public:

	TMXTiledMap* map;

	void loadMap(const char* name);
	TMXTiledMap* getMap();

	Point tileCoordinateToPosition(Size s, Point point);
	vector<Rect> getCollisionTiles(Point point, int fromX, int fromY);

	Level(void);
	virtual ~Level(void);
};