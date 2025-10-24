build_release:
	mkdir -p build_ && cd build_ && cmake -DCMAKE_BUILD_TYPE=Release .. && cmake --build .

build_test:
	mkdir -p build_ && cd build_ && cmake -DCMAKE_BUILD_TYPE=Debug .. && cmake --build .

.PHONY: clean
clean:
	rm build_/cv_tricks_vulkan -f

run_release: build_release
	./build_/cv_tricks_vulkan

run_test: build_test
	./build_/cv_tricks_vulkan