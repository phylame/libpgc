#  Copyright 2014 Peng Wan <minexiac@gmail.com>
#
#  Licensed under the Apache License, Version 2.0 (the "License");
#  you may not use this file except in compliance with the License.
#  You may obtain a copy of the License at

#      http://www.apache.org/licenses/LICENSE-2.0

#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.
#

STATIC_LIB = libxgc.a

SHARED_LIB = libxgc.so

# source path
VPATH = src

# distribute path
DISTDIR = dist

CFLAGS = -Wall -g -fPIC

CPPFLAGS = -Iinclude

OBJECTS = xgc.o array.o list.o

all: $(STATIC_LIB) $(SHARED_LIB)

$(STATIC_LIB): $(OBJECTS)
	@if [ ! -d $(DISTDIR) ]; then mkdir $(DISTDIR); fi
	$(AR) r $(DISTDIR)/$@ $?
	ranlib $(DISTDIR)/$@

$(SHARED_LIB): $(OBJECTS)
	@if [ ! -d $(DISTDIR) ]; then mkdir $(DISTDIR); fi
	$(CC) -shared -o $(DISTDIR)/$@ $?

clean:
	-rm *.o
	-rm $(DISTDIR)/*
	-rmdir $(DISTDIR)

.PHONY: clean
