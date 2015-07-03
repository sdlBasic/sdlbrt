echo "--- compile linux ----------------------------------------------"
make -f cross/makefile os=linux clean >/dev/null
make -f cross/makefile os=linux >/dev/null
echo "----------------------------------------------------------------"

echo "--- compile win32 ----------------------------------------------"
make -f cross/makefile os=win32 clean >/dev/null
make -f cross/makefile os=win32 >/dev/null
echo "----------------------------------------------------------------"

echo "--- compile open2x ---------------------------------------------"
make -f cross/makefile os=open2x clean >/dev/null
make -f cross/makefile os=open2x >/dev/null
echo "----------------------------------------------------------------"

