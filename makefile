all: release

prepare:
	mkdir -p obj
	gcc -c src/rmnewline.c -o obj/rmnewline.o -std=c99
	gcc -c src/haversine.c -o obj/haversine.o -lm -std=c99


debug: prepare src/main.c src/rmnewline.h src/haversine.h
	mkdir -p out
	gcc src/main.c obj/haversine.o obj/rmnewline.o -o out/dist -std=c99 -lm -D DEBUG

release: prepare src/main.c src/rmnewline.h src/haversine.h
	mkdir -p out
	gcc src/main.c obj/haversine.o obj/rmnewline.o -o out/dist -std=c99 -lm -D RELEASE

test: release
	out/dist -i route1.txt
	out/dist -i route2.txt
	out/dist -i huge_route.txt
	echo "Built and tested successfully"

clean:
	rm -r out
	rm -r obj