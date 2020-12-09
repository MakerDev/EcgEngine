#pragma once
#include <vector>
#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

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