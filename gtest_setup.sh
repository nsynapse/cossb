#!/bin/bash
# Install googletest
if [ ! -e /usr/local/lib/libgtest.a ];then
	wget https://googletest.googlecode.com/files/gtest-1.7.0.zip
	unzip gtest-1.7.0.zip
	pushd gtest-1.7.0
		./configure
		make
		sudo cp -a include/gtest /usr/local/include
		sudo cp -a lib/.libs/libgtest.[as]* /usr/local/lib
		sudo ldconfig
	popd
	rm -rf gtest-1.7.0*
fi
