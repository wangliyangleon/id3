#XMAKE edit-mode: -*- Makefile -*-
####################64Bit Mode####################
ifeq ($(shell uname -m),x86_64)
.PHONY:all
all:xmake_makefile_check id3 libid3.a test 
	@echo "[[1;32;40mXMAKE:BUILD[0m][Target:'[1;32;40mall[0m']"
	@echo "make all done"

.PHONY:xmake_makefile_check
xmake_makefile_check:
	@echo "[[1;32;40mXMAKE:BUILD[0m][Target:'[1;32;40mxmake_makefile_check[0m']"
	@if [ "XMAKE" -nt "Makefile" ] ; then echo "[ERROR]PLEASE UPDATE 'Makefile' BY 'xmake'" ; exit 250 ;  fi

.PHONY:clean
clean:
	@echo "[[1;32;40mXMAKE:BUILD[0m][Target:'[1;32;40mclean[0m']"
	rm -rf id3
	rm -rf ./output/bin/id3
	rm -rf libid3.a
	rm -rf ./output/lib/libid3.a
	$(MAKE) -C test clean
	rm -rf src/id3_id3_util.o
	rm -rf src/id3_id3_gdata.o
	rm -rf src/id3_id3.o
	rm -rf src/id3_main.o

.PHONY:dist
dist:clean
	@echo "[[1;32;40mXMAKE:BUILD[0m][Target:'[1;32;40mdist[0m']"
	cd ..;tar czvf id3.tar.gz id3;cd id3

id3:src/id3_id3_util.o \
  src/id3_id3_gdata.o \
  src/id3_id3.o \
  src/id3_main.o
	@echo "[[1;32;40mXMAKE:BUILD[0m][Target:'[1;32;40mid3[0m']"
	g++ src/id3_id3_util.o \
  src/id3_id3_gdata.o \
  src/id3_id3.o \
  src/id3_main.o -Xlinker "-("  thirdparty/gtest/lib/libgtest.a  -Xlinker "-)" -o id3
	mkdir -p ./output/bin
	cp -f --link id3 ./output/bin

libid3.a:src/id3_id3_util.o \
  src/id3_id3_gdata.o \
  src/id3_id3.o \
  src/id3_main.o
	@echo "[[1;32;40mXMAKE:BUILD[0m][Target:'[1;32;40mlibid3.a[0m']"
	ar crs libid3.a src/id3_id3_util.o \
  src/id3_id3_gdata.o \
  src/id3_id3.o \
  src/id3_main.o
	mkdir -p ./output/lib
	cp -f --link libid3.a ./output/lib

.PHONY:test
test:libid3.a
	@echo "[[1;32;40mXMAKE:BUILD[0m][Target:'[1;32;40mtest[0m']"
	@echo "[[1;32;40mXMAKE:BUILD[0m][Entering directory:'[1;32;40mtest[0m']"
	$(MAKE) -C test
	@echo "[[1;32;40mXMAKE:BUILD[0m][Leaving directory:'[1;32;40mtest[0m']"

src/id3_id3_util.o:src/id3_util.cpp \
  src/id3_util.cpp \
  include/id3_util.h \
  include/id3_def.h
	@echo "[[1;32;40mXMAKE:BUILD[0m][Target:'[1;32;40msrc/id3_id3_util.o[0m']"
	g++ -c -I. \
  -I./include \
  -I./output \
  -I./output/include \
  -I./Query \
  -I./Business \
  -I./AdInfo \
  -I./StarAdInfo -Ithirdparty/gtest \
  -Ithirdparty/gtest/include \
  -Ithirdparty/gtest/output \
  -Ithirdparty/gtest/output/include -D_GNU_SOURCE \
  -D__STDC_LIMIT_MACROS \
  -DVERSION=\"1.0.1.0\" \
  -DNDEBUG \
  -DNDEMO \
  -D__64BIT__ \
  -D_FILE_OFFSET_BITS=64 -g \
  -pipe \
  -W \
  -Wall \
  -fPIC \
  -O2 \
  -Wpointer-arith \
  -Wconversion \
  -rdynamic \
  -Wno-invalid-offsetof \
  -fstrict-aliasing  -o src/id3_id3_util.o src/id3_util.cpp

