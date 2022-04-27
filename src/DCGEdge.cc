
#include <stdio.h>

#include "DCGEdge.hh"
#include "Exception.hh"
#include <functional>

namespace SFT {

  DCGEdge::DCGEdge(FG::ConveyorBeltSP _belt, helpers_t& _helpers)
    : DCGComponent(DCGComponentType::Edge), c_throughput(_belt->throughput()) {

    c_input.direction = FG::EFactoryConnectionDirection::FCD_INPUT;
    c_output.direction = FG::EFactoryConnectionDirection::FCD_OUTPUT;
    c_belts.push_back(_belt);

    std::function<void(FG::FactoryConnectionComponentSP)> walk =
      [&](FG::FactoryConnectionComponentSP _conn) {
	printf("  Processing belt conncomp %s", _conn?_conn->instance().c_str():"none\n");
	// partially similar logic to DCGComponent::learnConnection
	if ( !_conn ) return;

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
	    printf(" input");
	    c_input.connection = _conn;
	    c_input.connected = false;
	  } else if ( isoutput ) {
	    printf(" output");
	    c_output.connection = _conn;
	    c_output.connected = false;
	  } else {
	    EXCEPTION("Unknown direction");
	  }
	  printf(" no conncomp\n");
	  return;
	}

	// see whether it's a belt or other building
	auto belt = std::dynamic_pointer_cast<FG::ConveyorBelt>(conncomp->parent());

	// if it's a belt, then:
	// A) same speed AND opposite component direction (out->in) = attach here
	// B) differnt speed OR same compdirs (out->out/in->in) = new edge connection
	if ( belt ) {
	  // Sanity check: if this belt has been procesed earlier, something is wrong
	  if ( _helpers.lookup(belt) )
	    EXCEPTION("Edge segment belt already in use");

	  if ( belt->throughput() == c_throughput &&
	       _conn->direction() != conncomp->direction() ) {
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

	    printf("same speed belt added\n");
	    walk(nextcomp);
	    return;
	  } else { // belt but different speed or direction mismatch
	    // different speed or same direction, it's a separate edge
	    FG::BuildingSP bsp;
	    if ( isinput ) {
	      bsp = learnConnection(c_input, conncomp);
	      c_input.peer = _helpers.lookup(bsp);
	    } else {
	      bsp = learnConnection(c_output, conncomp);
	      c_output.peer = _helpers.lookup(bsp);
	    }
	    return;
	  }
	  return;
	} // if belt

	// else it's a building
	auto bsp = std::dynamic_pointer_cast<FG::Building>(conncomp->parent());
	// something is wrong
	if ( !bsp )
	  EXCEPTION("No parent to connection peer comp");

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
      }; // end of walk lambda
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

    auto collect = [&](DCGConnection& item) {
      // if it's an empty port, we leave it
      if ( !item.connected ) return;
      
      // if the peer is associated, that means we have it
      // in the propert state
      if ( item.peer ) return;

      // if the item is not associated, then we try to do so
      // and if it still cannot be done, we add it
      FG::BuildingSP bsp = std::dynamic_pointer_cast<FG::Building>(item.peerconnection->parent());
      if ( !(item.peer = _helpers.lookup(bsp)) ) {
	rv.push_back(bsp);
      }
    };

    collect(c_input);
    collect(c_output);

    return rv;
  }
}
