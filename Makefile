CXXFLAGS = -Wall -Wextra -Werror -pedantic -Weffc++
OBJS = QuickPaste.o main.o
TARGET = qpaste

all: $(OBJS)
	$(CXX) $^ -o $(TARGET)

clean:
	$(RM) $(OBJS) $(TARGET)

