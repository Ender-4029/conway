CFLAGS = -Wall -Wextra -std=c11 -g
LDFLAGS = -lncurses
SRC = src/main.c src/game.c
OBJ = $(SRC:.c=.o)

.PHONY: build clean

build: $(OBJ)
	@gcc $(CFLAGS) -o build/conway $(SRC) $(LDFLAGS)
	@echo "Built"

%.o: %.c
	@gcc $(CFLAGS) -c $< -o build/output/$@

clean:
	rm -rf build/*