VERSION=1.0


CFLAGS= -O2 -Wall -march=native -g -pipe -D_FORTIFY_SOURCE=2 -fstack-protector-strong -fstack-clash-protection -fomit-frame-pointer -fsanitize=address
#CFLAGS= -O2 -Wall -march=native -g -pipe 
LDFLAGS=

CC=cc

