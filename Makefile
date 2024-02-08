all: compile

compile:
	gcc *.c -o quack

clean:
	rm quack