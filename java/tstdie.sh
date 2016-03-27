#!/bin/bash
java EeglGen | bit2raw | dieharder -g 200 -p 1 -d 0
