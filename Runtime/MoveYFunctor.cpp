#include "MoveYFunctor.h"
#include "RuntimeActionTemplates.h"
#include "EngineManager.h"

void MoveYFunctor::RegisterToRuntimeAction(RuntimeAction* runtimeAction, GameObject* target, const rapidjson::Value& actionObjectValue)
{
	//TODO : Create this
}

void MoveYFunctor::Execute(float delta)
{
	auto player = _target->GetSprite();
	Rect player_rect = player->getBoundingBox();
	auto player_size = Size(player_rect.size.width, player_rect.size.height);

	Point tmp;
	vector<Rect> tiles;
	tiles.clear();

	auto level = EngineManager::GetInstance()->GetDefaultLayer()->GetLevel();

	tmp = level->positionToTileCoordinate(Point(player->getPositionX() + player_size.width * 0.5f,
		player->getPositionY() + player_size.height * 0.5f + _delta));

	if (_delta > 0) {
		tiles = level->getCollisionTilesY(tmp, 1);
	}
	else if (_delta < 0) {
		tiles = level->getCollisionTilesY(tmp, -1);
	}

	player_rect.setRect(
		player->getBoundingBox().getMinX(),
		player->getBoundingBox().getMinY() + _delta,
		player_size.width,
		player_size.height
	);

	for (Rect tile : tiles) {
		if (tile.intersectsRect(player_rect)) {
			if (_delta > 0) {
				player->setPositionY(player->getPositionY() - _delta);
			}
			else {
				player->setPositionY(tile.getMaxY());
			}

			return;
		}
	}

	this->_moveFunction();
}

MoveYFunctor::MoveYFunctor(GameObject* target, float delta)
	: _target(target), _delta(delta)
{
	_moveFunction = std::bind(RuntimeActionTemplates::MoveY, target, delta);
}
