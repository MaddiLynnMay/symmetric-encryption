CXX = g++
CXXFLAGS = -Wall -g

TARGET = main
BUILD_DIRECTORY = build

SRCS := $(shell find . -name '*.cpp' -not -path './$(BUILD_DIRECTORY)/*' | sed 's|^\./||')

OBJS = $(SRCS:%.cpp=$(BUILD_DIRECTORY)/%.o)

all: $(BUILD_DIRECTORY)/$(TARGET) run

$(BUILD_DIRECTORY)/$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

$(BUILD_DIRECTORY)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(BUILD_DIRECTORY)/$(TARGET)
	./$(BUILD_DIRECTORY)/$(TARGET)

.PHONY: all run clean

clean:
	rm -rf $(BUILD_DIRECTORY)