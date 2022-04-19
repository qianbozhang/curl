#!/bin/bash

############################# openssl ##############################
cd $BASE_DIR/openssl-3.0.2
if [ ! -f "build_ok" ]; then
  echo ">>>>>>>>>>>>>>>>>>>>>>>>>>>> budil openssl-3.0.2 >>>>>>>>>>>>>>>>>>>>";
  ./Configure linux-armv4 --prefix=$INSTALL_DIR no-asm -fPIC shared
  make -j 8 && make install
fi;

if [ $? -eq 0 ]; then
  touch build_ok;
  echo "openssl-3.0.2 has finished build, please delete \"build_ok\" file in directory if you want to rebuild it";
else
  echo "openssl-3.0.2 build fail,plese fixed error and retry";
  exit 0;
fi;


############################ curl ################################
cd $BASE_DIR/curl-7.82.0
if [ ! -f "build_ok" ]; then
  echo ">>>>>>>>>>>>>>>>>>>>>>>>>>>> budil curl-7.82.0 >>>>>>>>>>>>>>>>>>>>";
  ./configure --prefix=$INSTALL_DIR   \
      CFLAGS="-fPIC -fPIE -pie"       \
      --with-openssl="$INSTALL_DIR"   \
      --with-ca-bundle=/application/certificates/cacert.pem	\
      --disable-telnet --disable-imap --disable-dict --disable-ftp --disable-tftp --disable-ldap --disable-ldaps --disable-gopher --disable-smtp --disable-smb
  make -j 8 && make install
fi;

if [ $? -eq 0 ]; then
  touch build_ok;
  echo "curl-7.82.0 has finished build, please delete \"build_ok\" file in directory if you want to rebuild it";
else
  echo "curl-7.82.0 build fail,plese fixed error and retry";
  exit 0;
fi;


