# Chương Trình Quản Lý Nhân Viên

![Version](https://img.shields.io/badge/version-1.0-blue) ![Language](https://img.shields.io/badge/language-C%2B%2B-brightgreen) ![Status](https://img.shields.io/badge/status-active-success)

Một ứng dụng C++ toàn diện để quản lý danh sách nhân viên sử dụng cấu trúc dữ liệu **danh sách liên kết đơn (Singly Linked List)**. Chương trình cung cấp các tính năng quản lý nhân viên từ nhập liệu, tìm kiếm, sắp xếp đến thêm, xóa, sửa thông tin với giao diện menu thân thiện.

---

## 📖 Mục Lục

- [Tính Năng Chính](#-tính-năng-chính)
- [Cấu Trúc Dữ Liệu](#-cấu-trúc-dữ-liệu)
- [Hàm Chính](#-các-hàm-chính)
- [Cấu Trúc File](#-cấu-trúc-file)
- [Hướng Dẫn Sử Dụng](#-hướng-dẫn-sử-dụng)
- [Ví Dụ Dữ Liệu](#-ví-dụ-dữ-liệu)
- [Lưu Ý Quan Trọng](#-lưu-ý-quan-trọng)
- [Yêu Cầu Hệ Thống](#-yêu-cầu-hệ-thống)
- [Độ Phức Tạp Thuật Toán](#-độ-phức-tạp-thuật-toán)
- [Khái Niệm DSA](#-khái-niệm-dsa-sử-dụng)

---

## 🎯 Tính Năng Chính

| # | Chức Năng | Mô Tả | File Lưu |
|----|----------|-------|----------|
| 1 | Nhập danh sách nhân viên | Nhập thông tin từ bàn phím với kiểm tra mã trùng lặp | DSNV.txt |
| 2 | Đọc danh sách từ file | Tải dữ liệu từ file `DSNV.txt` (tự động khi khởi động) | - |
| 3 | Tìm kiếm theo mã nhân viên | Tìm và hiển thị thông tin nhân viên bằng mã ID | - |
| 4 | Tìm kiếm theo tên nhân viên | Tìm kiếm theo từng phần của tên (không phân biệt hoa/thường) | - |
| 5 | Xem nhân viên lương thấp nhất | Hiển thị thông tin nhân viên có lương thực lĩnh thấp nhất | - |
| 6 | Sắp xếp theo lương | Sắp xếp danh sách theo lương giảm dần | DSNV_SAPXEP.txt |
| 7 | Xóa nhân viên | Xóa nhân viên theo mã, lưu thông tin vào file | DSNV_XOA.txt |
| 8 | Thêm nhân viên | Thêm nhân viên mới vào danh sách | DSNV_THEM.txt |
| 9 | Sửa thông tin nhân viên | Cập nhật thông tin nhân viên hiện có | DSNV_SUA.txt |

---

## 📁 Cấu Trúc Dữ Liệu

### Cấu Trúc Employee
```cpp
struct Employee {
    string EmployeeID;      // Mã nhân viên (ví dụ: NV001)
    string Name;            // Tên nhân viên
    string DoB;             // Ngày sinh (định dạng: DD/MM/YYYY)
    string Email;           // Email
    string Address;         // Địa chỉ
    int SoNgayCong;         // Số ngày công trong tháng
    long LuongNgay;         // Lương theo ngày (VND)
    long ThucLinh;          // Lương thực lĩnh = SoNgayCong * LuongNgay
};
```

### Danh Sách Liên Kết Đơn
```cpp
struct Node {
    Employee data;          // Dữ liệu nhân viên
    Node* pNext;            // Con trỏ tới node tiếp theo
};
typedef Node* LIST;         // LIST là con trỏ tới Node
```

---

## 🛠 Các Hàm Chính

### Quản lý Danh Sách Liên Kết (LinkedList Operations)

| Hàm | Mô Tả | Độ Phức Tạp |
|-----|-------|-------------|
| `create_list(LIST& l)` | Tạo danh sách rỗng | O(1) |
| `create_node(Employee emp)` | Tạo node mới | O(1) |
| `add_head(LIST& l, Employee emp)` | Thêm vào đầu danh sách | O(1) |
| `add_tail(LIST& l, Employee emp)` | Thêm vào cuối danh sách | O(n) |
| `add_pos(LIST& l, Employee emp, int pos)` | Thêm tại vị trí chỉ định | O(n) |
| `len_list(LIST l)` | Tính độ dài danh sách | O(n) |
| `del_head(LIST& l)` | Xóa node đầu tiên | O(1) |
| `del_tail(LIST& l)` | Xóa node cuối cùng | O(n) |
| `del_pos(LIST& l, int pos)` | Xóa node tại vị trí chỉ định | O(n) |
| `del_val(LIST& l, string val)` | Xóa tất cả node có giá trị mã nhân viên | O(n²) |

### Nhập/Xuất Dữ Liệu

| Hàm | Mô Tả |
|-----|-------|
| `input_list(LIST& l)` | Nhập danh sách nhân viên từ bàn phím |
| `output_list(LIST l)` | Hiển thị toàn bộ danh sách |
| `output_employee(Employee emp)` | Hiển thị thông tin một nhân viên (định dạng tiền tệ VND) |
| `read_file(string filename, fstream& f, LIST& l)` | Đọc dữ liệu từ file |
| `write_file(string filename, fstream& f, LIST l)` | Ghi dữ liệu vào file |
| `format_currency(long amount)` | Định dạng số thành tiền tệ VND (ví dụ: 5.500.000 VND) |

### Tìm Kiếm

| Hàm | Mô Tả | Độ Phức Tạp |
|-----|-------|-------------|
| `check_employee_id(LIST l, string id)` | Kiểm tra mã nhân viên tồn tại | O(n) |
| `search_byID(LIST l, string x)` | Tìm vị trí của node theo mã nhân viên | O(n) |
| `search_by_id(LIST l)` | Tìm và hiển thị nhân viên theo mã | O(n) |
| `search_by_name(LIST l)` | Tìm và hiển thị nhân viên theo tên (hỗ trợ tìm từng phần) | O(n) |

### Xử Lý Dữ Liệu

| Hàm | Mô Tả | Độ Phức Tạp |
|-----|-------|-------------|
| `sort_by_salary(LIST& l)` | Sắp xếp nhân viên theo lương giảm dần (Bubble Sort) | O(n²) |
| `display_lowestEmp(LIST l)` | Hiển thị nhân viên có lương thấp nhất | O(n) |
| `add_emp(LIST& l)` | Thêm nhân viên mới (với kiểm tra trùng mã) | O(n) |
| `delete_emp(LIST& l)` | Xóa nhân viên theo mã | O(n) |
| `update_emp(LIST& l)` | Sửa thông tin nhân viên | O(n) |

---

## 📂 Cấu Trúc File

```
Elearning2/
├── main.cpp                    # Mã nguồn chính (C++)
├── README.md                   # Tệp hướng dẫn này
├── DSNV.txt                    # Dữ liệu nhân viên gốc (được tải khi khởi động)
├── DSNV_SAPXEP.txt            # Danh sách nhân viên sắp xếp theo lương (giảm dần)
├── DSNV_THEM.txt              # Thông tin nhân viên vừa thêm
├── DSNV_SUA.txt               # Thông tin nhân viên vừa sửa
└── DSNV_XOA.txt               # Thông tin nhân viên vừa xóa
```

---

## 🚀 Hướng Dẫn Sử Dụng

### 1. Biên Dịch Chương Trình

**Trên Linux/Mac/Windows (với MinGW):**
```bash
g++ -o main main.cpp
```

**Hoặc chi tiết hơn:**
```bash
g++ -std=c++11 -Wall -O2 -o main main.cpp
```

### 2. Chạy Chương Trình

**Trên Linux/Mac:**
```bash
./main
```

**Trên Windows:**
```cmd
main.exe
```

### 3. Giao Diện Menu

Khi chạy, chương trình hiển thị menu chính:

```
  CHUONG TRINH QUAN LY NHAN VIEN
========================================
1. Nhap danh sach nhan vien
2. Doc danh sach nhan vien tu file
3. Tim kiem theo ma nhan vien
4. Tim kiem theo ten nhan vien
5. Xuat nhan vien co luong thap nhat
6. Sap xep theo luong (giam dan)
7. Xoa nhan vien
8. Them nhan vien
9. Sua thong tin nhan vien
0. Thoat chuong trinh
Chon tac vu (0-9): 
```

### 4. Các Bước Sử Dụng Cơ Bản

**Thêm Nhân Viên Mới:**
1. Chọn `8` từ menu
2. Nhập mã nhân viên (không được trùng)
3. Nhập các thông tin khác
4. Dữ liệu tự động được lưu vào `DSNV.txt` và `DSNV_THEM.txt`

**Tìm Kiếm Nhân Viên:**
1. Chọn `3` (tìm theo mã) hoặc `4` (tìm theo tên)
2. Nhập mã hoặc tên cần tìm
3. Chương trình hiển thị kết quả

**Xóa Nhân Viên:**
1. Chọn `7` từ menu
2. Nhập mã nhân viên cần xóa
3. Dữ liệu xóa được lưu vào `DSNV_XOA.txt`

---

## 📝 Ví Dụ Dữ Liệu

### Định Dạng File DSNV.txt

Mỗi nhân viên lưu trên 8 dòng liên tiếp:

```
NV001
Nguyen Van Anh
01/01/1990
nguyen.anh@company.com
123 Nguyen Hue, Ho Chi Minh
22
250000
5500000
NV002
Tran Thi Binh
15/03/1992
tran.binh@company.com
456 Le Loi, Ha Noi
20
280000
5600000
```

### Hiển Thị Trên Console

```
Ma NV: NV001
Ten NV: Nguyen Van Anh
Ngay sinh: 01/01/1990
Email: nguyen.anh@company.com
Dia chi: 123 Nguyen Hue, Ho Chi Minh
So ngay cong: 22
Luong ngay: 250.000 VND
Thuc linh: 5.500.000 VND
-----------------------------
```

---

## ⚙️ Lưu Ý Quan Trọng

### 1. Định Dạng Dữ Liệu
- **Mã Nhân Viên**: Không được trùng lặp (VD: NV001, NV002)
- **Ngày Sinh**: Định dạng DD/MM/YYYY (VD: 01/01/1990)
- **Email**: Định dạng email hợp lệ
- **Lương**: Số nguyên (VND), không có phần thập phân
- **Định dạng tiền tệ**: Hiển thị với dấu phân cách (VD: 5.500.000 VND)

### 2. Kiểm Tra & Xác Thực
- ✅ Kiểm tra mã trùng lặp khi thêm nhân viên
- ✅ Tự động tính lương thực lĩnh = Số ngày công × Lương ngày
- ✅ Tìm kiếm tên không phân biệt hoa/thường
- ✅ Hỗ trợ tìm kiếm theo từng phần của tên

### 3. Quản Lý File
- 📁 Danh sách gốc tự động tải từ `DSNV.txt` lúc khởi động
- 💾 Sau mỗi hành động, dữ liệu tự động lưu vào file tương ứng
- 📋 File `DSNV.txt` luôn được cập nhật khi thoát chương trình
- 🔄 Mỗi thao tác tạo bản ghi trong file riêng (THEM, XOA, SUA, SAPXEP)

### 4. Hạn Chế & Chú Ý
- ⚠️ Chương trình không hỗ trợ xóa toàn bộ dữ liệu một lần
- ⚠️ Tìm kiếm theo vị trí yêu cầu duyệt từ đầu danh sách
- ⚠️ Sắp xếp sử dụng Bubble Sort (O(n²)) không phù hợp với danh sách lớn
- ⚠️ Không hỗ trợ restore dữ liệu đã xóa từ file

---

## 🔧 Yêu Cầu Hệ Thống

### Phần Cứng
- CPU: Intel/AMD 1.5 GHz trở lên
- RAM: 512 MB trở lên
- Ổ cứng: 10 MB dung lượng trống

### Phần Mềm
- **Compiler C++**: 
  - GCC 4.8+ (Linux/Mac)
  - Clang 3.3+ (Linux/Mac)
  - MSVC 2013+ (Windows)
  - MinGW (Windows)
- **C++ Standard**: C++11 trở lên
- **Hệ điều hành**: 
  - Windows 7/8/10/11
  - Linux (Ubuntu, Debian, CentOS, v.v.)
  - macOS 10.9+

---

## 📊 Độ Phức Tạp Thuật Toán

| Hàm | Thời Gian | Không Gian | Ghi Chú |
|-----|-----------|-----------|---------|
| `create_list()` | O(1) | O(1) | Khởi tạo danh sách rỗng |
| `add_head()` | O(1) | O(1) | Thêm vào đầu danh sách |
| `add_tail()` | O(n) | O(1) | Phải duyệt để tìm cuối |
| `add_pos()` | O(n) | O(1) | Duyệt đến vị trí chỉ định |
| `len_list()` | O(n) | O(1) | Duyệt toàn bộ danh sách |
| `del_head()` | O(1) | O(1) | Xóa node đầu tiên |
| `del_tail()` | O(n) | O(1) | Phải duyệt để tìm cuối |
| `del_pos()` | O(n) | O(1) | Duyệt đến vị trí chỉ định |
| `search_by_id()` | O(n) | O(1) | Tìm kiếm tuyến tính |
| `search_by_name()` | O(n) | O(k) | k = số kết quả tìm được |
| `sort_by_salary()` | O(n²) | O(1) | Bubble Sort |
| `output_list()` | O(n) | O(1) | Duyệt và hiển thị |
| `read_file()` | O(n) | O(n) | Đọc n nhân viên |
| `write_file()` | O(n) | O(1) | Ghi n nhân viên |

**Ghi chú**: n = số lượng nhân viên trong danh sách

---

## 📚 Khái Niệm DSA Sử Dụng

### 1. Danh Sách Liên Kết Đơn (Singly Linked List)

**Khái Niệm**: Cấu trúc dữ liệu tuyến tính bao gồm các node, mỗi node chứa dữ liệu và con trỏ tới node tiếp theo.

**Ưu Điểm**:
- ✅ Thêm/xóa phần tử ở đầu danh sách: O(1)
- ✅ Cấp phát bộ nhớ động, không cần kích thước cố định
- ✅ Sử dụng bộ nhớ hiệu quả khi không biết trước số lượng phần tử

**Nhược Điểm**:
- ❌ Truy cập phần tử tại vị trí bất kỳ chậm: O(n)
- ❌ Sử dụng bộ nhớ cho con trỏ trong mỗi node
- ❌ Không thể duyệt ngược

### 2. Sắp Xếp Bubble Sort

**Khái Niệm**: Thuật toán sắp xếp đơn giản so sánh từng cặp phần tử liền kề và hoán đổi nếu chúng không đúng thứ tự.

**Quy Trình**:
1. Duyệt danh sách từ đầu
2. So sánh từng cặp node liền kề
3. Nếu lương không đúng thứ tự, hoán đổi dữ liệu
4. Lặp lại cho đến khi danh sách được sắp xếp

**Độ Phức Tạp**: O(n²)

### 3. Tìm Kiếm Tuyến Tính (Linear Search)

**Khái Niệm**: Tìm kiếm bằng cách duyệt lần lượt từng phần tử cho đến khi tìm thấy hoặc hết danh sách.

**Áp Dụng**:
- Tìm kiếm theo mã nhân viên: O(n)
- Tìm kiếm theo tên nhân viên: O(n)
- Kiểm tra mã trùng lặp: O(n)

---

## 🎓 Bài Học Rút Ra

1. **Danh sách liên kết**: Hiểu cách sử dụng con trỏ để tạo cấu trúc dữ liệu động
2. **Quản lý bộ nhớ**: Cấp phát và giải phóng bộ nhớ động với `new` và `delete`
3. **Thuật toán sắp xếp**: Implement bubble sort trên danh sách liên kết
4. **File I/O**: Đọc/ghi dữ liệu từ/vào file
5. **Tìm kiếm và xác thực**: Kiểm tra dữ liệu trùng lặp và tìm kiếm

---

## 📄 Giấy Phép

Chương trình này được tạo cho mục đích **học tập và giảng dạy** về cấu trúc dữ liệu danh sách liên kết và các khái niệm lập trình C++ cơ bản.

---

## 👨‍💻 Tác Giả

Phát triển cho: **Khóa học Cấu Trúc Dữ Liệu và Giải Thuật - E-Learning 2**

---

## 🔗 Tài Liệu Tham Khảo

- [Linked List - GeeksforGeeks](https://www.geeksforgeeks.org/linked-list-set-1-introduction/)
- [Bubble Sort - Wikipedia](https://en.wikipedia.org/wiki/Bubble_sort)
- [C++ File I/O](https://www.cplusplus.com/doc/tutorial/files/)
- [C++ Pointers](https://www.cplusplus.com/doc/tutorial/pointers/)

---

**Last Updated**: January 17, 2026  
**Status**: ✅ Active & Maintained
