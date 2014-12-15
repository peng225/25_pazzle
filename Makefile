#Makefile


# CFLAGS = -c -g -O3 -Wall -std=c++0x -flto -DNDEBUG -MMD -MP
# FINAL_CFLAGS = -g -O3 -Wall -std=c++0x -flto -DNDEBUG

CFLAGS := -c -g -O3 -Wall -std=c++14 -flto -MMD -MP
FINAL_CFLAGS := -g -O3 -Wall -std=c++14 -flto

# CFLAGS = -c -g -O0 -Wall -std=c++0x -MMD -MP
# FINAL_CFLAGS = -g -O0 -Wall -std=c++0x

# CFLAGS = -c -g -O1 -Wall -std=c++0x -DNDEBUG -MMD -MP
# FINAL_CFLAGS = -g -O1 -Wall -std=c++0x -DNDEBUG

TARGET := movenum

SRC_DIR := ./src
INC_DIR := ./include
OBJ_DIR := ./obj

SRCS = $(shell ls $(SRC_DIR)/*.cpp)
OBJS = $(subst $(SRC_DIR), $(OBJ_DIR), $(SRCS:.cpp=.o))
DEPS = $(OBJS:.o=.d)

INCLUDE = -I $(INC_DIR)

CC := g++

all: $(TARGET)

-include $(DEPS)

$(TARGET): $(OBJS)
	$(CC) $(FINAL_CFLAGS) $(INCLUDE) -o $@ $^


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $< 

clean:
	rm -f $(TARGET) $(OBJS) $(DEPS) $(SRC_DIR)/*~ $(INC_DIR)/*~ ./*~

.PHONY: all clean
