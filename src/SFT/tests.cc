
#include "SFT/tests.hh"
#include <stdio.h>

#include "FG/PowerInfoComponent.hh"
#include "FG/JSONObject.hh"
#include "FG/FactoryConnectionComponent.hh"

#include <map>

namespace SFT {
  void test_beltsplines(testargs& _args) {
    // belt spline checks
    for (auto it: _args.world->belts()) {
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

  void test_objrefs(testargs& _args) {
    // objref resolver tests
    for (auto it: _args.world->belts()) {
      printf("\n\nChecking %s\n", it.second->instance().c_str());
      test_objrefs_convany("input", it.second->input());
      test_objrefs_convany("output", it.second->output());

      printf("\n Belt items:\n");
      for (auto biit: it.second->beltItems()) {
	printf("%s\n", biit.item->className().c_str());
      }
      if ( it.second->beltItems().size()>0 ) break;
    }
  }

  void test_world(testargs& _args) {
    // we have a Brave New World, let's examine it
    printf("Checking components\n");
    {
      //std::set<std::string> filter{"Build_MinerMk1_C", "Build_MinerMk2_C", "Build_MinerMk3_C"};
      std::set<std::string> filter;
      for (auto it: _args.world->iounits()) {
	if ( filter.size() &&
	     filter.find(it.second->className()) == filter.end() ) continue;
	printf("\n\n ++ Entity:\n%s", it.second->str().c_str());
	for (auto cit: it.second->components()) {
	  printf(" + Component:\n%s%s", cit.second->str().c_str(), cit.second->compdetails().c_str());
	}
#if 0
	printf("input:\n%s", it.second->input()->compdetails().c_str());
	printf("output:\n%s", it.second->output()->compdetails().c_str());
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
	  auto pi = it.second->powerInfo();
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
  } // test_args.world

  void test_entityticks(testargs& _args) {
    std::map<FG::EntityType, FG::BuildingSP> subjects;

    // first we're looking for subjects for all entites
    for (auto it: _args.world->entities()) {
      auto et = it.second->entityType();
      if ( et == FG::EntityType::GenericEntity ||
	   subjects.find(et) != subjects.end() ) continue;
      if (FG::ConveyorBeltSP belt; (belt = std::dynamic_pointer_cast<FG::ConveyorBelt>(it.second)) ) {
	if ( !belt->beltItems().size() ) continue;
	subjects[et] = belt;
      } else {
	subjects[et] = std::dynamic_pointer_cast<FG::Building>(it.second);
      }
    }

    printf("Collected %lu subjects\n", subjects.size());

    //assemble the tickinfo
    tickinfo_t ti;
    ti.tickno = _args.world->headers().saveDate()+1;
    ti.timedelta = 1.0/(1.0*_args.frequency);

    printf("Running ConveyorBelt doTickCache...\n");
    FG::ConveyorBelt::doTickCache(ti);

    // now test each
    int i=0, max=3;
    for (auto it: subjects) {
      if ( i++ >= max ) break;
      printf("\n--\nTesting subject: %s\n", it.second->instance().c_str());
      it.second->doTick(ti);
    }
  }
}
