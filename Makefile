CXX = g++
CXXFLAGS = -std=c++17
INCLUDES = -IC:\SFML\include
LIBDIRS = -LC:\SFML\lib
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

TARGET = main.exe
SOURCES = $(wildcard src/*.cpp)

all: $(TARGET)

$(TARGET): $(SOURCES)
	@echo Compiling $(TARGET)...
	$(CXX) $(CXXFLAGS) $(SOURCES) $(INCLUDES) $(LIBDIRS) $(LIBS) -o $(TARGET)
	@echo Build successful!

run:  $(TARGET)
	@echo Running $(TARGET)...
	@$(TARGET)
	@echo.

test: $(TARGET) run

clean:
	@echo Cleaning up...
	@if exist $(TARGET) del /q $(TARGET)
	@if exist *.o del /q *.o
	@if exist *.obj del /q *.obj
	@if exist *.exe del /q *.exe
	@if exist *~ del /q *~
	@if exist *.swp del /q *.swp
	@if exist *.swo del /q *.swo
	@if exist *.un~ del /q *.un~
	@if exist *.tmp del /q *.tmp
	@echo Cleanup complete!

help:
	@echo Available targets:
	@echo	all	- Build the program (default)
	@echo	run	- Build and run the program
	@echo	test	- Same as run
	@echo	clean - Remove compiled files
	@echo	help	- Show this help

.PHONY: all run test clean help
