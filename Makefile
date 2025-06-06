# Definição de variáveis
CXX      = g++
# CXX = clang++
CXXFLAGS = -g -std=c++17 -O0 -Wall  -I. -I./src -I./mock -I./Unity -I./test -DUNIT_TEST -DENABLE_TEST
SRC_DIR  = src
TEST_DIR = test
UNITY_DIR = Unity
BIN_DIR  = bin

# Arquivos-fonte
UNITY_SRC  = $(UNITY_DIR)/unity.cpp
BUTTON_SRC = $(SRC_DIR)/Button.cpp
TEST_SRC   = $(TEST_DIR)/test_button.cpp

# Executáveis
TARGET     = $(BIN_DIR)/test_button

# Regra padrão (constroi o teste e executa)
all: $(TARGET)
	@echo "Compilação concluída. Executando os testes..."
	@./$(TARGET)

# Garante que o diretório bin exista
$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

# Compila o código principal e os testes
$(TARGET): $(UNITY_SRC) $(BUTTON_SRC) $(TEST_SRC) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(UNITY_SRC) $(BUTTON_SRC) $(TEST_SRC) -o $(TARGET)

# Form -f $(OBJ) $(OBJ:.o=.d) $(BIN)rça a recompilação
force: clean all

# Limpeza dos binários
clean:
	@rm -rf $(BIN_DIR)
	@echo "Arquivos de compilação limpos."
