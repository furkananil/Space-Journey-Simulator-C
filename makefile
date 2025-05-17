all: compile run

compile:
	gcc -I ./include/ -o ./lib/Kisi.o -c ./src/Kisi.c
	gcc -I ./include/ -o ./lib/Gezegen.o -c ./src/Gezegen.c
	gcc -I ./include/ -o ./lib/BuzDeviGezegen.o -c ./src/BuzDeviGezegen.c
	gcc -I ./include/ -o ./lib/KayacGezegen.o -c ./src/KayacGezegen.c
	gcc -I ./include/ -o ./lib/CuceGezegen.o -c ./src/CuceGezegen.c
	gcc -I ./include/ -o ./lib/GazDeviGezegen.o -c ./src/GazDeviGezegen.c
	gcc -I ./include/ -o ./lib/DosyaOkuma.o -c ./src/DosyaOkuma.c
	gcc -I ./include/ -o ./lib/Zaman.o -c ./src/Zaman.c
	gcc -I ./include/ -o ./lib/Simulasyon.o -c ./src/Simulasyon.c
	gcc -I ./include/ -o ./lib/UzayAraci.o -c ./src/UzayAraci.c
	gcc -I ./include/ -o ./bin/App ./lib/Kisi.o ./lib/Gezegen.o ./lib/UzayAraci.o ./lib/BuzDeviGezegen.o ./lib/KayacGezegen.o ./lib/CuceGezegen.o ./lib/GazDeviGezegen.o ./lib/DosyaOkuma.o ./lib/Zaman.o ./lib/Simulasyon.o ./src/main.c

run:
	./bin/App