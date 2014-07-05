#XMAKE edit-mode: -*- Makefile -*-
####################64Bit Mode####################
ifeq ($(shell uname -m),x86_64)
.PHONY:all
all:test_id3 test_util test_gdata 
	@echo "[[1;32;40mXMAKE:BUILD[0m][Target:'[1;32;40mall[0m']"
	@echo "make all done"

.PHONY:clean
clean:
	@echo "[[1;32;40mXMAKE:BUILD[0m][Target:'[1;32;40mclean[0m']"
	rm -rf test_id3
	rm -rf ./output/bin/test_id3
	rm -rf test_util
	rm -rf ./output/bin/test_util
	rm -rf test_gdata
	rm -rf ./output/bin/test_gdata
	rm -rf src/test_id3_test_id3.o
	rm -rf src/test_util_test_util.o
	rm -rf src/test_gdata_test_gdata.o

.PHONY:dist
dist:clean
	@echo "[[1;32;40mXMAKE:BUILD[0m][Target:'[1;32;40mdist[0m']"
	cd ..;tar czvf test.tar.gz test;cd test

test_id3:src/test_id3_test_id3.o \
  ../libid3.a
	@echo "[[1;32;40mXMAKE:BUILD[0m][Target:'[1;32;40mtest_id3[0m']"
	g++ src/test_id3_test_id3.o ../libid3.a ../thirdparty/gtest/lib/libgtest.a -lpthread \
  -lcrypto \
  -lm \
  -lssl -o test_id3
	mkdir -p ./output/bin
	cp -f test_id3 ./output/bin

test_util:src/test_util_test_util.o \
  ../libid3.a
	@echo "[[1;32;40mXMAKE:BUILD[0m][Target:'[1;32;40mtest_util[0m']"
	g++ src/test_util_test_util.o ../libid3.a ../thirdparty/gtest/lib/libgtest.a -lpthread \
  -lcrypto \
  -lm \
  -lssl -o test_util
	mkdir -p ./output/bin
	cp -f test_util ./output/bin

test_gdata:src/test_gdata_test_gdata.o \
  ../libid3.a
	@echo "[[1;32;40mXMAKE:BUILD[0m][Target:'[1;32;40mtest_gdata[0m']"
	g++ src/test_gdata_test_gdata.o ../libid3.a ../thirdparty/gtest/lib/libgtest.a -lpthread \
  -lcrypto \
  -lm \
  -lssl -o test_gdata
	mkdir -p ./output/bin
	cp -f test_gdata ./output/bin

src/test_id3_test_id3.o:src/test_id3.cpp \
  src/test_id3.cpp
	@echo "[[1;32;40mXMAKE:BUILD[0m][Target:'[1;32;40msrc/test_id3_test_id3.o[0m']"
	g++ -c -I./ \
  -I./include \
  -I../include -I../thirdparty/gtest \
  -I../thirdparty/gtest/include \
  -I../thirdparty/gtest/output \
  -I../thirdparty/gtest/output/include  -g \
  -pipe \
  -std=c++11 \
  -W \
  -Wall \
  -fPIC \
  -Wpointer-arith \
  -Wconversion \
  -Wno-invalid-offsetof \
  -fstrict-aliasing \
  -D_FILE_OFFSET_BITS=64  -o src/test_id3_test_id3.o src/test_id3.cpp

src/test_util_test_util.o:src/test_util.cpp \
  src/test_util.cpp
	@echo "[[1;32;40mXMAKE:BUILD[0m][Target:'[1;32;40msrc/test_util_test_util.o[0m']"
	g++ -c -I./ \
  -I./include \
  -I../include -I../thirdparty/gtest \
  -I../thirdparty/gtest/include \
  -I../thirdparty/gtest/output \
  -I../thirdparty/gtest/output/include  -g \
  -pipe \
  -std=c++11 \
  -W \
  -Wall \
  -fPIC \
  -Wpointer-arith \
  -Wconversion \
  -Wno-invalid-offsetof \
  -fstrict-aliasing \
  -D_FILE_OFFSET_BITS=64  -o src/test_util_test_util.o src/test_util.cpp

src/test_gdata_test_gdata.o:src/test_gdata.cpp \
  src/test_gdata.cpp
	@echo "[[1;32;40mXMAKE:BUILD[0m][Target:'[1;32;40msrc/test_gdata_test_gdata.o[0m']"
	g++ -c -I./ \
  -I./include \
  -I../include -I../thirdparty/gtest \
  -I../thirdparty/gtest/include \
  -I../thirdparty/gtest/output \
  -I../thirdparty/gtest/output/include  -g \
  -pipe \
  -std=c++11 \
  -W \
  -Wall \
  -fPIC \
  -Wpointer-arith \
  -Wconversion \
  -Wno-invalid-offsetof \
  -fstrict-aliasing \
  -D_FILE_OFFSET_BITS=64  -o src/test_gdata_test_gdata.o src/test_gdata.cpp

endif #ifeq ($(shell uname -m),x86_64)


