#!/bin/bash

# JDK bin directory
#JDKBIN=/usr/java/jdk1.6.0_04/bin
JDKBIN=/usr/bin
#JDKLIB=/usr/java/jre1.6.0_06/lib
JDKLIB=/System/Library/Frameworks/JavaVM.framework/Versions/A/Resources/Deploy.bundle/Contents/Resources/Java

$JDKBIN/javac -g -d dist -source 1.3 -target 1.3 ./java/*.java -classpath $JDKLIB/plugin.jar

#
# now in dist... move into the compiled folder, and package it up
#
cd dist
$JDKBIN/jar cvfm bulkupload.jar manifest *.class > /dev/null
rm -rf *.class
$JDKBIN/jarsigner -keystore mykeystore -storepass switchback bulkupload.jar switchback

rm -rf ../../bulkupload.jar
cp -p bulkupload.jar ../../bulkupload.jar