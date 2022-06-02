#include <stdio.h>
#include <stdint.h>

#include <iostream>
#include <string>
#include <map>

#include <boost/program_options.hpp>

#include "SFT/Loader.hh"
#include "SFT/Timer.hh"
#include "SFT/Exception.hh"
#include "FG/DocsJSON.hh"
#include "SFT/tests.hh"
#include "SFT/BeltSubsystem.hh"

namespace po = boost::program_options;

struct argdata {
  std::string savefile;
  std::string docsjson;
  std::string test;
  uint32_t frequency;
};

int parseargs(int argc, char* argv[], argdata& data);

int main(int argc, char *argv[]) {
  argdata args;
  args.frequency = 30;

  if (int rv; (rv = parseargs(argc, argv, args))!=0 ) {
    return rv;
  }

  std::map<std::string, SFT::testfun_t> tests = {
    {"beltsplines", SFT::test_beltsplines},
    {"objrefs", SFT::test_objrefs},
    {"world", SFT::test_world},
    {"entityticks", SFT::test_entityticks},
    //{"", SFT::test_},
  };
  

  if ( args.test != "" && tests.find(args.test) == tests.end()) {
    printf("Test not found: %s\nAvailable tests:", args.test.c_str());
    for (auto it: tests) printf(" %s", it.first.c_str());
    printf("\n");
    return -3;
  }

  // check the docs.json first
  printf("Docsjson: %s\n", args.docsjson.c_str());
  std::shared_ptr<FG::DocsJSON> objdump;
  try {
    SFT::Timer t("docs.json parse");
    objdump = std::make_shared<FG::DocsJSON>(args.docsjson);
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
    SFT::Loader *l = new SFT::Loader(args.savefile);
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

  if ( args.test.length() == 0 ) {
    // no tests
    printf("Starting simulation...\n");
  } else {
    printf("Testing mode: %s\n", args.test.c_str());
    // testing mode
    try {
      auto it = tests.find(args.test);
      SFT::testargs targs;
      targs.world = world;
      targs.frequency = args.frequency;
      it->second(std::ref(targs));
    }
    catch (SFT::Exception& e) {
      printf("Caught SFT::Exception: %s\n", e.what());
      return -1;
    }
    catch (std::exception& e) {
      printf("Caught std::exception: %s\n", e.what());
      return -2;
    }
  }

  // deallocation
  bss = nullptr;
  world = nullptr;
  return 0;
}

int parseargs(int argc, char* argv[], argdata& data) {
  
  // command line options
  po::options_description desc("SatisFactory ticks options");
  desc.add_options()
    ("help,h", "Show the help message")
    ("frequency,f", po::value<uint32_t>(&data.frequency)->default_value(data.frequency), "Processing frequency [Hz]")
    ("test,t", po::value<std::string>(&data.test), "Specify test to run instead of the main loop")
    ("docs-json", po::value<std::string>(&data.docsjson)->required(), "Path to the Docs.json file")
    ("save-file", po::value<std::string>(&data.savefile)->required(), "Path to the save file")
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
    return 2;
  }
  catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
    return 3;
  }

  if ( vm.count("help") ) {
    std::cout << desc << std::endl;
    return 4;
  }

  return 0;
}

