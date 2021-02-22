all: build-sample

rebuild: rebuild-sample

distclean: distclean-sample

build-sample:
	@$(MAKE) -C sample

rebuild-sample:
	@$(MAKE) -C sample rebuild

distclean-sample:
	@$(MAKE) -C sample distclean

clean:
	@$(MAKE) -C sample clean

copy:
	cp /y .\bin\EBOOT.PBP F:\PSP\GAME\csdlibrary

explorer:
	explorer /e, F:\PSP\GAME\csdlibrary

