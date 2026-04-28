# Trình biên dịch
CXX = g++
# Cờ biên dịch
CXXFLAGS = -Wall -std=c++11

# Tên file thực thi
TARGET = app

# Tìm tất cả các file .cpp trong các thư mục
SRCS = main.cpp \
       models/Tour.cpp models/Customer.cpp models/Booking.cpp \
       services/TourService.cpp \
       utils/FileHandler.cpp utils/Validator.cpp \
       menu/Menu.cpp

# Quy tắc biên dịch chính
all:
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

# Lệnh dọn dẹp file cũ
clean:
	rm -f $(TARGET)