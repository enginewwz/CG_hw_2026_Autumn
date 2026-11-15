
g++ line-and-arc.h draw-line-and-arc.cpp line-and-arc-impl.cpp -lglut -lGLU -lGL -o build/line-and-arc
g++ line-and-arc.h line-and-arc-impl.cpp shape.h shape-impl.cpp draw-shape.cpp -lglut -lGLU -lGL -o build/shape