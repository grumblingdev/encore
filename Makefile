CC = /usr/bin/gcc
BUILD_DIR = ./build

mkdir: src/mkdir/mkdir.c
	$(CC) -o $(BUILD_DIR)/mkdir src/mkdir/mkdir.c -g
cp: src/cp/cp.c
	$(CC) -o $(BUILD_DIR)/cp src/cp/cp.c
