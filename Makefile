build_release:
	mkdir -p build_release_ && cd build_release_ && cmake -DCMAKE_BUILD_TYPE=Release .. && cmake --build . -j 12

build_debug:
	mkdir -p build_debug_ && cd build_debug_ && cmake -DCMAKE_BUILD_TYPE=Debug .. && cmake --build . -j 12

.PHONY: clean
clean:
	rm build_debug_/cv_tricks_vulkan -f
	rm build_release_/cv_tricks_bulkan -f

run_release: build_release
	./build_release_/cv_tricks_vulkan

run_debug: build_debug
	./build_debug_/cv_tricks_vulkan