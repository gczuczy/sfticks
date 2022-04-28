
#include <stdio.h>
#include "DCGNode.hh"
#include "misc.hh"
#include "FGConveyorAttachmentSplitter.hh"
#include "FGConveyorAttachmentMerger.hh"

namespace SFT {
  DCGNode::DCGNode(FG::BuildingSP _building, helpers_t& _helpers)
    : DCGComponent(DCGComponentType::Node), c_building(_building) {

    // This is a non-belt building, meaning it might have multiple
    // in and outputs

    c_inputs.clear();
    c_outputs.clear();
    auto inouts = [&](std::list<DCGConnection>& local, FG::Building::Connections& remote) {
      for (auto& it: remote) {
	auto& conn = local.emplace_back();
	auto bsp = learnConnection(conn, it);
	
	if ( bsp ) {
#ifdef DEBUG_DCG_BUILD
	  printf(" - Connection to %s .. ", bsp->instance().c_str());
#endif
	  if ( (conn.peer = _helpers.lookup(bsp)) ) {
#ifdef DEBUG_DCG_BUILD
	    printf(" found\n");
#endif
	  } else {
#ifdef DEBUG_DCG_BUILD
	    printf(" not yet found, TBD\n");
#endif
	  }
	} else {
#ifdef DEBUG_DCG_BUILD
	  printf("Not connected\n");
#endif
	}
      }
    }; // lambda inouts

    inouts(std::ref(c_inputs), std::ref(c_building->inputs()));
    inouts(c_outputs, c_building->outputs());
  }
  
  DCGNode::~DCGNode() {
  }

  std::list<FG::BuildingSP> DCGNode::buildings() {
    return std::list<FG::BuildingSP>{c_building};
  }

  std::list<FG::BuildingSP> DCGNode::tryConnect(helpers_t& _helpers) {
    std::list<FG::BuildingSP> rv;

#ifdef DEBUG_DCG_BUILD
    printf("DCGNode::tryConnect()\n");
#endif

    auto collect = [&](DCGConnection& item) {
#ifdef DEBUG_DCG_BUILD
      printf(" checking %s", item.connection?item.connection->instance().c_str():"!connection");
#endif
      // if it's an empty port, we leave it
      if ( !item.connected ) {
#ifdef DEBUG_DCG_BUILD
	printf(" not connected\n");
#endif
	return;
      }
      
      // if the peer is associated, that means we have it
      // in the propert state
      if ( item.peer ) {
#ifdef DEBUG_DCG_BUILD
	printf(" peer present\n");
#endif
	return;
      }

      // if the item is not associated, then we try to do so
      // and if it still cannot be done, we add it
      FG::BuildingSP bsp = std::dynamic_pointer_cast<FG::Building>(item.peerconnection->parent());
      if ( !(item.peer = _helpers.lookup(bsp)) ) {
	rv.push_back(bsp);
#ifdef DEBUG_DCG_BUILD
	printf(" peer lookup failed\n");
#endif
      } else {
#ifdef DEBUG_DCG_BUILD
	printf(" succewssful lookup of %s\n", bsp->instance().c_str());
#endif
      }
    };

    for (auto& it: c_inputs) collect(std::ref(it));
    for (auto& it: c_outputs) collect(std::ref(it));

    return rv;
  }

  std::string DCGNode::dbgstr() const {
    std::string rv;

    rv += strprintf("Node(%s): I:", c_building->instance().c_str());
    for (auto& it:c_inputs) {
      rv += strprintf(" %s", it.connected?"conn":"noconn");
    }
    rv += strprintf(" O:");
    for (auto& it:c_outputs) {
      rv += strprintf(" %s", it.connected?"conn":"noconn");
    }
    rv += strprintf("\n");

#ifdef DEBUG_DCG_BUILD
    // for in or out nodes, examine types of interest more closely
    if ( isGraphInput() || isGraphOutput() ) {
      if (FG::ConveyorAttachmentSplitterSP cau;
	  (cau = std::dynamic_pointer_cast<FG::ConveyorAttachmentSplitter>(c_building))) {
	//examine more closely if it's a splitter
	if ( isGraphInput() ) {
	  printf("Details %s\n", cau->instance().c_str());
	  // a splitter shouldn't be an input, single input and that should be plugged
	  auto in = cau->inputs()[0];
	  if ( in ) {
	    printf("%s\n", in->compdetails().c_str());
	  } else {
	    printf("No input object");
	  }
	}
      } else if (FG::ConveyorAttachmentMergerSP cau;
		 (cau = std::dynamic_pointer_cast<FG::ConveyorAttachmentMerger>(c_building))) {
	//examine more closely if it's a splitter
	if ( isGraphOutput() ) {
	  printf("Details %s\n", cau->instance().c_str());
	  // a merger shouldn't be an output, single output and that should be plugged
	  auto in = cau->outputs()[0];
	  if ( in ) {
	    printf("%s\n", in->compdetails().c_str());
	  } else {
	    printf("No input object");
	  }
	}
      }

    } // if in/oput
#endif

    return rv;
  }

  bool DCGNode::isGraphInput() const {
    for (auto& it: c_inputs)
      if ( it.connected ) return false;
    return true;
  }

  bool DCGNode::isGraphOutput() const {
    for (auto& it: c_outputs)
      if ( it.connected ) return false;
    return true;
  }
}
