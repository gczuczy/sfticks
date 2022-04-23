
#include "tests.hh"
#include <stdio.h>

#include "FGPowerInfoComponent.hh"
#include "FGJSONObject.hh"
#include "FGFactoryConnectionComponent.hh"

namespace SFT {
  void test_beltsplines(FG::WorldSP _world) {
    // belt spline checks
    for (auto it: _world->belts()) {
      auto sdata = it.second->splineData();

      printf("Belt(%.3f): %s\n", it.second->length(),
	     it.second->instance().c_str());
      printf(" Spline data:\n");
      for (int i=0; i<sdata.size(); ++i) {
	printf("  %i:\n", i);
	printf("   - Location: %s\n", sdata[i].Location.str().c_str());
	printf("   - ArriveTangent: %s\n", sdata[i].ArriveTangent.str().c_str());
	printf("   - LeaveTangent: %s\n", sdata[i].LeaveTangent.str().c_str());
      }
    }
  }

  void test_objrefs_convany(const std::string& _name, FG::FactoryConnectionComponentSP _fccsp) {
    auto comp = _fccsp->connectedComponent();

    printf("%s:\n", _name.c_str());
    if ( !comp ) {
      printf(" - Not connected\n");
      return;
    }
    printf("%s", comp->str().c_str());

    printf(" - Parent:\n%s", comp->parent()->str().c_str());
  }

  void test_objrefs(FG::WorldSP _world) {
    // objref resolver tests
    for (auto it: _world->belts()) {
      printf("\n\nChecking %s\n", it.second->instance().c_str());
      test_objrefs_convany("Any0", it.second->ConveyorAny0());
      test_objrefs_convany("Any1", it.second->ConveyorAny1());

      printf("\n Belt items:\n");
      for (auto biit: it.second->beltItems()) {
	FG::JSONObjectSP item = biit.item.as<FG::JSONObject>();
	printf("  - %.2f %s / ", biit.position, biit.item.pathName().c_str());
	if ( item ) printf("%s\n", item->className().c_str());
	else printf("lookup failed\n");
      }
      if ( it.second->beltItems().size()>0 ) break;
    }
  }

  void test_world(FG::WorldSP _world) {
    // we have a Brave New World, let's examine it
    printf("Checking components\n");
    {
      //std::set<std::string> filter{"Build_MinerMk1_C", "Build_MinerMk2_C", "Build_MinerMk3_C"};
      std::set<std::string> filter;
      for (auto it: _world->iounits()) {
	if ( filter.size() &&
	     filter.find(it.second->className()) == filter.end() ) continue;
	printf("\n\n ++ Entity:\n%s", it.second->str().c_str());
	for (auto cit: it.second->components()) {
	  printf(" + Component:\n%s%s", cit.second->str().c_str(), cit.second->compdetails().c_str());
	}
#if 0
	printf("ConveyorAny0:\n%s", it.second->ConveyorAny0()->compdetails().c_str());
	printf("ConveyorAny1:\n%s", it.second->ConveyorAny1()->compdetails().c_str());
#endif
	printf("Inputs:\n");
	for (auto cit: it.second->inputs()) {
	  if ( cit ) {
	    printf(" - %s\n%s", cit->instance().c_str(), cit->compdetails().c_str());
	  } else {
	    printf(" - failed\n");
	  }
	}
	printf("Outputs:\n");
	for (auto cit: it.second->outputs()) {
	  if ( cit ) {
	    printf(" - %s\n%s", cit->instance().c_str(), cit->compdetails().c_str());
	  } else {
	    printf(" - failed\n");
	  }
	}
	printf("Inventories:\n");
	for (auto cit: it.second->inventories()) {
	  printf(" - %s:", cit.first.c_str());
	  if ( cit.second ) {
	    printf("%s\n%s", cit.second->instance().c_str(), cit.second->compdetails().c_str());
	  } else {
	    printf("failed\n");
	  }
	}
	printf("PowerInfo:\n");
	try {
	  auto pi = it.second->powerInfo().as<FG::PowerInfoComponent>();
	  if ( pi ) {
	    printf("%s", pi->str().c_str());
	  } else {
	    printf("Lookup failed\n");
	  }
	}
	catch (SFT::Exception& e) {
	  printf("powerInfo lookup failed: %s\n", e.what());
	}
      }
    }
  }
}
