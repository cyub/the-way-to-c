build: clean-build
	cmake -DDEFAULT_PORT=8099 -S . -B build
	cmake --build build

clean-build:
	rm -rf build

format:
	find . -maxdepth 2 -type f \( -name "*.c" -o -name "*.h" \) -print0 | xargs -0 clang-format -style=file -i
