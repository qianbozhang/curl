#!/bin/bash

#import env
source ./build/set_env.sh

#budil
./build/build_base.sh
./build/build_project.sh
#clear env
./build/unset_env.sh
