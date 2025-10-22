build:
	mkdir -p build_ && cd build_ && cmake .. && cmake --build .

.PHONY: clean
clean:
	rm build_/cv_tricks_vulkan -f

test: build
	./build_/cv_tricks_vulkan