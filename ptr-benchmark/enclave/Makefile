# Copyright (c) Open Enclave SDK contributors.
# Licensed under the MIT License.

include ../../config.mk

CRYPTO_LDFLAGS := $(shell pkg-config oeenclave-$(CXX_COMPILER) --variable=${OE_CRYPTO_LIB}libs)

ifeq ($(LVI_MITIGATION), ControlFlow)
    ifeq ($(LVI_MITIGATION_BINDIR),)
        $(error LVI_MITIGATION_BINDIR is not set)
    endif
    # Only run once.
    ifeq (,$(findstring $(LVI_MITIGATION_BINDIR),$(CXX)))
        CXX := $(LVI_MITIGATION_BINDIR)/$(CXX)
    endif
    CXX_COMPILER := $(CXX_COMPILER)-lvi-cfg
    CRYPTO_LDFLAGS := $(shell pkg-config oeenclave-$(CXX_COMPILER) --variable=${OE_CRYPTO_LIB}libslvicfg)
endif

ifeq ($(OE_CRYPTO_LIB),openssl_3)
  CXX_FLAGS=$(shell pkg-config oeenclave-$(CXX_COMPILER) --variable=${OE_CRYPTO_LIB}flags)
else
  CXX_FLAGS=$(shell pkg-config oeenclave-$(CXX_COMPILER) --cflags)
endif
LDFLAGS=$(shell pkg-config oeenclave-$(CXX_COMPILER) --libs)
INCDIR=$(shell pkg-config oeenclave-$(CXX_COMPILER) --variable=includedir)

all:
	$(MAKE) build
	$(MAKE) keys
	$(MAKE) sign

build:
	@ echo "Compilers used: $(C), $(CXX)"
	oeedger8r ../helloworld.edl --trusted \
		--search-path $(INCDIR) \
		--search-path $(INCDIR)/openenclave/edl/sgx
	$(CXX) -g -c $(CXX_FLAGS) -DOE_API_VERSION=2 enc.cpp -o enc.o
	$(CXX) -g -c $(CXX_FLAGS) -DOE_API_VERSION=2 helloworld_t.c -o helloworld_t.o
	$(CXX) -o enclave helloworld_t.o enc.o $(LDFLAGS) $(CRYPTO_LDFLAGS)

sign:
	oesign sign -e enclave -c helloworld.conf -k private.pem

clean:
	rm -f enc.o enclave enclave.signed private.pem public.pem helloworld_t.o helloworld_t.h helloworld_t.c helloworld_args.h

keys:
	openssl genrsa -out private.pem -3 3072
	openssl rsa -in private.pem -pubout -out public.pem
