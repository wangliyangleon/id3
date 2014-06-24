id3:src/id3_id3_gdata.o \
  src/id3_id3.o \
  src/id3_id3_util.o \
  src/id3_main.o
	@echo "[[1;32;40mXMAKE:BUILD[0m][Target:'[1;32;40mid3[0m']"
	g++ src/id3_id3_gdata.o \
  src/id3_id3.o \
  src/id3_id3_util.o \
  src/id3_main.o -Xlinker "-("    -Xlinker "-)" -o id3
	mkdir -p ./output/bin
	cp -f --link id3 ./output/bin

src/id3_id3_gdata.o:src/id3_gdata.cpp \
  src/id3_gdata.cpp \
  include/id3_gdata.h \
  include/id3_def.h \
  include/id3_util.h
	@echo "[[1;32;40mXMAKE:BUILD[0m][Target:'[1;32;40msrc/id3_id3_gdata.o[0m']"
	g++ -c -I. \
  -I./include   -g \
  -pipe \
  -W \
  -Wall \
  -fPIC \
  -O2  -o src/id3_id3_gdata.o src/id3_gdata.cpp

src/id3_id3.o:src/id3.cpp \
  src/id3.cpp \
  include/id3.h \
  include/id3_def.h \
  include/id3_gdata.h \
  include/id3_util.h
	@echo "[[1;32;40mXMAKE:BUILD[0m][Target:'[1;32;40msrc/id3_id3.o[0m']"
	g++ -c -I. \
  -I./include   -g \
  -pipe \
  -W \
  -Wall \
  -fPIC \
  -O2  -o src/id3_id3.o src/id3.cpp

src/id3_id3_util.o:src/id3_util.cpp \
  src/id3_util.cpp \
  include/id3_util.h \
  include/id3_def.h
	@echo "[[1;32;40mXMAKE:BUILD[0m][Target:'[1;32;40msrc/id3_id3_util.o[0m']"
	g++ -c -I. \
  -I./include   -g \
  -pipe \
  -W \
  -Wall \
  -fPIC \
  -O2  -o src/id3_id3_util.o src/id3_util.cpp

src/id3_main.o:src/main.cpp \
  src/main.cpp \
  include/id3.h \
  include/id3_def.h \
  include/id3_gdata.h \
  include/id3_util.h
	@echo "[[1;32;40mXMAKE:BUILD[0m][Target:'[1;32;40msrc/id3_main.o[0m']"
	g++ -c -I. \
  -I./include   -g \
  -pipe \
  -W \
  -Wall \
  -fPIC \
  -O2  -o src/id3_main.o src/main.cpp

libid3.a:src/id3_id3_gdata.o \
  src/id3_id3.o \
  src/id3_id3_util.o \
  src/id3_main.o
	@echo "[[1;32;40mXMAKE:BUILD[0m][Target:'[1;32;40mlibid3.a[0m']"
	ar crs libid3.a src/id3_id3_gdata.o \
  src/id3_id3.o \
  src/id3_id3_util.o 
	mkdir -p ./output/lib
	cp -f --link libid3.a ./output/lib



clean:
	rm -rf libid3.a
	rm -rf ./output/lib/libid3.a
	rm -rf id3
	rm -rf ./output/bin/id3
	rm -rf src/id3_id3_gdata.o
	rm -rf src/id3_id3.o
	rm -rf src/id3_id3_util.o
	rm -rf src/id3_main.o
