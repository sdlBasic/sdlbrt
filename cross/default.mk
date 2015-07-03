
OSMKLIST := $(wildcard cross/*.mk)

OSLIST := $(OSMKLIST:cross/%.mk=%)
OSLIST := $(OSLIST:default=)

default:
	@echo 
	@echo "Please specifiy cross target ( make -f cross/makefile OS=crosstarget )"
	@echo 
	@echo cross targets available: 
	@echo 
	@for os in $(OSLIST); do echo $$os; done
