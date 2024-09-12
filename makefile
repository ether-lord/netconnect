BUILD_DIR=build

all: server

server: server.c
	gcc server.c -o $(BUILD_DIR)/server