src/id3_id3_gdata.o:src/id3_gdata.cpp \
  src/id3_gdata.cpp \
  include/id3_gdata.h \
  include/id3_def.h \
  include/id3_util.h
	@echo "[[1;32;40mXMAKE:BUILD[0m][Target:'[1;32;40msrc/id3_id3_gdata.o[0m']"
	g++ -c -I. \
  -I./include \
  -I./output \
  -I./output/include \
  -I./Query \
  -I./Business \
  -I./AdInfo \
  -I./StarAdInfo -Ithirdparty/gtest \
  -Ithirdparty/gtest/include \
  -Ithirdparty/gtest/output \
  -Ithirdparty/gtest/output/include -D_GNU_SOURCE \
  -D__STDC_LIMIT_MACROS \
  -DVERSION=\"1.0.1.0\" \
  -DNDEBUG \
  -DNDEMO \
  -D__64BIT__ \
  -D_FILE_OFFSET_BITS=64 -g \
  -pipe \
  -W \
  -Wall \
  -fPIC \
  -O2 \
  -Wpointer-arith \
  -Wconversion \
  -rdynamic \
  -Wno-invalid-offsetof \
  -fstrict-aliasing  -o src/id3_id3_gdata.o src/id3_gdata.cpp

src/id3_id3.o:src/id3.cpp \
  src/id3.cpp \
  include/id3.h \
  include/id3_def.h \
  include/id3_gdata.h \
  include/id3_util.h
	@echo "[[1;32;40mXMAKE:BUILD[0m][Target:'[1;32;40msrc/id3_id3.o[0m']"
	g++ -c -I. \
  -I./include \
  -I./output \
  -I./output/include \
  -I./Query \
  -I./Business \
  -I./AdInfo \
  -I./StarAdInfo -Ithirdparty/gtest \
  -Ithirdparty/gtest/include \
  -Ithirdparty/gtest/output \
  -Ithirdparty/gtest/output/include -D_GNU_SOURCE \
  -D__STDC_LIMIT_MACROS \
  -DVERSION=\"1.0.1.0\" \
  -DNDEBUG \
  -DNDEMO \
  -D__64BIT__ \
  -D_FILE_OFFSET_BITS=64 -g \
  -pipe \
  -W \
  -Wall \
  -fPIC \
  -O2 \
  -Wpointer-arith \
  -Wconversion \
  -rdynamic \
  -Wno-invalid-offsetof \
  -fstrict-aliasing  -o src/id3_id3.o src/id3.cpp

src/id3_main.o:src/main.cpp \
  src/main.cpp \
  include/id3.h \
  include/id3_def.h \
  include/id3_gdata.h \
  include/id3_util.h
	@echo "[[1;32;40mXMAKE:BUILD[0m][Target:'[1;32;40msrc/id3_main.o[0m']"
	g++ -c -I. \
  -I./include \
  -I./output \
  -I./output/include \
  -I./Query \
  -I./Business \
  -I./AdInfo \
  -I./StarAdInfo -Ithirdparty/gtest \
  -Ithirdparty/gtest/include \
  -Ithirdparty/gtest/output \
  -Ithirdparty/gtest/output/include -D_GNU_SOURCE \
  -D__STDC_LIMIT_MACROS \
  -DVERSION=\"1.0.1.0\" \
  -DNDEBUG \
  -DNDEMO \
  -D__64BIT__ \
  -D_FILE_OFFSET_BITS=64 -g \
  -pipe \
  -W \
  -Wall \
  -fPIC \
  -O2 \
  -Wpointer-arith \
  -Wconversion \
  -rdynamic \
  -Wno-invalid-offsetof \
  -fstrict-aliasing  -o src/id3_main.o src/main.cpp

endif #ifeq ($(shell uname -m),x86_64)


