# Compiler settings
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

# File names
TARGET = load_balancer.exe
SOURCE = *.cpp *.h

# Main targets
all: $(TARGET)

$(TARGET): $(SOURCE)
	@echo Compiling $(SOURCE)...
	@$(CXX) $(CXXFLAGS) $(SOURCE) -o $(TARGET) 2>&1 || (echo Compilation failed. && exit 1)
	@echo Compilation successful.

run: $(TARGET)
	@./$(TARGET)

clean:
	@echo Cleaning...
	@del /F /Q $(TARGET) >nul 2>&1 || exit 0

.PHONY: all run clean
