#/bin/bash
rcc -binary -compress 6 -threshold 7 ./manuscript.qrc -o ../../bin/templates/manuscript.rcc
cp ./manuscript.png ../../bin/templates/
cp ./manuscript.ini ../../bin/templates/
