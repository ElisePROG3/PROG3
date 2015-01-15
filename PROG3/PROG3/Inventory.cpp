#include "Inventory.h"

namespace stain{
	Inventory::Inventory():
		selectedItem(nullptr)
	{

	}

	Inventory::~Inventory(){

	}

	Inventory* Inventory::getInstance(){
		return new Inventory();
	}

	void Inventory::addItem(InventoryItem* item){
		std::vector<InventoryItem*>::iterator itr;
		for (itr = items.begin(); itr != items.end();){
			if (*itr == item){
				/* If item exists increment the amount */
				item->invAmount(item->invAmount() + 1);
				return;
			}
			else
				++itr;
		}
		
		/* Item doesn't exists in the list, let's add it */
		if (item != nullptr){
			items.push_back(item);
			selectedItem = item;
		}
	}

	void Inventory::removeItem(InventoryItem* item, bool deleteEntireStack){
		/*
		*	Remove an item from the inventory list by iterating the list,
		*	if the item has an amount bigger than zero then decrease that with one instead of removing.
		*/
		std::vector<InventoryItem*>::iterator itr;
		for (itr = items.begin(); itr != items.end();){
			if (*itr == item){
				if (deleteEntireStack || item->invAmount() == 0){
					itr = items.erase(itr);
					delete(item);
				}else{
					item->invAmount(item->invAmount() - 1);
				}
				break;
			}
			else
				++itr;
		}
	}

	std::vector<InventoryItem*> Inventory::getItems() const {
		return items;
	}

	int Inventory::setSelectedItem(int index){
		int vectorIndex = index % items.size();

		selectedItem = items[vectorIndex];

		return vectorIndex;
	}

	InventoryItem* Inventory::getSelectedItem() const {
		return selectedItem;
	}
}