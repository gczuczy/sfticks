
#ifndef SFT_INVENTORYSTACK_H
#define SFT_INVENTORYSTACK_H

#include <stdint.h>
#include <string>

namespace FG {

  struct InventoryItem {
    int32_t un1;
    std::string ItemType, un2, un3;
    inline std::string str() {
      return std::string("InventoryStack: ")+ItemType;
    };
  };

  struct InventoryStack {
    InventoryItem Item;
    int32_t NumItems;

    inline std::string str() {
      return "InventoryStack";
    };
  };

}

#endif
