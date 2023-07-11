# Copyright (c) Open Enclave SDK contributors.
# Licensed under the MIT License.

include ../config.mk

.PHONY: all build clean run simulate nonoe nonoe-run

OE_CRYPTO_LIB := mbedtls
export OE_CRYPTO_LIB

CXXFLAGS=$(shell pkg-config oehost-$(CXX_COMPILER) --cflags)
LDFLAGS=$(shell pkg-config oehost-$(CXX_COMPILER) --libs)


all: build

build:
	$(MAKE) -C enclave
	$(MAKE) -C host

clean:
	$(MAKE) -C enclave clean
	$(MAKE) -C host clean
	rm nonoe

run:
	host/helloworld_host ./enclave/enclave.signed

simulate:
	host/helloworld_host ./enclave/enclave.signed --simulate

# -g -m64 -fPIE -ftls-model=local-exec -fvisibility=hidden -fstack-protector-strong -fno-omit-frame-pointer -ffunction-sections -fdata-sections -mllvm -x86-speculative-load-hardening non-oe-kernel.cpp


nonoe:
	@echo "START"
	@echo ${CXX_FLAGS}
	$(CXX) $(CXXFLAGS) non-oe-kernel.cpp -o nonoe $(LDFLAGS)
	

nonoe-run:
	./nonoe

