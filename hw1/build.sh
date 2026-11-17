mkdir build
g++ line-and-arc.h draw-line-and-arc.cpp line-and-arc-impl.cpp -lglut -lGLU -lGL -o build/line-and-arc
g++ line-and-arc.h line-and-arc-impl.cpp shape.h shape-impl.cpp draw-shape.cpp -lglut -lGLU -lGL -o build/shape
g++ line-and-arc.h line-and-arc-impl.cpp shape.h shape-impl.cpp draw-not-filled-mini-computer-logo.cpp -lglut -lGLU -lGL -o build/not-filled-mini-computer-logo
g++ line-and-arc.h line-and-arc-impl.cpp shape.h shape-impl.cpp draw-filled-mini-computer-logo.cpp -lglut -lGLU -lGL -o build/filled-mini-computer-logo
g++ line-and-arc.h line-and-arc-impl.cpp shape.h shape-impl.cpp interact.cpp -lglut -lGLU -lGL -o build/interact
