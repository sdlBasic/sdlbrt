echo "--- clean linux ----------------------------------------------"
make -f cross/makefile os=linux cleanall

echo "--- clean win32 ----------------------------------------------"
make -f cross/makefile os=win32 cleanall

echo "--- clean open2x ---------------------------------------------"
make -f cross/makefile os=open2x cleanall


