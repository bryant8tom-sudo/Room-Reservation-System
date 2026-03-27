CXX=clang++
CXX_FLAGS=-std=c++20 -g -fstandalone-debug -Iincludes -Wall -Wextra -Werror -fsanitize=address,null -fno-omit-frame-pointer -O0 -gdwarf-4 -Wno-unused-parameter

exec: bin/exec
tests: bin/tests

bin/exec: ./src/driver.cc ./src/room_reservation.cc ./includes/room_reservation.hpp 
	$(CXX) $(CXX_FLAGS) ./src/driver.cc ./src/room_reservation.cc -o $@

bin/tests: ./tests/tests.cc ./src/room_reservation.cc ./includes/room_reservation.hpp 
	$(CXX) $(CXX_FLAGS) ./tests/tests.cc ./src/room_reservation.cc -o $@

.DEFAULT_GOAL := exec
.PHONY: exec clean

clean:
	rm -rf bin/* 
