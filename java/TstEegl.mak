OBJ=TstEegl.class \
	EeglSum.class \
	EeglChi.class \
	EeglGen.class

CC=javac

all:			$(OBJ)

TstEegl.class:	      TstEegl.java
		$(CC) TstEegl.java

EeglSum.class:	      EeglSum.java
		$(CC) EeglSum.java

EeglChi.class:	      EeglChi.java
		$(CC) EeglChi.java

EeglGen.class:	      EeglGen.java
		$(CC) EeglGen.java

clean:
		rm -f $(OBJ)
