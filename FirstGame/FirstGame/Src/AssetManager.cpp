#include "AssetManager.h"
#include "Math/Hashing.h"

map<unsigned, SpriteSheet*> AssetManager::AllSpriteSheets = map<unsigned, SpriteSheet*>();

void AssetManager::AddSpriteSheet(const char* index, const char* assetLoction)
{
	AddSpriteSheet(index, new SpriteSheet(assetLoction));
}

void AssetManager::AddSpriteSheet(const char* index, SpriteSheet* spriteSheet)
{
	AddSpriteSheet(Hashing::Hash(index), spriteSheet);
}

void AssetManager::AddSpriteSheet(unsigned hash, SpriteSheet* spriteSheet)
{
	assert(spriteSheet != nullptr);
	AllSpriteSheets[hash] = spriteSheet;
}

SpriteSheet* AssetManager::GetSpriteSheet(const char* index)
{
	return GetSpriteSheet(Hashing::Hash(index));
}

SpriteSheet* AssetManager::GetSpriteSheet(unsigned hash)
{
	if (AllSpriteSheets.find(hash) == AllSpriteSheets.end()) {
		return nullptr;
	}
	return AllSpriteSheets[hash];
}

void AssetManager::Lua_AddSpriteSheet(const char* index, const char* assetLoction)
{
	AddSpriteSheet(index, assetLoction);
}

SpriteSheet* AssetManager::Lua_GetSpriteSheet(const char* index)
{
	return GetSpriteSheet(index);
}