
DEBUG	:=	0

CXX	:= g++
LD	:= g++

CXXFLAGS	:= -std=c++11 -Wall -Wextra -pedantic -fno-rtti -fno-exceptions
LIBS		:= -lglew32 -lGLFW/glfw3 -lopengl32

ifeq (1, $(DEBUG))
	CXXFLAGS := $(CXXFLAGS) -g -O0 -D_DEBUG
else
	CXXFLAGS := $(CXXFLAGS) -O3 -fomit-frame-pointer
endif

ifeq ($(OS),Windows_NT)
	TARGET	:= $(shell basename $(CURDIR)).exe
else
	TARGET	:= $(shell basename $(CURDIR))
endif
OUTPUT		:= $(CURDIR)/$(TARGET)
SOURCES		:= src
INCLUDES	:= include

CXXFILES	:= $(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.cpp)))
OFILES		:= $(CXXFILES:.cpp=.o)
PRECOMPILED	:= include/Precompiled.h.gch

export VPATH	:= $(foreach dir,$(SOURCES),$(CURDIR)/$(dir))

export INCLUDE	:= $(foreach dir,$(INCLUDES),-I$(CURDIR)/$(dir))
#-----------------------------------------
%.o : %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

$(PRECOMPILED) : include/Precompiled.h
	$(CXX) $(CXXFLAGS) $(INCLUDE) $<
#-----------------------------------------
.PHONY: clean, run

all: $(OUTPUT)
	

clean:
	rm -rf $(OFILES) $(OUTPUT) $(PRECOMPILED)

run: $(OUTPUT)
	$(OUTPUT)

$(OFILES): $(PRECOMPILED)


$(OUTPUT): $(OFILES)
	$(CXX) $(CXXFLAGS) -o $@ $(OFILES) $(LIBS)

