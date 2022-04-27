
#ifndef SFT_BELTSUBSYSTEM_H
#define SFT_BELTSUBSYSTEM_H

#include "World.hh"
#include "DCG.hh"

#include <memory>
#include <list>

namespace SFT {

  class BeltSubsystem {
  private:
  public:
    BeltSubsystem();
    BeltSubsystem(const BeltSubsystem&) = delete;
    BeltSubsystem(BeltSubsystem&&) = delete;
    ~BeltSubsystem();

    void learn(FG::WorldSP _world);

  private:
    std::list<std::shared_ptr<DCG> > c_dcgs;
  };
  typedef std::unique_ptr<BeltSubsystem> BeltSubsystemUP;
}

#endif
