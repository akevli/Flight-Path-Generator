# Executable names:
EXE = airport
TEST = test

# Add all object files needed for compiling:
EXE_OBJ = main.o
OBJS = main.o vertex_parser.o graph.o random.o edge_parser.o BFS_Traversal.o dijkstra.o landmark_path.o connected_component.o

# Generated files
CLEAN_RM = actual-*.png

# Use the cs225 makefile template:
include cs225/make/cs225.mk