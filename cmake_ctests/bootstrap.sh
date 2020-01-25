#!/bin/bash


DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

mkdir -p "$DIR"/conan_deps
(cd "$DIR"/conan_deps && conan install .. -s compiler.cppstd=14 -s compiler.libcxx=libstdc++11 --build=missing )

cmake -DCMAKE_PROJECT_INCLUDE="$DIR"/conan_deps/conan_paths.cmake "$@"
