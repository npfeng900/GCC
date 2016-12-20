# all dependece includes and libs
DIR_CURR=.

# compile and link flags
GCC = g++
CPPFLAGS = -I"$(DIR_CURR)"
CXXFLAGS = -g -c
LINK = -g


# target and objects
CLIENT   = Client
SERVER   = Server
CLIENT_OBJ= $(CLIENT).o
SERVER_OBJ= $(SERVER).o


# make dependecne
all : $(SERVER) $(CLIENT) clean
$(SERVER) : $(SERVER_OBJ)
	$(GCC) $(CPPFLAGS) $(LINK) $^ -o $@
$(SERVER_OBJ): $(SERVER).cpp $(SERVER).h
	$(GCC) $(CPPFLAGS) $(CXXFLAGS) $< -o $@
$(CLIENT) : $(CLIENT_OBJ)
	$(GCC) $(CPPFLAGS) $(LINK) $^ -o $@
$(CLIENT_OBJ): $(CLIENT).cpp $(CLIENT).h
	$(GCC) $(CPPFLAGS) $(CXXFLAGS) $< -o $@
$(SERVER).h : Frame.h

$(CLIENT).h : Frame.h


# other commands
.PHONY : clean
clean:
	rm -f *.o *~

.PHONY : run
run:
	./$(CLIENT)












