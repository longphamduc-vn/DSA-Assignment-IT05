#!/bin/bash

# Tên file đầu ra
output="AllInOne.cpp"

# Xóa file cũ nếu có
rm -f "$output"

# Tìm tất cả file .cpp và .h trong thư mục hiện tại và các thư mục con
find . -type f \( -name "*.cpp" -o -name "*.h" \) | while read file; do
    echo "// ===== Bắt đầu $file =====" >> "$output"
    cat "$file" >> "$output"
    echo -e "\n// ===== Kết thúc $file =====\n" >> "$output"
done

echo "✅ Đã gộp tất cả các file .cpp và .h trong thư mục và thư mục con thành $output"
