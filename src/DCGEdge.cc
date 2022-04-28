
#include <stdio.h>

#include "DCGEdge.hh"
#include "Exception.hh"
#include "misc.hh"

#include <functional>

namespace SFT {

  DCGEdge::DCGEdge(FG::ConveyorBeltSP _belt, helpers_t& _helpers)
    : DCGComponent(DCGComponentType::Edge), c_throughput(_belt->throughput()) {

    c_input.direction = FG::EFactoryConnectionDirection::FCD_INPUT;
    c_output.direction = FG::EFactoryConnectionDirection::FCD_OUTPUT;
    c_belts.push_back(_belt);

    // now walk both ends
    walk(_belt->ConveyorAny0(), _helpers);
    walk(_belt->ConveyorAny1(), _helpers);

    // calculate the total length
    for (auto& it: c_belts) c_length += it->length();

    //printf("Edge created, belts (len: %.2f\n", c_length);
    //for (auto& it: c_belts) printf(" - %s\n", it->instance().c_str());
  }
  
  DCGEdge::~DCGEdge() {
  }

  std::list<FG::BuildingSP> DCGEdge::buildings() {
    std::list<FG::BuildingSP> rv;

    for (auto it: c_belts) rv.push_back(it);
    return rv;
  }

  std::list<FG::BuildingSP> DCGEdge::tryConnect(helpers_t& _helpers) {
    std::list<FG::BuildingSP> rv;

#ifdef DEBUG_DCG_BUILD
    printf("DCGEdge::tryConnect\n");
#endif

    auto collect = [&](DCGConnection& item) {
      if ( !item.connection ) {
#ifdef DEBUG_DCG_BUILD
	printf(" Connection missing\n");
#endif
	return;
      }
#ifdef DEBUG_DCG_BUILD
      printf(" Checking %s ", item.connection->instance().c_str());
#endif
      // if it's an empty port, we leave it
      if ( !item.connected ) {
#ifdef DEBUG_DCG_BUILD
	printf(" noconn\n");
#endif
	return;
      }
      
      // if the peer is associated, that means we have it
      // in the propert state
      if ( item.peer ) {
#ifdef DEBUG_DCG_BUILD
	printf(" has peer\n");
#endif
	return;
      }

      // if the item is not associated, then we try to do so
      // and if it still cannot be done, we add it
      FG::BuildingSP bsp = std::dynamic_pointer_cast<FG::Building>(item.peerconnection->parent());
      if ( !(item.peer = _helpers.lookup(bsp)) ) {
	rv.push_back(bsp);
#ifdef DEBUG_DCG_BUILD
	printf(" returning\n");
#endif
      }
    };

    collect(std::ref(c_input));
    collect(std::ref(c_output));

    ////printf(" retsize: %lu\n", rv.size());
    return rv;
  }

  std::string DCGEdge::dbgstr() const {
    std::string rv;

    rv = strprintf("Edge len: %.2f in:%s out:%s\n", c_length,
		   c_input.connected?"conn":"noconn",
		   c_output.connected?"conn":"noconn");
    rv += strprintf(" Belt segments:\n");
    for (auto& it: c_belts)
      rv += strprintf("  - %s\n", it->instance().c_str());

    return rv;
  }

  bool DCGEdge::isGraphInput() const {
    if ( c_input.connected ) return false;
    return true;
  }

  bool DCGEdge::isGraphOutput() const {
    if ( c_output.connected ) return false;
    return true;
  }
  
