all:
	@echo "make: Entering directory 'cpp11test/src'"
	@Rscript -e 'devtools::load_all("cpp11test")'
	@echo "make: Leaving directory 'cpp11test/src'"

test: all
	@echo "make: Entering directory 'cpp11test/tests/testthat'"
	@Rscript -e 'devtools::test("cpp11test")'
	@echo "make: Leaving directory 'cpp11test/tests/testthat'"

clean:
	@Rscript -e 'devtools::clean_dll()'

clang_format=`which clang-format`
format: $(shell find . -name '*.hpp') $(shell find . -name '*.cpp')
ifeq ($(findstring version 10,$(shell ${clang_format} --version 2>/dev/null)),)
	@echo "clang-format 10 is required"
else
	@${clang_format} -i $?
endif
