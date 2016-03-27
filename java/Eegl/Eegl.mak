OBJ=Eegl.class

CC=javac

Eegl.class:	      Eegl.java
		$(CC) Eegl.java

clean:
		rm -f $(OBJ)
