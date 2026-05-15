import pyautogui
import time
import os
import platform

# Tạo thư mục lưu ảnh để không bị rác thư mục code
SCREENSHOT_DIR = "screenshots"
os.makedirs(SCREENSHOT_DIR, exist_ok=True)

def type_and_enter(text, wait_time=0.5):
    """Hỗ trợ gõ phím và nhấn Enter"""
    pyautogui.write(str(text))
    pyautogui.press('enter')
    time.sleep(wait_time)

def press_enter_for_pause(wait_time=0.5):
    """Chỉ bấm Enter để qua màn hình pauseScreen() mà không chụp ảnh"""
    time.sleep(wait_time)
    pyautogui.press('enter')
    time.sleep(0.5)

def take_screenshot_and_back(filename, wait_time=1.0):
    """Chờ UI load, chụp ảnh, và bấm Enter để qua pauseScreen()"""
    time.sleep(wait_time)
    filepath = os.path.join(SCREENSHOT_DIR, filename)
    pyautogui.screenshot(filepath)
    print(f"[V] Đã chụp ảnh: {filepath}")
    
    # Bấm Enter để qua hàm pauseScreen() của C++
    pyautogui.press('enter')
    time.sleep(0.5)

def run_full_test():
    exe_name = "tour_app"
    
    print("======================================================")
    print(f" BẮT ĐẦU TỰ ĐỘNG CHẠY FILE: {exe_name}")
    print("======================================================")
    
    try:
        if platform.system() == "Windows":
            os.startfile(f"{exe_name}.exe")
        else:
            os.system(f"./{exe_name} &")
        print(f"[INFO] Đã khởi chạy {exe_name} thành công.")
    except Exception as e:
        print(f"[LỖI] Lỗi khi khởi chạy: {e}")
        return

    # Đợi 3 giây để cửa sổ Console khởi động và tự động lấy focus
    time.sleep(3)
    print("...Đang chạy kịch bản tự động, vui lòng bỏ tay khỏi chuột và bàn phím...\n")

    # =========================================================
    # 1. MENU 1: Master Data Management (Load File và In danh sách)
    # =========================================================
    print("-> Test Menu 1: Master Data Management")
    type_and_enter('1')
    
    # Load dữ liệu từ file txt
    print("  [Load Tour từ file]")
    type_and_enter('3') # Read Tour
    press_enter_for_pause()
    
    print("  [Load Customer từ file]")
    type_and_enter('7') # Read Customer
    press_enter_for_pause()
    
    print("  [Load Employee từ file]")
    type_and_enter('11') # Read Employee
    press_enter_for_pause()
    
    print("  [Load Booking từ file]")
    type_and_enter('15') # Read Booking
    press_enter_for_pause()
    
    # In bảng ra màn hình và chụp ảnh
    print("  [Hiển thị danh sách Tour]")
    type_and_enter('2') # Output Tour
    take_screenshot_and_back('01_DanhSachTour.png')
    
    print("  [Hiển thị danh sách Customer]")
    type_and_enter('6') # Output Customer
    take_screenshot_and_back('02_DanhSachCustomer.png')
    
    print("  [Hiển thị danh sách Employee]")
    type_and_enter('10') # Output Employee
    take_screenshot_and_back('03_DanhSachEmployee.png')
    
    print("  [Hiển thị danh sách Booking]")
    type_and_enter('14') # Output Booking
    take_screenshot_and_back('04_DanhSachBooking.png')
    
    type_and_enter('0') # Back to Main Menu

    # =========================================================
    # 2. MENU 2: Update Information (ADD/EDIT/DELETE)
    # =========================================================
    print("\n-> Test Menu 2: Information Update (ADD/EDIT/DELETE)")
    type_and_enter('2')
    
    # ===== ADD TOUR =====
    print("  [Thêm Tour mới]")
    type_and_enter('1') # Add Tour
    # Nhập dữ liệu Tour
    type_and_enter('T999')  # Tour ID
    type_and_enter('Tour Phu Quoc')  # Tour Name
    type_and_enter('Phu Quoc')  # Destination
    type_and_enter('3500000')  # Price
    type_and_enter('4')  # Duration (days)
    type_and_enter('30')  # Max capacity
    time.sleep(1)
    press_enter_for_pause()
    
    # ===== DISPLAY TOUR AFTER ADD =====
    print("  [Hiển thị Tour sau khi thêm]")
    type_and_enter('2')  # Go back to Menu 2 first
    
    # Display all tours
    type_and_enter('0')  # Back to main
    type_and_enter('1')  # Menu 1 - Master Data
    type_and_enter('2')  # Output Tour
    take_screenshot_and_back('05_TourSauKhiThem.png')
    type_and_enter('0')  # Back
    
    # Go back to Menu 2
    type_and_enter('2')
    
    # ===== EDIT TOUR =====
    print("  [Sửa Tour]")
    type_and_enter('2') # Edit Tour
    type_and_enter('T999')  # Tour ID to edit
    type_and_enter('Tour Phu Quoc Updated')  # Update Tour Name
    type_and_enter('Phu Quoc Island')  # Update Destination
    type_and_enter('3800000')  # Update Price
    type_and_enter('5')  # Update Duration
    type_and_enter('35')  # Update Max capacity
    time.sleep(1)
    press_enter_for_pause()
    
    # ===== ADD CUSTOMER =====
    print("  [Thêm Customer mới]")
    type_and_enter('4') # Add Customer
    type_and_enter('C999')  # Customer ID
    type_and_enter('Nguyen Van A')  # Customer Name
    type_and_enter('0987654321')  # Phone
    type_and_enter('a@gmail.com')  # Email
    time.sleep(1)
    press_enter_for_pause()
    
    # ===== EDIT CUSTOMER =====
    print("  [Sửa Customer]")
    type_and_enter('5') # Edit Customer
    type_and_enter('C999')  # Customer ID to edit
    type_and_enter('Nguyen Van A Updated')  # Update Name
    type_and_enter('0988888888')  # Update Phone
    type_and_enter('a.updated@gmail.com')  # Update Email
    time.sleep(1)
    press_enter_for_pause()
    
    # ===== ADD EMPLOYEE =====
    print("  [Thêm Employee mới]")
    type_and_enter('7') # Add Employee
    type_and_enter('E999')  # Employee ID
    type_and_enter('Tran Van B')  # Employee Name
    type_and_enter('Sales')  # Position
    type_and_enter('0977777777')  # Phone
    time.sleep(1)
    press_enter_for_pause()
    
    # ===== EDIT EMPLOYEE =====
    print("  [Sửa Employee]")
    type_and_enter('8') # Edit Employee
    type_and_enter('E999')  # Employee ID to edit
    type_and_enter('Tran Van B Updated')  # Update Name
    type_and_enter('Manager')  # Update Position
    type_and_enter('0976666666')  # Update Phone
    time.sleep(1)
    press_enter_for_pause()
    
    # ===== ADD BOOKING =====
    print("  [Thêm Booking mới]")
    type_and_enter('10') # Add Booking
    type_and_enter('C999')  # Customer ID
    type_and_enter('T999')  # Tour ID
    # Nhập dữ liệu booking thêm (tùy thuộc InputHandler)
    type_and_enter('2025-05-20')  # Booking Date
    type_and_enter('5')  # Number of People
    type_and_enter('confirmed')  # Status
    type_and_enter('E999')  # Employee ID
    time.sleep(1)
    press_enter_for_pause()
    
    # ===== DISPLAY AFTER ALL ADDS =====
    print("  [Hiển thị dữ liệu sau khi thêm mới]")
    type_and_enter('0')  # Back to main
    type_and_enter('1')  # Menu 1
    type_and_enter('2')  # Output Tour
    take_screenshot_and_back('06_DuLieuSauKhiThemMoi.png')
    type_and_enter('0')  # Back
    
    # Go back to Menu 2 for delete operations
    type_and_enter('2')
    
    # ===== DELETE BOOKING =====
    print("  [Xóa Booking]")
    type_and_enter('11') # Delete Booking
    type_and_enter('B999')  # Booking ID to delete (nếu có)
    time.sleep(1)
    press_enter_for_pause()
    
    # ===== DELETE TOUR =====
    print("  [Xóa Tour]")
    type_and_enter('3') # Delete Tour
    type_and_enter('T999')  # Tour ID to delete
    time.sleep(1)
    press_enter_for_pause()
    
    # ===== DELETE CUSTOMER =====
    print("  [Xóa Customer]")
    type_and_enter('6') # Delete Customer
    type_and_enter('C999')  # Customer ID to delete
    time.sleep(1)
    press_enter_for_pause()
    
    # ===== DELETE EMPLOYEE =====
    print("  [Xóa Employee]")
    type_and_enter('9') # Delete Employee
    type_and_enter('E999')  # Employee ID to delete
    time.sleep(1)
    press_enter_for_pause()
    
    type_and_enter('0') # Back to Main Menu

    # =========================================================
    # 3. MENU 3: Data Query (SEARCH)
    # =========================================================
    print("\n-> Test Menu 3: Data Query (Search)")
    type_and_enter('3')
    
    # Search Tour
    print("  [Tìm kiếm Tour]")
    type_and_enter('1') # Search Tour
    type_and_enter('Ha Noi') # Từ khóa tìm kiếm
    take_screenshot_and_back('07_TimKiemTour.png')
    
    # Search Customer
    print("  [Tìm kiếm Customer]")
    type_and_enter('4') # Search Customer
    type_and_enter('Nguyen') # Từ khóa tìm kiếm
    take_screenshot_and_back('08_TimKiemCustomer.png')
    
    # Search Booking
    print("  [Tìm kiếm Booking theo Customer]")
    type_and_enter('7') # Search Booking by Customer
    type_and_enter('C001') # Customer ID
    take_screenshot_and_back('09_TimKiemBooking.png')
    
    type_and_enter('0') # Back to Main Menu

    # =========================================================
    # 4. MENU 4: Data Organization (SORT)
    # =========================================================
    print("\n-> Test Menu 4: Data Organization (Sort)")
    type_and_enter('4')
    
    print("  [Sắp xếp Tour theo Giá]")
    type_and_enter('3') # Sort Tour by Price
    take_screenshot_and_back('10_SapXepTourTheoGia.png')
    
    print("  [Sắp xếp Customer theo ID]")
    type_and_enter('4') # Sort Customer by ID
    take_screenshot_and_back('11_SapXepCustomerTheoID.png')
    
    type_and_enter('0') # Back to Main Menu

    # =========================================================
    # 5. MENU 5: Boundary Analysis (Min/Max)
    # =========================================================
    print("\n-> Test Menu 5: Boundary Analysis")
    type_and_enter('5')
    
    print("  [Phân tích Giá Tour]")
    type_and_enter('1') # Price Analysis
    take_screenshot_and_back('12_PhanTichGiaTour.png')
    
    print("  [Phân tích Người đặt Tour]")
    type_and_enter('4') # Booking People Analysis
    take_screenshot_and_back('13_PhanTichNguoiDatTour.png')
    
    type_and_enter('0') # Back to Main Menu

    # =========================================================
    # 6. MENU 6: General Measurement (Thống kê Tổng/Trung bình)
    # =========================================================
    print("\n-> Test Menu 6: General Measurement")
    type_and_enter('6')
    
    print("  [Tổng quan Tour]")
    type_and_enter('1') # Tour Overview
    take_screenshot_and_back('14_TongQuanTour.png')
    
    print("  [Báo cáo Tài chính]")
    type_and_enter('4') # Financial Report
    take_screenshot_and_back('15_BaoCaoTaiChinh.png')
    
    print("  [Thống kê nhân viên]")
    type_and_enter('5') # Employee Statistics
    take_screenshot_and_back('16_ThongKeNhanVien.png')
    
    type_and_enter('0') # Back to Main Menu

    # =========================================================
    # 7. MENU 7: Categorical Reporting (Phân loại & Thống kê)
    # =========================================================
    print("\n-> Test Menu 7: Categorical Reporting")
    type_and_enter('7')
    
    print("  [Tour theo Điểm đến]")
    type_and_enter('1') # Tours by Destination
    take_screenshot_and_back('17_TourTheoDiemDen.png')
    
    print("  [Doanh thu theo Tour]")
    type_and_enter('2') # Revenue by Tour
    take_screenshot_and_back('18_DoanhThuTheoTour.png')
    
    print("  [Đơn đặt theo Trạng thái]")
    type_and_enter('3') # Bookings by Status
    take_screenshot_and_back('19_DonDatTheoTrangThai.png')
    
    type_and_enter('0') # Back to Main Menu

    # =========================================================
    # SAVE DATA BEFORE EXIT
    # =========================================================
    print("\n-> Lưu dữ liệu trước khi thoát")
    type_and_enter('1') # Menu 1 - Master Data
    print("  [Lưu Tour vào file]")
    type_and_enter('4') # Save Tour
    press_enter_for_pause()
    
    print("  [Lưu Customer vào file]")
    type_and_enter('8') # Save Customer
    press_enter_for_pause()
    
    print("  [Lưu Employee vào file]")
    type_and_enter('12') # Save Employee
    press_enter_for_pause()
    
    print("  [Lưu Booking vào file]")
    type_and_enter('16') # Save Booking
    press_enter_for_pause()
    
    type_and_enter('0') # Back to Main Menu

    # =========================================================
    # EXIT PROGRAM
    # =========================================================
    print("\n-> Thoát chương trình")
    type_and_enter('0', wait_time=2)
    time.sleep(1)
    pyautogui.screenshot(os.path.join(SCREENSHOT_DIR, '20_ThoatVaLuuData.png'))
    print(f"[V] Đã chụp ảnh: {os.path.join(SCREENSHOT_DIR, '20_ThoatVaLuuData.png')}")

    print("\n" + "="*50)
    print("[THÀNH CÔNG] Quá trình tự động hóa đã hoàn tất!")
    print("Vui lòng kiểm tra thư mục 'screenshots' để xem kết quả.")
    print("="*50)

if __name__ == "__main__":
    run_full_test()