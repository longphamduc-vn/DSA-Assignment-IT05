import pyautogui
import time
import os
import platform

SCREENSHOT_DIR = "screenshots"
os.makedirs(SCREENSHOT_DIR, exist_ok=True)

def type_and_enter(text, wait_time=0.1):
    """Gõ phím và nhấn Enter"""
    pyautogui.write(str(text))
    pyautogui.press('enter')
    time.sleep(wait_time)

def take_screenshot_and_back(filename, wait_time=0.3):
    """Chờ UI load kết quả, chụp ảnh, sau đó bấm Enter để qua màn hình pauseScreen()"""
    time.sleep(wait_time)
    filepath = os.path.join(SCREENSHOT_DIR, filename)
    
    if os.path.exists(filepath):
        try: os.remove(filepath)
        except: pass

    pyautogui.screenshot(filepath)
    print(f"[V] Đã chụp: {filename}")
    
    pyautogui.press('enter')
    time.sleep(0.1)

def run_full_test():
    exe_name = "tour_app"
    
    print("======================================================")
    print(" BẮT ĐẦU CHỤP ẢNH TOÀN BỘ TỪNG CHỨC NĂNG CỦA HỆ THỐNG")
    print("======================================================")
    
    try:
        if platform.system() == "Windows":
            os.startfile(f"{exe_name}.exe")
        else:
            os.system(f"./{exe_name} &")
    except Exception as e:
        print(f"[LỖI] {e}")
        return

    time.sleep(3)
    print("...Đang tự động chạy, VUI LÒNG KHÔNG CHẠM CHUỘT/BÀN PHÍM...\n")

    # # =========================================================
    # # MENU 1: MASTER DATA MANAGEMENT
    # # =========================================================
    # print("--- MENU 1: MASTER DATA ---")
    # type_and_enter('1')
    
    # # READ DATA
    # type_and_enter('3'); take_screenshot_and_back('M1_01_DocFileTour.png')
    # type_and_enter('7'); take_screenshot_and_back('M1_02_DocFileCustomer.png')
    # type_and_enter('11'); take_screenshot_and_back('M1_03_DocFileEmployee.png')
    # type_and_enter('15'); take_screenshot_and_back('M1_04_DocFileBooking.png')
    
    # # OUTPUT DATA
    # type_and_enter('2'); take_screenshot_and_back('M1_05_HienThiTour.png')
    # type_and_enter('6'); take_screenshot_and_back('M1_06_HienThiCustomer.png')
    # type_and_enter('10'); take_screenshot_and_back('M1_07_HienThiEmployee.png')
    # type_and_enter('14'); take_screenshot_and_back('M1_08_HienThiBooking.png')
    
    # type_and_enter('0') # Back

    # # =========================================================
    # # MENU 2: UPDATE INFORMATION (CRUD)
    # # =========================================================
    # print("--- MENU 2: UPDATE INFO (CRUD) ---")
    # type_and_enter('2')
    
    # # TOUR
    # type_and_enter('1') # Add Tour
    # type_and_enter('T999')
    # type_and_enter('Tour Kiem Thu')
    # type_and_enter('Ha Noi')
    # type_and_enter('2500000')
    # type_and_enter('3')
    # type_and_enter('20')
    # type_and_enter('20')
    # type_and_enter('15/08/2025')
    # type_and_enter('active')
    # take_screenshot_and_back('M2_01_ThemTourMoi.png')

    # type_and_enter('') 

    # type_and_enter('2') # Edit Tour
    # type_and_enter('T999')
    # type_and_enter('T999')
    # type_and_enter('Tour Kiem Thu (Da Sua)')
    # type_and_enter('Da Nang')
    # type_and_enter('3000000')
    # type_and_enter('4')
    # type_and_enter('25')
    # type_and_enter('25')
    # type_and_enter('20/08/2025')
    # type_and_enter('active')
    # take_screenshot_and_back('M2_02_SuaThongTinTour.png')

    # # CUSTOMER
    # type_and_enter('') 

    # type_and_enter('4') # Add Cust
    # type_and_enter('C999')
    # type_and_enter('Khach Hang Test')
    # type_and_enter('0912345678')
    # type_and_enter('test@email.com')
    # take_screenshot_and_back('M2_03_ThemCustomer.png')

    # type_and_enter('') 

    # type_and_enter('5') # Edit Cust
    # type_and_enter('C999')
    # type_and_enter('C999')
    # type_and_enter('Khach Hang Test (Sua)')
    # type_and_enter('0988888888')
    # type_and_enter('test_sua@email.com')
    # take_screenshot_and_back('M2_04_SuaCustomer.png')

    # # EMPLOYEE
    # type_and_enter('') 

    # type_and_enter('7') # Add Emp
    # type_and_enter('E999')
    # type_and_enter('Nhan Vien Test')
    # type_and_enter('TourGuide')
    # take_screenshot_and_back('M2_05_ThemEmployee.png')

    # type_and_enter('') 

    # type_and_enter('8') # Edit Emp
    # type_and_enter('E999')
    # type_and_enter('E999')
    # type_and_enter('Nhan Vien Test (Sua)')
    # type_and_enter('Manager')
    # take_screenshot_and_back('M2_06_SuaEmployee.png')

    # # BOOKING
    # type_and_enter('') 

    # type_and_enter('10') # Add Booking
    # type_and_enter('C999') # ID Khach
    # type_and_enter('T999') # ID Tour
    # type_and_enter('B999') # ID Booking
    # type_and_enter('2')    # So nguoi
    # type_and_enter('01/06/2025') # Ngay dat
    # take_screenshot_and_back('M2_07_TaoBooking.png')
    
    # type_and_enter('0') # Back

    # =========================================================
    # MENU 3: DATA QUERY (SEARCH)
    # =========================================================
    # print("--- MENU 3: DATA QUERY ---")
    type_and_enter('3')
    
    type_and_enter('1'); type_and_enter('Ha Noi') # Search Tour
    type_and_enter('0')
    take_screenshot_and_back('M3_01_TimKiemTour.png')
    
    type_and_enter('2'); type_and_enter('Nguyen Van A') # Search Customer
    take_screenshot_and_back('M3_02_TimKiemCustomer.png')
    
    type_and_enter('3'); type_and_enter('Staff') # Search Employee (Giả định phím 3)
    take_screenshot_and_back('M3_03_TimKiemEmployee.png')
    
    type_and_enter('4'); type_and_enter('B005') # Search Booking
    take_screenshot_and_back('M3_04_TimKiemBooking.png')
    
    type_and_enter('0') # Back

    # =========================================================
    # MENU 4: DATA ORGANIZATION (SORT)
    # =========================================================
    print("--- MENU 4: SORTING ---")
    type_and_enter('4')
    
    # Ghi chú: Chỉnh lại các phím (1, 2, 3...) cho khớp với giao diện menu 4 thực tế của bạn
    type_and_enter('1'); take_screenshot_and_back('M4_01_SapXepTour.png')
    type_and_enter('2'); take_screenshot_and_back('M4_02_SapXepCustomer.png')
    
    type_and_enter('0') # Back

    # =========================================================
    # MENU 5: BOUNDARY ANALYSIS (MAX/MIN)
    # =========================================================
    print("--- MENU 5: BOUNDARY ANALYSIS ---")
    type_and_enter('5')
    
    type_and_enter('1'); take_screenshot_and_back('M5_01_MaxMin_GiaTour.png')
    type_and_enter('2'); take_screenshot_and_back('M5_02_MaxMin_ThoiGianTour.png')
    type_and_enter('3'); take_screenshot_and_back('M5_03_MaxMin_DoPhoBienTour.png')
    type_and_enter('4'); take_screenshot_and_back('M5_04_MaxMin_SoNguoiDatBooking.png')
    
    type_and_enter('0') # Back

    # =========================================================
    # MENU 6: GENERAL MEASUREMENT
    # =========================================================
    print("--- MENU 6: MEASUREMENT ---")
    type_and_enter('6')
    
    type_and_enter('1'); take_screenshot_and_back('M6_01_TongQuanHeThong.png')
    type_and_enter('4'); take_screenshot_and_back('M6_02_BaoCaoTaiChinh.png')
    type_and_enter('3'); take_screenshot_and_back('M6_03_ThongKeNhanVien.png')
    
    type_and_enter('0') # Back

    # =========================================================
    # MENU 7: CATEGORICAL REPORTING
    # =========================================================
    print("--- MENU 7: CATEGORICAL REPORT ---")
    type_and_enter('7')
    
    type_and_enter('1'); take_screenshot_and_back('M7_01_TourTheoDiemDen.png')
    
    type_and_enter('2'); type_and_enter('1000000'); type_and_enter('5000000') # Nhập Min - Max Price
    take_screenshot_and_back('M7_02_TourTheoKhoangGia.png')
    
    type_and_enter('3'); take_screenshot_and_back('M7_03_TourTheoTrangThai.png')
    type_and_enter('4'); take_screenshot_and_back('M7_04_DoanhThuTheoTungTour.png')
    type_and_enter('5'); take_screenshot_and_back('M7_05_GiaTriTrungBinhTheoTrangThai.png')
    type_and_enter('6'); take_screenshot_and_back('M7_06_BookingTheoTrangThai.png')
    type_and_enter('7'); take_screenshot_and_back('M7_07_NhanVienTheoChucVu.png')
    type_and_enter('8'); take_screenshot_and_back('M7_08_HieuSuatNhanVien.png')
    
    type_and_enter('0') # Back

    # =========================================================
    # DELETE DATA (DỌN DẸP DỮ LIỆU ĐÃ TEST)
    # =========================================================
    print("--- DỌN DẸP DỮ LIỆU TEST ---")
    type_and_enter('2') # Vào lại Menu 2
    
    type_and_enter('11'); type_and_enter('B999'); take_screenshot_and_back('M8_01_XoaBookingTest.png')
    type_and_enter('3');  type_and_enter('T999'); take_screenshot_and_back('M8_02_XoaTourTest.png')
    type_and_enter('6');  type_and_enter('C999'); take_screenshot_and_back('M8_03_XoaCustomerTest.png')
    type_and_enter('9');  type_and_enter('E999'); take_screenshot_and_back('M8_04_XoaEmployeeTest.png')
    
    type_and_enter('0') # Back

    # =========================================================
    # LƯU FILE VÀ THOÁT
    # =========================================================
    print("--- LƯU DATA VÀ THOÁT ---")
    type_and_enter('1') # Vào Menu 1
    
    type_and_enter('4'); take_screenshot_and_back('M9_01_LuuFileTour.png')
    type_and_enter('8'); take_screenshot_and_back('M9_02_LuuFileCustomer.png')
    type_and_enter('12'); take_screenshot_and_back('M9_03_LuuFileEmployee.png')
    type_and_enter('16'); take_screenshot_and_back('M9_04_LuuFileBooking.png')
    
    type_and_enter('0') # Về Menu chính
    type_and_enter('0', wait_time=2) # Nhấn 0 để thoát hẳn
    
    pyautogui.screenshot(os.path.join(SCREENSHOT_DIR, 'M10_ManHinhThoat.png'))

    print("\n" + "="*50)
    print(f"[HOÀN TẤT] Mở thư mục '{SCREENSHOT_DIR}' để xem tất cả ảnh chức năng!")
    print("="*50)

if __name__ == "__main__":
    run_full_test()