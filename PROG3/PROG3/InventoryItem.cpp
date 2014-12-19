#include "InventoryItem.h"

namespace stain{
	InventoryItem::InventoryItem():
		amount(0)
	{

	}

	InventoryItem::~InventoryItem(){

	}

	int InventoryItem::invAmount(){
		return amount;
	}

	void InventoryItem::invAmount(int setAmount){
		amount = setAmount;
	}
}