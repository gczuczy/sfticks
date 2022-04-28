
#include "BeltSubsystem.hh"
#include "FGConveyorBelt.hh"
#include "FGBuilding.hh"

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
      // skipping generic entities
      if ( it.second->entityType() == FG::EntityType::GenericEntity ) continue;

      // if it's not a belt, check the connections
      // if there are no belt ports, we're skipping it, that's out of scope
      auto isbelt = std::dynamic_pointer_cast<FG::ConveyorBelt>(it.second);
      if ( !isbelt ) {
	auto bsp = std::dynamic_pointer_cast<FG::Building>(it.second);
	// and skip if it has no inputs and outputs
	if ( bsp->inputs().size()==0 && bsp->outputs().size()==0 ) {
#ifdef DEBUG_DCG_BUILD
	  printf("Skipping from pool: %s\n", it.first.c_str());
#endif
	  continue;
	}
      }

      // and finally we add it to the pool
      pool[it.first] = it.second;
    }
    // allocate DCGs while the pool is not empty
    while (pool.size()>0) {
      DCGSP dcg = std::make_shared<DCG>();
      auto start = pool.size();
#ifdef DEBUG_DCG_BUILD
      printf(" - Creating new DCG, starting pool size %lu\n", start);
#endif
      dcg->build(pool);
      auto end = pool.size();
      printf("  - DCG built (%u items), remaining pool size %lu\n", dcg->size(), end);
      c_dcgs.push_back(dcg);
      uint64_t used = start-end;
      if ( dcg->size() > used ) printf(" ++ anomaly DCG:%u used:%lu!\n%s",
				       dcg->size(), used,
				       dcg->dbgstr().c_str());
    }
    printf("Created %lu DCGs\n", c_dcgs.size());

#if 0
    // dev checks
    for (auto& it: c_dcgs) {
      if ( it->size()>3 ) continue;
      printf("\n\n%s", it->dbgstr().c_str());
    }
#endif
  }
}
