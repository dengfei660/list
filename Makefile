TARGET= test

C_FILES = $(shell ls *.c)
BASE = $(basename $(C_FILES))
OBJS = $(addsuffix .o, $(addprefix obj/,$(BASE)))

$(TARGET):$(OBJS)
	rm -f $@
	g++ -o $(TARGET) $(OBJS) -pthread

obj/%.o:%.c
	@if test ! -d "obj"; then\
		mkdir -p obj;\
	fi;

	g++ -c -o $@ $<

clean:
	-rm -f test
	-rm -f obj/*.o