#/bin/bash
rcc -binary -compress 6 -threshold 7 ./blueblog.qrc -o ../../bin/templates/blueblog.rcc
cp ./blueblog.png ../../bin/templates/
cp ./blueblog.ini ../../bin/templates/
