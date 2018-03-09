#!/bin/bash
echo "Build Cossb for Timbo"
make timbo

echo "Copying files..."
cp -rp ./bin/cossb /usr/local/bin/
cp -rp ./bin/wsclient.comp /usr/local/bin/
cp -rp ./bin/wsclient.xml /usr/local/bin/
cp -rp ./bin/app_timbo.comp /usr/local/bin/
cp -rp ./bin/app_timbo.xml /usr/local/bin/
cp -rp ./bin/timboprotocol.comp /usr/local/bin/
cp -rp ./bin/timboprotocol.xml /usr/local/bin/
cp -rp ./bin/nanopi_timbo.comp /usr/local/bin/
cp -rp ./bin/nanopi_timbo.xml /usr/local/bin/
cp -rp ./bin/manifest_timbo.xml /usr/local/bin/

cp -rp ./bin/wsbroadcaster /usr/local/bin/
cp -rp ./bin/lwan /usr/local/bin/
cp -rp ./bin/lwan.conf /usr/local/bin/