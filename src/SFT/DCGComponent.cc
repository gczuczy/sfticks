
#include "SFT/DCGComponent.hh"

namespace SFT {

  DCGComponent::DCGComponent(DCGComponentType _ct): c_comptype(_ct) {
  }

  DCGComponent::~DCGComponent() {
  }

  // this returns the peer's FG object
  // _conn.peer to be populated
  FG::BuildingSP DCGComponent::learnConnection(DCGConnection& _conn,
					       FG::FactoryConnectionComponentSP _fcc) {
    //printf("DCGComponent::learnConnection ");
    _conn.connected = false;
    // if it's not define, setting nullptr as not connected and leaving
    if ( !(_conn.connection = _fcc) ) {
      //printf("no fcc: %s\n", _fcc?"yes":"no");
      return nullptr;
    }

    // check the peer connection
    if ( !(_conn.peerconnection =
	   std::dynamic_pointer_cast<FG::FactoryConnectionComponent>(_fcc->connectedComponent())) ) {
      //printf(" no peerconnection\n");
      return nullptr;
    }

    // check whether there's a parent
    FG::BuildingSP bsp;
    if ( !(bsp = std::dynamic_pointer_cast<FG::Building>(_conn.peerconnection->parent())) ) {
      //printf(" no parent\n");
      return nullptr;
    }

    // now we are connected, and set stuff up
    _conn.connected = true;
    _conn.direction = _conn.connection->direction();

    // peer will be populated by the caller
    //printf(" great success %s\n", bsp->instance().c_str());
    return bsp;
  }
}
