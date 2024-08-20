# ==========================================================================
# @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
# ==========================================================================

HEADERS = Application.h Object.h Scene.h
SOURCES = Application.cxx Object.cxx Scene.cxx
OBJECTS = Application.o Object.o Scene.o
COMPILER = g++ -std=c++2a
CFLAGS = -O2
LDFLAGS = -lGL -lGLU -lglut

all: projectile_motion

projectile_motion: $(OBJECTS) projectile_motion.cxx
	$(COMPILER) $(CFLAGS) $(LDFLAGS) $^ -o $@

%.o: %.cxx %.h
	$(COMPILER) -c $(CFLAGS) $<

clean:
	rm -f $(OBJECTS) projectile_motion

# eof - $RCSfile$
