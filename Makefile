PHONY: all clean
.DEFAULT_GOAL = all

BUILD_DIR = build
#Компилятор 
CXX = g++
$(BUILD_DIR):
	mkdir -p $@/src

# Флаги компиляции
CXXFLAGS = -Wall -Wextra

#Флаги линковки 
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

#Исходники и объектные файлы 
SOURCES := $(shell find src -name '*.cpp') 
OBJS := $(patsubst %.cpp, %.o, $(addprefix $(BUILD_DIR)/,$(SOURCES)))

#итоговый исполняемый файлы
$(BUILD_DIR)/%.o :%.cpp | $(BUILD_DIR)
	@echo $< $@
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BUILD_DIR)/prog: $(OBJS)
	$(CXX) $(CXXFLAG) -o $@ $(OBJS) $(LDFLAGS)


#TARGET =Kokotoni 

all:$(BUILD_DIR)/prog

#$(TARGET):$(OBJ)
#	$(CXX) $(CXXFLAG) -o $(TARGET) $(OBJ) $(LDFLAGS)

#%.o: %.cpp
#	$(CXX) $(CXXFLAGS) -c $< -o $@

#clean:
#	rm -f $(OBJ) #$(TARGET)

clean:
	rm -rf $(BUILD_DIR)
