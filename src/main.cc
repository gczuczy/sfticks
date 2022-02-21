#include <stdio.h>

#include <exception>
#include <iostream>

#include <boost/program_options.hpp>

#include "Loader.hh"
#include "Timer.hh"

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

  // parse the file
  try {
    Timer tl("Loader");
    Loader *l = new Loader(filename);

    l->parse();
  }
  catch (std::exception e) {
    printf("Caught exception\n");
  }
  return 0;
}
