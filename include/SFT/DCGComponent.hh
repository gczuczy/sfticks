
#ifndef SFT_DCGCOMPONENT_H
#define SFT_DCGCOMPONENT_H

#include "FG/Building.hh"
#include "FG/FactoryConnectionComponent.hh"

#include <stdint.h>
#include <memory>
#include <functional>
#include <list>

namespace SFT {

  enum class DCGComponentType:uint8_t {
    Edge=0,
    Node,
  };

  struct DCGConnection;
  struct helpers_t;
  // This is a base class for edges and nodes
  class DCGComponent {
  public:
    DCGComponent()=delete;
    virtual ~DCGComponent()=0;
  protected:
    DCGComponent(DCGComponentType _ct);

  public:
    inline DCGComponentType componentType() const {return c_comptype;};
    virtual std::list<FG::BuildingSP> buildings()=0;
    // this one tries to connect all unconnected inouts,
    // and returns the unconnected BuildingSPs
    virtual std::list<FG::BuildingSP> tryConnect(helpers_t& _helpers)=0;
    virtual std::string dbgstr() const =0;
    virtual bool isGraphInput() const =0;
    virtual bool isGraphOutput() const =0;

  protected:
    FG::BuildingSP learnConnection(DCGConnection& _conn,
				   FG::FactoryConnectionComponentSP _fcc);

  private:
    DCGComponentType c_comptype;
  };
  typedef std::shared_ptr<DCGComponent> DCGComponentSP;

  // this is to remove a used entity from the pool
  // identifier is the instance() string, as key
  typedef std::function<void(const std::string&)> rmfn_t;
  // this is for registering new components
  typedef std::function<void(DCGComponentSP)> regcomp_t;
  // and this one is for checking whether a building
  // has already been handled handled or not
  typedef std::function<DCGComponentSP (FG::BuildingSP)> lookup_t;

  // and pack them together
  struct helpers_t {
    //rmfn_t rm;
    regcomp_t reg;
    lookup_t lookup;
  };

  /*
    Grouping the structures required for
    a connection.
    Some of these can be calculated, but cached here
    for faster access.

    (me)->connection->peerconnection->peer
  */
  struct DCGConnection {
    bool connected=false;
    DCGComponentSP peer=nullptr;
    FG::EFactoryConnectionDirection direction;
    FG::FactoryConnectionComponentSP connection=nullptr;
    FG::FactoryConnectionComponentSP peerconnection=nullptr;
    FG::InventoryComponentSP inventory=nullptr;
  };
}

#endif
