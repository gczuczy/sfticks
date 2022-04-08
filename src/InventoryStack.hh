
#ifndef SFT_INVENTORYSTACK_H
#define SFT_INVENTORYSTACK_H

#include <stdint.h>
#include <string>

struct InventoryItem {
  int32_t un1;
  std::string ItemType, un2, un3;
};

struct InventoryStack {
  InventoryItem Item;
  int32_t NumItems;
};

#endif
