CXX=g++
CXXFLAGS += -g -Wall -Wextra -pthread
CPPFLAGS += -isystem src -std=c++11

MKDIR_P = mkdir -p
OBJ_DIR = obj

all: fork exec print wait pointer

${OBJ_DIR}:
	${MKDIR_P} ${OBJ_DIR}

obj/%.o: %.cpp ${OBJ_DIR}
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

fork: obj/fork.o
	$(CXX) -o $@ $^

print: obj/print.o
	$(CXX) -o $@ $^

exec: obj/exec.o
	$(CXX) -o $@ $^

wait: obj/wait.o
	$(CXX) -o $@ $^

pointer: obj/pointer.o
	$(CXX) -o $@ $^

clean:
	rm -f *~ obj/*.o *.zip
	rm -f fork exec print wait pointer
