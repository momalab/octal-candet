chmod 0777 -R *

cd cpp_cgt
call style.bat -r *.cpp *.h *.inc
cd ..
cd cpp_share
call style.bat -r *.cpp *.h *.inc
cd ..

#cd user
#call style.bat -r *.cpp *.h *.inc
#cd ..

cd db
cd templ
call style.bat -r *.cpp *.h *.inc
cd ..
cd ..

#cd ../tests/user
#call style.bat -r *.cpp *.h *.inc
#cd ..
