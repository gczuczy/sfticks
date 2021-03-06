
#ifndef SFT_FGOBJECTHEADER_H
#define SFT_FGOBJECTHEADER_H

#include "FG/Saveable.hh"
#include "FG/ObjectReference.hh"

#include <list>
#include <memory>

namespace FG {

  class ObjectHeader: public Saveable {
  private:
    struct instdata {
      std::string str1; // namespace
      std::string str2; // :PersistentLevel
      std::string objtype;
      int32_t instid;
      // component data
      std::string compname;
      int32_t compinstid;
      void clear();
      void print();
    };
  public:
    ObjectHeader()=delete;
    ObjectHeader(Reader& _reader);
    ObjectHeader(const ObjectHeader&)=default;
    virtual ~ObjectHeader();

    inline bool isComponent() const {return c_objtype==0;};
    inline bool isEntity() const {return c_objtype==1;};
    inline std::string name() const {return c_name;};
    inline std::string proptype() const {return c_proptype;};
    inline std::string instance() const {return c_instance;};
    inline int32_t instanceid() const {return c_instanceid;};
    inline std::string className() const {return c_classname;};
    inline std::string componentName() const {return c_component_name;};
    inline int32_t componentInstanceid() const {return c_component_instanceid;};

    virtual void deserializeProperties(Reader &_reader);
    virtual void deserializeSupplementalData(Reader &_reader) {};
    virtual std::string str() const;
    std::string str_compbase() const;

  private:
    static bool parse_inststr(const std::string& _str, bool _entity, ObjectHeader::instdata& _data);
    //static bool parse_inststr(const std::string& _str, bool _entity, instdata& _data);
    virtual void deserialize(Reader& _reader);

  protected:
    void deserializeCompDefs(Reader& _reader);
    std::list<ObjectReference>& getCompDefs() {return c_compdefs;};

  protected:
    int32_t c_objtype;
    std::string c_name, c_proptype, c_instance;
    int32_t c_instanceid, c_component_instanceid;
    std::string c_classname;
    std::string c_component_name;

    ObjectReference c_basecomp;
    std::list<ObjectReference> c_compdefs;
  };
  typedef std::shared_ptr<ObjectHeader> ObjectHeaderSP;

}

#endif
