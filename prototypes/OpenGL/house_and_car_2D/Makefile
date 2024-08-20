# ==========================================================================
# @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
# ==========================================================================

HEADERS = Application.h Object.h Scene.h
SOURCES = Application.cxx Object.cxx Scene.cxx
OBJECTS = Application.o Object.o Scene.o
COMPILER = g++ -std=c++2a
CFLAGS = -O2
LDFLAGS = -lGL -lGLU -lglut

all: house_and_car_2D

house_and_car_2D: $(OBJECTS) house_and_car_2D.cxx
	$(COMPILER) $(CFLAGS) $(LDFLAGS) $^ -o $@

%.o: %.cxx %.h
	$(COMPILER) -c $(CFLAGS) $<

clean:
	rm -f $(OBJECTS) house_and_car_2D

# eof - $RCSfile$
