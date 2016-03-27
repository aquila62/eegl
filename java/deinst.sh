#!/bin/bash
make -f bit2raw.mak clean
cd Eegl
make -f Eegl.mak clean
cd ..
make -f TstEegl.mak clean
