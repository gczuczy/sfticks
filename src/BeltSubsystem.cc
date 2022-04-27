
#include "BeltSubsystem.hh"

namespace SFT {

  BeltSubsystem::BeltSubsystem() {
  }

  BeltSubsystem::~BeltSubsystem() {
    c_dcgs.clear();
  }

  void BeltSubsystem::learn(FG::WorldSP _world) {
    /*
      First create a pool of entities. All items' root
      is Entity, so we can have all belts, attachments and various
      units inside. When the pool is reduced to zero, we have
      decomposed all of them to DCGs.
    */

    std::map<std::string, FG::EntitySP>  pool;

    for (auto it: _world->entities()) {
      if ( it.second->entityType() != FG::EntityType::GenericEntity ) {
	pool[it.first] = it.second;
      }
    }
    // allocate DCGs while the pool is not empty
    while (pool.size()>0) {
      DCGSP dcg = std::make_shared<DCG>();
      printf("Creating new DCG, started pool size %lu\n", pool.size());
      dcg->build(pool);
      printf("DCG done(%u items), remaining pool size %lu\n", dcg->size(), pool.size());
      c_dcgs.push_back(dcg);
      break;
    }
  }
}
