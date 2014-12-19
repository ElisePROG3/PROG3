#ifndef INVENTORYITEM_H
#define INVENTORYITEM_H

namespace stain{
	class InventoryItem{
	public:
		int invAmount();
		void invAmount(int setAmount);
		virtual ~InventoryItem();
	protected:
		InventoryItem();
		int amount;
	};
}
#endif