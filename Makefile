.PHONY: all clean client shared graph

CXX = g++
AR = ar
INC_DIR = -Isrc
CXXFLAGS = -Wall --std=c++14 -O0 -DLINUX -g -pg $(INC_DIR)
LDFLAGS = -O0 -g -pg -lGL -lGLEW -lSDL2 -lSDL2_image -lSDL2_ttf -lGLU
SRC_DIR = src

SRCS_SHARED = $(wildcard \
	$(SRC_DIR)/*.cpp \
	$(SRC_DIR)/shared/*.cpp \
	$(SRC_DIR)/shared/**/*.cpp \
	$(SRC_DIR)/shared/**/**/*.cpp \
	$(SRC_DIR)/shared/**/**/**/*.cpp \
	$(SRC_DIR)/shared/**/**/**/**/*.cpp \
)
OBJS_SHARED =  $(SRCS_SHARED:.cpp=.o)
TARGET_SHARED = teeworlds3d_shared.a

SRCS_CLIENT = $(wildcard \
	$(SRC_DIR)/client/*.cpp \
	$(SRC_DIR)/client/**/*.cpp \
	$(SRC_DIR)/client/**/**/*.cpp \
	$(SRC_DIR)/client/**/**/**/*.cpp \
	$(SRC_DIR)/client/**/**/**/**/*.cpp \
)
OBJS_CLIENT = $(SRCS_CLIENT:.cpp=.o)
TARGET_CLIENT = teeworlds3d

SRCS = $(wildcard $(SRCS_SHARED) $(SRCS_CLIENT))
OBJS = $(wildcard $(OBJS_SHARED) $(OBJS_CLIENT))
TARGET = $(wildcard $(TARGET_SHARED) $(TARGET_CLIENT))

all: client

client: $(TARGET_CLIENT)
$(TARGET_CLIENT): $(OBJS_CLIENT) $(TARGET_SHARED)
	$(CXX) $(LDFLAGS) $(OBJS_CLIENT) $(TARGET_SHARED) -o $(TARGET_CLIENT)

shared: $(TARGET_SHARED)
$(TARGET_SHARED): $(OBJS_SHARED)
	$(AR) rcs $(TARGET_SHARED) $(OBJS_SHARED)

$(OBJS): %.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(TARGET) $(OBJS)

graph:
	dot -Tpng -O graph.dot
