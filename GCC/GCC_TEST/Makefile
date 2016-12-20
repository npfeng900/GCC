# all dependece includes and libs
DIR_CURR=.
DIR_HEAD=$(DIR_CURR)/head
DIR_SRC=$(DIR_CURR)/src
DIR_DEBUG=$(DIR_CURR)/debug

# compile and link flags
GCC = g++
CPPFLAGS = -I"$(DIR_CURR)" -I"$(DIR_HEAD)"  -I"$(DIR_SRC)"
CXXFLAGS = -g -c
LINK = -g


# target and objects
FUN       = fun
TARGET    = main
FUN_OBJ   = $(FUN).o
TARGET_OBJ= $(TARGET).o


# make dependecne
all : $(TARGET) clean run
$(TARGET) : $(TARGET_OBJ) $(FUN_OBJ)
	$(GCC) $(CPPFLAGS) $(LINK) $^ -o $@
$(TARGET_OBJ): $(DIR_SRC)/$(TARGET).cpp $(DIR_HEAD)/$(FUN).h
	$(GCC) $(CPPFLAGS) $(CXXFLAGS) $< -o $@
$(FUN_OBJ): $(DIR_SRC)/$(FUN).cpp  $(DIR_HEAD)/$(FUN).h
	$(GCC) $(CPPFLAGS) $(CXXFLAGS) $< -o $@

# other commands
.PHONY : clean
clean:
	rm -f *.o *~

.PHONY : run
run:
	./$(TARGET)












