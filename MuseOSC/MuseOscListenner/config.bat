del main_test.exe
g++ -std=c++14 main_test.cpp osc/*.cpp ip/*.cpp ip/win32/*.cpp -Wall -Wextra -I. -lwinmm -o main_test -lws2_32
pause