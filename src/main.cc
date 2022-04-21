#include <stdio.h>

#include <iostream>

#include <boost/program_options.hpp>

#include "Loader.hh"
#include "Timer.hh"
#include "Exception.hh"

namespace po = boost::program_options;

int main(int argc, char *argv[]) {
  std::string filename;

  // command line options
  po::options_description desc("SatisFactory ticks options");
  desc.add_options()
    ("help", "Show the help message")
    ("save-file", po::value<std::string>(&filename)->required(), "Path to the save file")
    ;

  po::positional_options_description p;
  p.add("save-file", -1);

  po::variables_map vm;
  try {
    po::store(po::command_line_parser(argc, argv).
	      options(desc).positional(p).run(), vm);
    if ( vm.count("help") ) {
      std::cout << desc << std::endl;
      return 1;
    }
    po::notify(vm);
  }
  catch (boost::program_options::required_option &e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }
  catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }

  if ( vm.count("help") ) {
    std::cout << desc << std::endl;
    return 1;
  }

  // the world we'll load it into
  std::shared_ptr<FG::World> world;

  // parse the file
  try {
    SFT::Loader *l = new SFT::Loader(filename);
    SFT::Timer tl("World deserialization");

    world = l->parse();
  }
  catch (SFT::Exception &e) {
    printf("Caught exception: %s\n", e.what());
    return -1;
  }
#if 0
  catch (std::bad_weak_ptr &e) {
    throw e;
  }
  catch (std::exception &e) {
    printf("Caught exception: %s\n", e.what());
    return -2;
  }
#endif

#if 1
  // belt spline checks
  for (auto it: world->belts()) {
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
    printf(" Belt items:\n");
    for (auto biit: it.second->beltItems()) {
      printf("  - %.2f %s\n", biit.position, biit.item.pathName().c_str());
    }
  }
#endif

#if 0
  // objref resolver tests
  for (auto it: world->belts()) {
    auto any0 = it.second->ConveyorAny0();
    auto any1 = it.second->ConveyorAny1();
    auto comp0 = any0->mConnectedComponent();
    auto comp1 = any1->mConnectedComponent();

    printf("Any0:\n - Level: %s\n - Path: %s\n",
	   comp0.levelName().c_str(),
	   comp0.pathName().c_str());
    comp0.resolve();
    auto obj0 = comp0.object();
    printf("%s", obj0->str().c_str());
    if ( obj0->isComponent() ) {
      FG::ComponentSP objc0;
      if ( !(objc0 = comp0.as<FG::Component>()) ) {
	printf(" - FG::Component failed\n");
      } else {
	printf(" - FG::Component now\n");
	printf(" - Parent: %s\n", objc0->parentEntityName().c_str());
	try {
	  printf("%s", objc0->parent()->str().c_str());
	}
	catch (SFT::Exception& e) {
	  printf("Error %s\n", e.what());
	}
      } // successful component
    }
    break;
  }
#endif

#if 0
  // we have a Brave New World, let's examine it
  printf("Checking components\n");
  {
    //std::set<std::string> filter{"Build_MinerMk1_C", "Build_MinerMk2_C", "Build_MinerMk3_C"};
    std::set<std::string> filter;
    for (auto it: world->iounits()) {
      if ( filter.size() &&
	   filter.find(it.second->objectType()) == filter.end() ) continue;
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
	auto pi = it.second->powerInfo().object();
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
#endif
  
  return 0;
}
