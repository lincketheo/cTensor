#!/bin/bash


build_dat_baby () {
  mkdir builds
  pushd ./builds
  cmake ../src
  make
  cp run runTheDamnNetwork ../bin/
  popd
}

build_dat_baby
