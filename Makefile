INCPATH=-I/usr/local/include
CXXFLAGS=-Werror -pedantic -std=c++17 -Wno-c11-extensions $(INCPATH)
LDFLAGS=-L/usr/local/lib -pthread -lboost_program_options -lz

OBJS=main.o Loader.o Exception.o Timer.o
OUT=../bin/sfticks

.if defined(DEBUG)
CXXFLAGS+= -O0 -glldb
.else
CXXFLAGS+= -O2
.endif

.SUFFIXES : .o .cc .hh
.OBJDIR   : obj/
.PATH.cc  : $(.CURDIR)/src/
.PATH.hh  : $(.CURDIR)/src/

.PHONY = clean sfticks depend .depend

sfticks: .depend $(OUT)

depend: .depend

.depend: ../Makefile
	mkdep $(INCPATH) ../src/*.cc ../src/*.hh

clean:
	rm -f .depend $(OUT) $(OBJS)
	rm -f ../src/*~

$(OUT): $(OBJS)
	$(CXX) -o $@ $(.ALLSRC) $(LDFLAGS)

.cc.o:
	$(CXX) -c -pipe -o $@ $< $(CXXFLAGS)

.sinclude ".depend"
