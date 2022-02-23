INCPATH=-I/usr/local/include
CXXFLAGS=-Werror -pedantic -std=c++17 -Wno-c11-extensions $(INCPATH)
LDFLAGS=-L/usr/local/lib -pthread -lboost_program_options -lz

OBJS=main.o Loader.o Exception.o Timer.o SaveObject.o SaveEntity.o vectors.o SaveComponent.o \
	SaveWorld.o Reader.o ObjectReference.o SaveProperties.o
OBJS_ZL=zltest.o Timer.o Exception.o
OUT=../bin/sfticks
OUT_ZL=../bin/zltest

.if defined(DEBUG)
CXXFLAGS+= -O0 -DSFT_DEBUG
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
