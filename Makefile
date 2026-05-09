# ==========================================
# File: Makefile
# Author: Phạm Đức Long
# Description: Tự động hóa quá trình biên dịch dự án Quản lý Đặt Tour
# Môi trường đề xuất: WSL / Linux (với clang++)
# ==========================================

# 1. Cấu hình Trình biên dịch (Sử dụng clang++ theo môi trường WSL của bạn)
CXX = clang++

# 2. Cờ biên dịch (Compile Flags)
# -std=c++17: Sử dụng chuẩn C++17
# -Wall -Wextra: Bật các cảnh báo lỗi để code an toàn hơn
# -Wno-unused-private-field: Tắt cảnh báo trường private không sử dụng trong Menu.h
CXXFLAGS = -std=c++17 -Wall -Wextra -Wno-unused-private-field

# 3. Tên file thực thi đầu ra
TARGET = tour_app

# 4. Danh sách các file mã nguồn (.cpp)
# Do dự án hiện tại chủ yếu dùng Template và Header-only, chỉ có main.cpp
SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)

# 5. Danh sách các file Header (Để tự động biên dịch lại nếu bạn sửa code trong các file .h)
HEADERS = $(wildcard core/*.h models/*.h data/*.h services/*.h utils/*.h menu/*.h)

# ==========================================
# CÁC LUẬT BIÊN DỊCH (RULES)
# ==========================================

# Luật mặc định khi gõ lệnh 'make'
all: setup $(TARGET)

# Tự động tạo thư mục data/ và các file .txt rỗng (tránh lỗi FileIO khi chạy lần đầu)
setup:
	@mkdir -p data
	@touch data/tours.txt data/customers.txt data/employees.txt data/bookings.txt
	@echo "[INFO] Da khoi tao thu muc va file du lieu mau."

# Liên kết (Link) các object files thành file thực thi
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)
	@echo "[INFO] Bien dich thanh cong! File thuc thi: $(TARGET)"

# Biên dịch các file .cpp thành .o
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Lệnh 'make clean': Dọn dẹp các file rác sinh ra trong quá trình biên dịch
clean:
	rm -f $(OBJS) $(TARGET)
	@echo "[INFO] Da xoa cac file bien dich (.o, $(TARGET))."

# Lệnh 'make run': Vừa biên dịch (nếu có thay đổi) vừa chạy chương trình luôn
run: all
	@echo "========================================"
	@echo "          KHOI CHAY CHUONG TRINH        "
	@echo "========================================"
	./$(TARGET)

# Đánh dấu các luật không phải là file vật lý
.PHONY: all setup clean run