# ==========================================
# File: Makefile (Optimized)
# ==========================================

CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wno-unused-private-field -O2 # Thêm -O2 để tối ưu tốc độ chạy

TARGET = tour_app
SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)

# Tìm tất cả file header trong các thư mục con
HEADERS = $(shell find . -name "*.h")

# --- Rules ---

all: setup $(TARGET)

setup:
	@mkdir -p data
	@touch data/tours.txt data/customers.txt data/employees.txt data/bookings.txt
	@echo "[INFO] Ready: Data directory and files initialized."

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)
	@echo "[INFO] Build successful! Output: $(TARGET)"

# Quy tắc biên dịch file .o phụ thuộc vào cả file .cpp và tất cả .h
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
	@echo "[INFO] Cleaned up object files and executable."

run: clean all
	@echo "========================================"
	@echo "           STARTING PROGRAM             "
	@echo "========================================"
	./$(TARGET)

.PHONY: all setup clean run