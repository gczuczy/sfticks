#include <stdio.h>

#include <iostream>

#include <boost/program_options.hpp>

#include "Loader.hh"
#include "Timer.hh"
#include "Exception.hh"
#include "FGDocsJSON.hh"
#include "tests.hh"
#include "BeltSubsystem.hh"

namespace po = boost::program_options;

int main(int argc, char *argv[]) {
  std::string savefile, docsjson;

  // command line options
  po::options_description desc("SatisFactory ticks options");
  desc.add_options()
    ("help", "Show the help message")
    ("docs-json", po::value<std::string>(&docsjson)->required(), "Path to the Docs.json file")
    ("save-file", po::value<std::string>(&savefile)->required(), "Path to the save file")
    ;

  po::positional_options_description p;
  p.add("docs-json", 1);
  p.add("save-file", 1);

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

  // check the docs.json first
  printf("Docsjson: %s\n", docsjson.c_str());
  std::shared_ptr<FG::DocsJSON> objdump;
  try {
    SFT::Timer t("docs.json parse");
    objdump = std::make_shared<FG::DocsJSON>(docsjson);
  }
  catch (SFT::Exception &e) {
    printf("SFT::Exception: %s\n", e.what());
    return -1;
  }
#if 0
  catch (std::exception& e) {
    printf("std::exception: %s\n", e.what());
    return -2;
  }
#endif

  // the world we'll load it into
  FG::WorldSP world;

  // parse the file
  try {
    SFT::Loader *l = new SFT::Loader(savefile);
    SFT::Timer tl("World deserialization");

    world = l->parse();
  }
  catch (SFT::Exception &e) {
    printf("Caught exception: %s\n", e.what());
    return -1;
  }
  // termination here for debugging is good for now
#if 0
  catch (std::bad_weak_ptr &e) {
    throw e;
  }
  catch (std::exception &e) {
    printf("Caught exception: %s\n", e.what());
    return -2;
  }
#endif

  SFT::BeltSubsystemUP bss(std::make_unique<SFT::BeltSubsystem>());
  printf("Teaching Beltsubsystem ...\n");
  try {
    SFT::Timer t("Teaching BeltSubsystem");
    bss->learn(world);
  }
  catch (SFT::Exception& e) {
    printf("SFT::Exception: %s\n", e.what());
    return -1;
  }

  try {
    //SFT::test_beltsplines(world);
    //SFT::test_objrefs(world);
    //SFT::test_world(world);
  }
  catch (SFT::Exception& e) {
    printf("Caught SFT::Exception: %s\n", e.what());
    return -1;
  }
  catch (std::exception& e) {
    printf("Caught std::exception: %s\n", e.what());
    return -2;
  }

  // deallocation
  bss = nullptr;
  world = nullptr;
  return 0;
}
