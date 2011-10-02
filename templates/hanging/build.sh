#/bin/bash
rcc -binary -compress 6 -threshold 7 ./hanging.qrc -o ../../bin/templates/hanging.rcc
cp ./hanging.png ../../bin/templates/
cp ./hanging.ini ../../bin/templates/
