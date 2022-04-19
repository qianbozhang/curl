#!/bin/bash

##########################env setting#####################
export ENV_DIR=$PWD
export ROOT=$ENV_DIR;
export BASE_DIR=$ROOT/base;
export INSTALL_DIR=$ROOT/vender/usr/local;

echo "env dir = $ENV_DIR";
echo "root = $ROOT";
echo "base dir = $BASE_DIR";
echo "install dir = $INSTALL_DIR";

## create install directory
if [ ! -d "$INSTALL_DIR" ]; then
	mkdir -p $INSTALL_DIR;
fi;

## check double
if [ ! -d "$INSTALL_DIR" ]; then
	exit;
fi;


## flags
export CC="gcc";
export CXX="g++";


## force pkg-cfg only searching for cross root
export PKG_CONFIG_PATH=$INSTALL_DIR/lib/pkgconfig;
export PKG_CONFIG_LIBDIR=$PKG_CONFIG_PATH;

