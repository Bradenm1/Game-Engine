#include "TileMap.h"
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "Math/Hashing.h"

void TileMap::InitTileMap()
{
	for (int x = 0; x < TileMapSizeX; x++)
	{
		for (int y = 0; y < TileMapSizeX; y++)
		{
			auto item = Layers.begin();
			std::advance(item, rand() % Layers.size());
			unsigned layer = item->first;
			CreateTile(layer, x, y, 2, 3);
		}
	}
}

void TileMap::CreateTile(const char* layer, int x, int y, int sX, int sY)
{
	CreateTile(Hashing::Hash(layer), x, y, sX, sY);
}

void TileMap::CreateTile(unsigned layer, int x, int y, int sX, int sY)
{
	// Stop memory leaks from trying to render negative numbers
	if (IsTileOutOfBounds(x, y)) return;
	if (CheckTileExists(x, y)) {
		cout << "ERROR: TRYING TO CREATE A TILE ON AN EXISTING TILE: " << x << ", " << y << endl;
		return;
	}

	Entity* entity = &Game::EntityManager->AddEntity();
	entity->AddComponent<PositionComponent>(x * SPRITESIZE, y * SPRITESIZE);
	entity->AddComponent<SpriteComponent>(Layers[layer]->Spritesheet, sX, sY);
	if (Layers[layer]->Cancolide) {
		entity->AddComponent<BoxColliderComponent>();
		entity->AddGroup("Wall");
	}
	else {
		entity->AddGroup("Floor");
	}
	AssignTile(entity, x, y);
}

bool TileMap::IsTileOutOfBounds(int x, int y) 
{
	if (x < 0 || y < 0) {
		cout << "ERROR: TILE IS OUT OF BOUNDS: " << x << ", " << y << endl;
		return true;
	}
	return false;
}

bool TileMap::CheckTileExists(int x, int y) 
{
	return Map[x][y] != nullptr;
}

void TileMap::AssignTile(Entity* tile, int x, int y)
{
	Map[x][y] = tile;
}

void TileMap::AddLayer(unsigned hash, bool colide)
{
	Layers[hash] = new Layer(AssetManager::GetSpriteSheet(hash), colide);
}

void TileMap::AddLayer(const char* name, bool colide)
{
	unsigned hash = Hashing::Hash(name);
	Layers[hash] = new Layer(AssetManager::GetSpriteSheet(hash), colide);
}

Layer* TileMap::GetLayer(const char* name)
{
	unsigned hash = Hashing::Hash(name);
	return Layers[hash];
}

Layer* TileMap::GetLayer(unsigned hash)
{
	return Layers[hash];
}

void TileMap::SetTileSourceRender(int xT, int yT, int x, int y)
{
	if (!Map[xT][yT]->HasComponent<SpriteComponent>()) return;
	SpriteComponent* sprite = &Map[xT][yT]->GetComponent<SpriteComponent>();
	sprite->SetSpiteSourceRender(x, y);
}

void TileMap::SetTileSourceRenderSize(int xT, int yT, int w, int h)
{
	if (!Map[xT][yT]->HasComponent<SpriteComponent>()) return;
	SpriteComponent* sprite = &Map[xT][yT]->GetComponent<SpriteComponent>();
	sprite->SetSpiteSourceRenderSize(w, h);
}

void TileMap::Lua_CreateTileChar(const char* layer, int x, int y, int sX, int sY)
{
	CreateTile(layer, x, y, sX, sY);
}

void TileMap::Lua_CreateTileUnsigned(unsigned layer, int x, int y, int sX, int sY)
{
	CreateTile(layer, x, y, sX, sY);
}

void TileMap::Lua_AddLayerChar(const char* name, bool colide)
{
	AddLayer(name, colide);
}

void TileMap::Lua_AddLayerUnsigned(unsigned hash, bool colide)
{
	AddLayer(hash, colide);
}
