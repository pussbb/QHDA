#/bin/bash
rcc -binary -compress 6 -threshold 7 ./binarynews.qrc -o ../../bin/templates/binarynews.rcc
cp ./binarynews.png ../../bin/templates/
cp ./binarynews.ini ../../bin/templates/
