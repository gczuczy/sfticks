INCPATH=-I/usr/local/include
CXXFLAGS=-Werror -pedantic -std=c++20 -Wno-c11-extensions $(INCPATH)
LDFLAGS=-L/usr/local/lib -pthread -lboost_program_options -lz

PROPERTY_OBJS=SaveProperty.o IntProperty.o \
	ObjectProperty.o ArrayProperty.o InterfaceProperty.o StrProperty.o StructProperty.o \
	EnumProperty.o FloatProperty.o BoolProperty.o TextProperty.o NameProperty.o ByteProperty.o \
	Int64Property.o MapProperty.o SaveWorld.o SaveComponent.o SaveObject.o SaveEntity.o ObjectReference.o

OBJS=main.o Loader.o Exception.o Timer.o vectors.o Reader.o Trace.o Saveable.o World.o SavePropertyType.o \
	FGObjectHeader.o misc.o FGEntity.o FGGenericEntity.o FGComponent.o FGGenericComponent.o FGBuilding.o \
	FGConveyorBelt.o FGConveyorBeltMk1.o FGConveyorBeltMk2.o FGConveyorBeltMk3.o FGConveyorBeltMk4.o \
	FGConveyorBeltMk5.o
OBJS_ZL=zltest.o Timer.o Exception.o
OUT=../bin/sfticks
OUT_ZL=../bin/zltest

.if defined(DEBUG)
CXXFLAGS+= -O0 -DSFT_DEBUG -ferror-limit=2
.else
CXXFLAGS+= -O2
.endif

.SUFFIXES : .o .cc .hh
.OBJDIR   : obj/
.PATH.cc  : $(.CURDIR)/src/
.PATH.hh  : $(.CURDIR)/src/

.PHONY = clean sfticks depend .depend

sfticks: .depend $(OUT) $(OUT_ZL)

depend: .depend

.depend: ../Makefile
	mkdep $(INCPATH) ../src/*.cc ../src/*.hh

clean:
	rm -f .depend $(OUT) $(OUT_ZL) $(OBJS) $(OBJS_ZL)
	rm -f ../src/*~

$(OUT): $(OBJS)
	$(CXX) -o $@ $(.ALLSRC) $(LDFLAGS)

$(OUT_ZL): $(OBJS_ZL)
	$(CXX) -o $@ $(.ALLSRC) $(LDFLAGS)

.cc.o:
	$(CXX) -c -pipe -o $@ $< $(CXXFLAGS)

.sinclude ".depend"
