build:
	g++ main.cc -o boggle-exe
build-debug:
	g++ -g main.cc -o boggle-exe
clean:
	rm -f boggle-exe
test:
	./boggle-exe
debug:
	gdb ./boggle-exe