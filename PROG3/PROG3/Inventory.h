#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include "InventoryItem.h"

namespace stain{
	class Inventory{
	public:
		static Inventory* getInstance();
		~Inventory();

		void addItem(InventoryItem* item);
		void removeItem(InventoryItem* item, bool deleteEntireStack = false);
		std::vector<InventoryItem*> getItems() const;
		int setSelectedItem(int index);
		InventoryItem* getSelectedItem() const;
	private:
		Inventory();

		std::vector<InventoryItem*> items;
		InventoryItem* selectedItem;
	};
}
#endif