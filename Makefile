INCPATH=-I/usr/local/include
CXXFLAGS=-Werror -pedantic -std=c++20 -Wno-c11-extensions $(INCPATH)
LDFLAGS=-L/usr/local/lib -pthread -lboost_program_options -lz

OBJS=main.o Loader.o Exception.o Timer.o SaveObject.o SaveEntity.o vectors.o SaveComponent.o \
	SaveWorld.o Reader.o ObjectReference.o Trace.o SaveProperty.o IntProperty.o \
	ObjectProperty.o ArrayProperty.o InterfaceProperty.o StrProperty.o StructProperty.o \
	EnumProperty.o FloatProperty.o BoolProperty.o TextProperty.o NameProperty.o ByteProperty.o \
	Int64Property.o MapProperty.o
OBJS_ZL=zltest.o Timer.o Exception.o
OUT=../bin/sfticks
OUT_ZL=../bin/zltest

.if defined(DEBUG)
CXXFLAGS+= -O0 -DSFT_DEBUG -ferror-limit=1
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
