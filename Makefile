
CC=g++
CFLAGS=-w
OUT=dist/out
HEADERS=src/headers
INCLUDE=src/include/

main: src/main.cpp
	$(CC) src/main.cpp $(INCLUDE)Camera.cpp $(INCLUDE)utils.cpp $(CFLAGS) -o $(OUT) -I$(HEADERS)

clean:
	rm -f $(OUT)

run:
	$(OUT) $(PARAM)