  void DCGEdge::walk(FG::FactoryConnectionComponentSP _conn, helpers_t& _helpers) {
#ifdef DEBUG_DCG_BUILD
    printf("  Processing belt conncomp %s", _conn?_conn->instance().c_str():"none\n");
#endif
    // partially similar logic to DCGComponent::learnConnection
    if ( !_conn ) {
#ifdef DEBUG_DCG_BUILD
      printf(" noconn\n");
#endif
      return;
    }

    // there are other as well
    bool isinput = _conn->direction() == FG::EFactoryConnectionDirection::FCD_INPUT;
    bool isoutput = _conn->direction() == FG::EFactoryConnectionDirection::FCD_OUTPUT;

    if ( !isinput && !isoutput )
      EXCEPTION("FCC is neither in or out");

    FG::FactoryConnectionComponentSP conncomp, peercomp;
    conncomp = std::dynamic_pointer_cast<FG::FactoryConnectionComponent>(_conn->connectedComponent());

    if ( !conncomp ) {
      // no peer connected
      if ( isinput ) {
#ifdef DEBUG_DCG_BUILD
	printf(" input");
#endif
	c_input.connection = _conn;
	c_input.connected = false;
      } else if ( isoutput ) {
#ifdef DEBUG_DCG_BUILD
	printf(" output");
#endif
	c_output.connection = _conn;
	c_output.connected = false;
      } else {
	EXCEPTION("Unknown direction");
      }
#ifdef DEBUG_DCG_BUILD
      printf(" no conncomp\n");
#endif
      return;
    }

    // see whether it's a belt or other building
    auto belt = std::dynamic_pointer_cast<FG::ConveyorBelt>(conncomp->parent());

    // if it's a belt, then:
    // A) same speed AND opposite component direction (out->in) = attach here
    // B) differnt speed OR same compdirs (out->out/in->in) = new edge connection
    if ( belt ) {
#ifdef DEBUG_DCG_BUILD
      printf(" belt");
#endif

      if ( belt->throughput() == c_throughput &&
	   _conn->direction() != conncomp->direction() ) {
#ifdef DEBUG_DCG_BUILD
	printf(" same");
#endif

	// Sanity check: if this belt has been procesed earlier, something is wrong
	// this only applies for samespeed belts. differents are different edges
	if ( _helpers.lookup(belt) )
	  EXCEPTION(strprintf("Edge segment belt already in use: %s", belt->instance().c_str()));

	// same type of belt, attach to this virtual segment in the edge
	FG::FactoryConnectionComponentSP nextcomp;
	if ( isinput ) {
	  c_belts.push_front(belt);
	} else if ( isoutput ) {
	  c_belts.push_back(belt);
	} else {
	  EXCEPTION("Neither input or output");
	}
	if ( belt->ConveyorAny0()->direction() == _conn->direction() ) {
	  nextcomp = belt->ConveyorAny0();
	} else if ( belt->ConveyorAny1()->direction() == _conn->direction() ) {
	  nextcomp = belt->ConveyorAny1();
	} else {
	  EXCEPTION("ConveyorAny0/1 have the same direction");
	}

#ifdef DEBUG_DCG_BUILD
	printf(" added\n  %s\n", belt->instance().c_str());
#endif
	walk(nextcomp, _helpers);
      } else { // belt but different speed or direction mismatch
#ifdef DEBUG_DCG_BUILD
	printf(" different");
#endif
	// different speed or same direction, it's a separate edge
	FG::BuildingSP bsp;
	if ( isinput ) {
#ifdef DEBUG_DCG_BUILD
	  printf(" input");
#endif
	  bsp = learnConnection(c_input, _conn);
	  c_input.peer = _helpers.lookup(bsp);
	} else {
#ifdef DEBUG_DCG_BUILD
	  printf(" output");
#endif
	  bsp = learnConnection(c_output, _conn);
	  c_output.peer = _helpers.lookup(bsp);
	}
#ifdef DEBUG_DCG_BUILD
	printf(" added\n  %s\n", bsp->instance().c_str());
#endif
      }
      return;
    } // if belt

    // else it's a building
    auto bsp = std::dynamic_pointer_cast<FG::Building>(conncomp->parent());
    // something is wrong
    if ( !bsp )
      EXCEPTION(strprintf("No parent to connection peer comp: %s", conncomp->instance().c_str()));

    // this will be a node
    if ( isinput ) {
      bsp = learnConnection(c_input, _conn);
      c_input.peer = _helpers.lookup(bsp);
    } else if ( isoutput ) {
      bsp = learnConnection(c_output, _conn);
      c_output.peer = _helpers.lookup(bsp);
    } else {
      EXCEPTION("Edge bsp neither in our out");
    }
#ifdef DEBUG_DCG_BUILD
    printf(" bulding connection added\n  %s\n", bsp->instance().c_str());
#endif
  }
}
