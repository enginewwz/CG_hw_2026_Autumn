#!/usr/bin/env bash
set -u

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="$SCRIPT_DIR/build"

CXX="${CXX:-g++}"
CXXFLAGS="${CXXFLAGS:--std=c++17 -Wall -Wextra}"
LDLIBS="-lglut -lGLU -lGL"

if [ ! -d "$BUILD_DIR" ]; then
    if ! mkdir -p "$BUILD_DIR"; then
        echo "error: cannot create build directory: $BUILD_DIR" >&2
        exit 1
    fi
fi

if ! cd "$SCRIPT_DIR"; then
    echo "error: cannot enter directory: $SCRIPT_DIR" >&2
    exit 1
fi

FAILED=0

build() {
    local name="$1"
    shift

    if ! "$CXX" $CXXFLAGS "$@" $LDLIBS -o "$BUILD_DIR/$name"; then
        echo "error: build failed: $name" >&2
        FAILED=$((FAILED + 1))
    fi
}

COMMON="line-and-arc-impl.cpp shape-impl.cpp"

build line-and-arc                  $COMMON draw-line-and-arc.cpp
build shape                         $COMMON draw-shape.cpp
build not-filled-mini-computer-logo $COMMON draw-not-filled-mini-computer-logo.cpp
build filled-mini-computer-logo     $COMMON draw-filled-mini-computer-logo.cpp
build interact                      $COMMON interact.cpp

if [ "$FAILED" -ne 0 ]; then
    echo "error: $FAILED target(s) failed" >&2
    exit 1
fi
