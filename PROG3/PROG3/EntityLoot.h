#ifndef ENTITYLOOT_H
#define ENTITYLOOT_H

#include "Entity.h"
#include "InventoryItem.h"

namespace stain{
	class EntityLoot : public Entity {
	public:
		~EntityLoot();
		static EntityLoot* getInstance(int x, int y, int size, Sprite* sprite, int timeToLive = 20000, InventoryItem* lootItem = nullptr);

		void tick(std::vector<Entity*> interactors);
		void addLootItem(InventoryItem* item);
		std::vector<InventoryItem*> getLootItems();
	private:
		EntityLoot(int x, int y, int size, Sprite* sprite, int timeToLive, InventoryItem* lootItem);
		unsigned int timeToLive;
		unsigned int startTime;
		std::vector<InventoryItem*> loot;
	};
}
#endif