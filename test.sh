#! /bin/sh

g++ user/raytracer/vec3.cc test/vector_test.cc -o build/vector_test -I. -DISOLATE && ./build/vector_test
