
#ifndef SFT_SAVEPROPERTIES_HH
#define SFT_SAVEPROPERTIES_HH

#include "PropertyInterface.hh"

namespace FG {

  class SaveProperties {
  public:
    SaveProperties()=default;
    virtual ~SaveProperties()=default;

  protected:
    void defineProperty(PropertyInterfaceSP _prop);
    void loadProperties(Reader& _reader);

  private:
    struct pdkey {
      pdkey(const std::string& _name, const int32_t _index);
      bool operator<(const pdkey& other) const;
      bool operator==(const pdkey& other) const;
      std::string name;
      int32_t index;
    };
    std::map<pdkey, PropertyInterfaceSP> c_propdefs;
  };

}

#endif
