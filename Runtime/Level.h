#pragma once

#include "cocos2d.h"
#include <vector>

using namespace cocos2d;
using namespace std;

class Level : public Node
{
public:

	TMXTiledMap* _map;

	void loadMap(const char* name);
	TMXTiledMap* getMap();

	Point tileCoordinateToPosition(Point point);
	//Point positionForTileCoordinate(Size s, Point point);
	Point positionToTileCoordinate(Point point);
	vector<Rect> getCollisionTilesX(Point point, int direction);
	vector<Rect> getCollisionTilesY(Point point, int direction);

	Level(void);
	virtual ~Level(void);
};