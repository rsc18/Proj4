CC= g++
CFLAGS=	-std=c++11 
OUT=    output

all:	$(OUT)

output: main.cpp
	$(CC) $(CFLAGS) main.cpp -o output

clean:
	rm $(OUT)

