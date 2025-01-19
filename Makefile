jupyter-book = jupyter-book
build_dir = _build

build: clean
	$(jupyter-book) build .

clean:
	rm -rf $(build_dir)