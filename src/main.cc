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

#if 0
  // we have a Brave New World, let's examine it
  printf("Checking components\n");
  {
    for (auto it: world->storageUnits()) {
      printf(" ++ Entity:\n%s", it.second->str().c_str());
      for (auto cit: it.second->components()) {
	printf(" + Component:\n%s", cit.second->str().c_str());
      }
      // storage units
      printf("Inputs:\n");
      for (auto cit: it.second->inputs()) printf(" - %s\n", cit?cit->instance().c_str():"failed");
      printf("Outputs:\n");
      for (auto cit: it.second->outputs()) printf(" - %s\n", cit?cit->instance().c_str():"failed");
      printf("Inventories:\n");
      for (auto cit: it.second->inventories())
	printf(" - %s:%s\n",
	       cit.first.c_str(),
	       cit.second?cit.second->instance().c_str():"failed");
    }
  }
#endif
  
  return 0;
}
