all: build_lib build_funcional build_unit

build_lib:
	mkdir -p bin
	g++ -fPIC -shared -DBUILD_DLL src/*.cpp -I./src -o bin/libmodel.so

build_funcional:
	g++ test/funcional/*.cpp -I./src -L./bin -lmodel -o bin/funcional_tests

build_unit:
	g++ test/unit/*.cpp -I./src -L./bin -lmodel -o bin/unit_tests 

run_funcional:
	LD_LIBRARY_PATH=./bin ./bin/funcional_tests

run_unit:
	LD_LIBRARY_PATH=./bin ./bin/unit_tests

clean:
	rm -rf bin/