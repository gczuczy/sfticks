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
  catch (std::exception &e) {
    printf("Caught exception: %s\n", e.what());
    return -2;
  }

  // we have a Brave New World, let's examine it
  printf("Checking belts\n");
  {
    for (auto it: world->iounits()) {
      printf(" ++ Entity:\n%s", it.second->str().c_str());
      for (auto cit: it.second->components()) {
	printf(" + Component:\n%s", cit.second->str().c_str());
      }
#if 1
      // IOUnits
      printf("Inputs:\n");
      for (auto cit: it.second->inputs()) printf(" - %s\n", cit?cit->instance().c_str():"failed");
      printf("Outputs:\n");
      for (auto cit: it.second->outputs()) printf(" - %s\n", cit?cit->instance().c_str():"failed");
      printf("InputInventory: %s\n",
	     it.second->InputInventory()?it.second->InputInventory()->instance().c_str():"failed");
      printf("OutputInventory: %s\n",
	     it.second->OutputInventory()?it.second->OutputInventory()->instance().c_str():"failed");
      printf("InventoryPotential: %s\n",
	     it.second->InventoryPotential()?it.second->InventoryPotential()->instance().c_str():"failed");
#endif
#if 0
      // beltlogics
      printf("Inputs:\n");
      for (auto cit: it.second->inputs()) printf(" - %s\n", cit?cit->instance().c_str():"failed");
      printf("Outputs:\n");
      for (auto cit: it.second->outputs()) printf(" - %s\n", cit?cit->instance().c_str():"failed");
      printf("StorageInventory: %s\n", it.second->StorageInventory()?it.second->StorageInventory()->instance().c_str():"failed");
#endif
#if 0
      // Belts
      //printf(" - ConveyorAny0: %s\n", it.second->ConveyorAny0()? it.second->ConveyorAny0()->instance().c_str():"no");
      //printf(" - ConveyorAny1: %s\n", it.second->ConveyorAny1()? it.second->ConveyorAny1()->instance().c_str():"no");
#endif
    }
  }
  
  return 0;
}
