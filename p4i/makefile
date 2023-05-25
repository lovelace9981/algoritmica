buildBF:
	@echo "Building Brute Force program..."
	g++ -o mainBF.bin main.cpp

buildDP:
	@echo "Building Dynamic Programming program..."
	g++ -o mainDP.bin mainPD.cpp

clean: 
	@echo "Removing .bin files..."
	rm *.bin

runBF: buildBF
	@echo "Running Brute Force program for pruebaPapel.stocks with 10 budget..."
	./mainBF.bin 10 pruebaPapel.stocks

runDP: buildDP
	@echo "Running Dynamic Programming program for pruebaPapel.stocks with 10 budget..."
	./mainDP.bin 10 pruebaPapel.stocks