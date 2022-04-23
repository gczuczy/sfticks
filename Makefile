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
	FGConveyorBeltMk5.o FGConveyorLiftMk1.o FGConveyorLiftMk2.o FGConveyorLiftMk3.o FGConveyorLiftMk4.o \
	FGConveyorLiftMk5.o FGConveyorBeltLogic.o FGConveyorAttachmentMerger.o FGConveyorAttachmentSplitter.o \
	FGConveyorAttachmentSplitterSmart.o FGIOUnit.o FGAssemblerMk1.o FGBlender.o FGConstructorMk1.o FGFoundryMk1.o \
	FGHadronCollider.o FGManufacturerMk1.o FGOilRefinery.o FGPackager.o FGSmelterMk1.o FGGeneratorCoal.o FGGeneratorFuel.o \
	FGGeneratorNuclear.o FGResourceSink.o FGSpaceElevator.o FGStorageUnit.o FGDroneStation.o FGStorageContainerMk1.o \
	FGStorageContainerMk2.o FGTrainDockingStation.o FGGeneratorUnit.o PropertyInterface.o FloatProperty.o ObjectReference.o \
	ObjectProperty.o BoolProperty.o StructProperty.o GenericStruct.o IntProperty.o EnumProperty.o GenericArrayProperty.o \
	FGConveyorLift.o SortRule.o SaveProperties.o ByteProperty.o FGFactoryConnectionComponent.o FGInventoryComponent.o \
	SplinePointData.o FGEnums.o FGMiner.o FGMinerMk1.o FGMinerMk2.o FGMinerMk3.o FGObjectLibrary.o FGObjectDictionary.o \
	FGPowerInfoComponent.o FGDocsJSON.o FGBaseObject.o FGJSONObject.o FGDescObject.o FGRecipeObject.o tests.o

OBJS_ZL=zltest.o Timer.o Exception.o
OUT=../bin/sfticks
OUT_ZL=../bin/zltest

.if defined(DEBUG)
CXXFLAGS+= -O0 -DSFT_DEBUG -ferror-limit=2 -glldb
.else
CXXFLAGS+= -O2
.endif

.SUFFIXES : .o .cc .hh
.OBJDIR   : obj/
.PATH.cc  : $(.CURDIR)/src/
.PATH.hh  : $(.CURDIR)/src/

.PHONY = clean sfticks depend .depend

# $(OUT_ZL)
sfticks: .depend $(OUT)

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
