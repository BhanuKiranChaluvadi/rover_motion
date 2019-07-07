# Introduction

Simple euclidean motion of a rover

# Requirements

An internet connection. This example will download the google test library the first time you run the CMake configure step. See the 
link:https://github.com/google/googletest/blob/master/googletest/README.md[google test readme] and link:http://crascit.com/2015/07/25/cmake-gtest/[here] for details.

# Building
[source,bash]
----
$ mkdir build

$ cd build/

$ cmake ..

$ make

$ make test

$ ./rover_binary

[source,bash]
----

