compile:
	g++ BankSimulation.cpp

run:
	./a.out

clean:
	rm a.out

test:
	make compile
	make run
	cat outFile.txt
