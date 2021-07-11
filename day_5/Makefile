LIBS=-lsfml-graphics -lsfml-window -lsfml-system
CXX:=g++

all: Test

%.o:%.cpp
	$(CXX) -c $< -o $@ -I ~/Desktop/mai-pract/day_5/SFML-2.5.1/include

Test: *.o
	$(CXX) -o Test *.o $(LIBS) -L ~/Desktop/mai-pract/day_5/SFML-2.5.1/lib

clean:
	@echo "Removing object files and executabes"
	rm -f Test
	rm -f *.o

install:
	@echo "Installing"
	cp smfl /usr/bin

uninstall:
	@echo "Uninstalling"
	rm Test
