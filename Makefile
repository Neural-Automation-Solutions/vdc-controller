
CC=g++
CFLAGS=-w
OUT=dist/vdc-main
HEADERS=src/headers
INCLUDE=src/include/

main: src/main.cpp
	$(CC) src/main.cpp \
		$(INCLUDE)Camera.cpp \
		$(INCLUDE)utils.cpp \
		$(INCLUDE)LED.cpp \
		$(INCLUDE)Switch.cpp \
		$(CFLAGS) -o $(OUT) -I$(HEADERS) -lpigpio

clean:
	rm -f $(OUT)

run:
	$(OUT) $(PARAM)
