include ../make.vars

TARGET=exe
SUBDIR=.
SRC=$(foreach DIR, $(SUBDIR), $(wildcard ${DIR}/*.cpp ))
OBJ=$(patsubst %.cpp, %.o, $(SRC))

BIN_TARGET: $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(TARGET) $(LIB_DIR) -lcurl -lrt

$(OBJ): %.o:%.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@

.PHONY:clean
clean:
	@for DIR in $(SUBDIR); do	\
        rm -rf  $$DIR/*.o; 		\
    done
	@rm -rf $(TARGET);
