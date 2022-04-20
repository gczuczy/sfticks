
#ifndef SFT_SAVEPROPERTIES_HH
#define SFT_SAVEPROPERTIES_HH

#include "PropertyInterface.hh"

#include <functional>

namespace FG {

  class SaveProperties {
  public:
    typedef std::function<void(Reader&)> supplemental_handler;
  public:
    SaveProperties()=default;
    virtual ~SaveProperties()=default;

  protected:
    void defineProperty(PropertyInterfaceSP _prop);
    void loadProperties(Reader& _reader, bool _debug=false);
    inline void defineSupplementalHandler(supplemental_handler _h) {
      c_suphandler = _h;
    }

  private:
    struct pdkey {
      pdkey(const std::string& _name, const int32_t _index);
      bool operator<(const pdkey& other) const;
      bool operator==(const pdkey& other) const;
      std::string name;
      int32_t index;
    };
    std::map<pdkey, PropertyInterfaceSP> c_propdefs;
    supplemental_handler c_suphandler;
  };

}

#endif
