sudo apt-get install python-dev # 2.7
sudo apt-get install libpython-all-dev # C binaries

# Compile
# old: gcc -I/usr/include/python2.7 CallPythonTest.c -lpython2.7
gcc CallPythonTest.c -lpython2.7 -I/usr/include/python2.7 -o CallPythonTest

