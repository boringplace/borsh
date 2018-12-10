.PHONY: run clean

all: Cargo.toml
	@msgfmt i18n/ru.po -o ru.mo
	@cargo build

run:
	@cargo run

clean:
	@cargo clean
	@git clean -fdx

