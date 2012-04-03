MODE := 3
FRICTION := 7
EREST:= 1

CC := gcc -g
CFLAGS :=-lpthread -lGLU -lglut -lGL -lm
vpath %.h header
vpath %.c src
vpath %.o src
CFILES := aibot1.c start.c physics.c bothandler.c man.c manageer.c network.c rules.c msghandler.c
%.o: %.c headers.h
	@$(CC) $(CFLAGS) -c $< -o src/$@;
type:	
	@cd header;\
	echo "#define FRICTION $(FRICTION) \n#define MODE $(MODE) \n#define EREST $(EREST) \n" > mainhead1.h;\
	cd .. ;
carrom: type
	@cd src;\
	$(CC) $(CFLAGS) $(CFILES) -o carrom;\
	mv carrom ..;

