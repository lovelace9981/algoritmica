buildBF:
	@echo "Building Brute Force program..."
	g++ -o BFmain.bin main.cpp

buildBFineficiente:
	@echo "Building Inefficient Brute Force program..."
	g++ -o BFmainIneficiente.bin main_ineficiente.cpp

buildDP:
	@echo "Building Dynamic Programming program..."
	g++ -o DPmain.bin mainPD.cpp

build: buildBF buildDP buildBFineficiente

clean: 
	@echo "Removing .bin files..."
	rm *.bin

BFrunInefficient: buildBFineficiente
	@echo "Running Inefficient Brute Force program for pruebaPapel.stocks with 10 budget..."
	./BFmainIneficiente.bin 10 pruebaPapel.stocks

BFrun: buildBF
	@echo "Running Brute Force program for pruebaPapel.stocks with 10 budget..."
	./BFmain.bin 10 pruebaPapel.stocks

DPrun: buildDP
	@echo "Running Dynamic Programming program for pruebaPapel.stocks with 10 budget..."
	./DPmain.bin 10 pruebaPapel.stocks

debugDP:
	@echo "Building DPmain for debugging..."
	g++ -g -o DPmain.bin mainPD.cpp