#!/bin/bash
make -f bit2raw.mak
cd Eegl
make -f Eegl.mak
cd ..
make -f TstEegl.mak
