#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

// Cau truc du lieu nhan vien
struct Employee
{
    string EmployeeID;
    string Name;
    string DoB;
    string Email;
    string Address;
    int SoNgayCong;
    double LuongNgay;
    double ThucLinh = SoNgayCong * LuongNgay;
};

struct Node
{
    Employee data;
    Node* pNext;
};

typedef Node* LIST;

Node* create_node(Employee emp)
{
    Node* p = new Node;
    if (p == NULL)
        return NULL;
    p->data = emp;
    p->pNext = NULL;
    return p;
}

void create_list(LIST& l)
{
    l = NULL;
}

void add_head(LIST& l, Employee emp)
{
    Node* p = create_node(emp);
    if (l == NULL)
        l = p;
    else
    {
        p->pNext = l;
        l = p;
    }
}

void add_tail(LIST& l, Employee emp)
{
    Node* p = create_node(emp);
    if (l == NULL)
        l = p;
    else
    {
        Node* Q = l;
        while (Q->pNext != NULL)
            Q = Q->pNext;
        Q->pNext = p;
    }
}

int len_list(LIST l)
{
    Node* Q = l;
    int i = 0;
    while (Q != NULL)
    {
        i++;
        Q = Q->pNext;
    }
    return i;
}

void add_pos(LIST& l, Employee emp, int pos)
{
    if (pos <= 1)
        add_head(l, emp);
    else
    {
        if (pos > len_list(l))
            add_tail(l, emp);
        else
        {
            Node* p = create_node(emp);
            int i = 1;
            Node* Q = l;
            while (i != pos - 1)
            {
                i++;
                Q = Q->pNext;
            }
            p->pNext = Q->pNext;
            Q->pNext = p;
        }
    }
}

bool check_employee_id(LIST l, string id)
{
    Node* Q = l;
    while (Q != NULL)
    {
        if (Q->data.EmployeeID == id)
            return true;
        Q = Q->pNext;
    }
    return false;
}

void input_list(LIST& l)
{
    int n;
    cout << "Nhap so luong nhan vien can nhap: ";
    cin >> n;
    cin.ignore();
    for (int i = 0; i < n; i++)
    {
        cout << "\nNhap thong tin nhan vien thu " << i + 1 << ":\n";
        Employee emp;
        do
        {
            cout << "Nhap Ma NV: ";
            getline(cin, emp.EmployeeID);
            if (check_employee_id(l, emp.EmployeeID))
            {
                cout << "Loi: Ma NV da ton tai! Vui long nhap ma khac.\n";
            }
        } while (check_employee_id(l, emp.EmployeeID));

        cout << "Nhap Ten NV: ";
        getline(cin, emp.Name);
        cout << "Nhap Ngay sinh: ";
        getline(cin, emp.DoB);
        cout << "Nhap Email: ";
        getline(cin, emp.Email);
        cout << "Nhap Dia chi: ";
        getline(cin, emp.Address);
        cout << "Nhap so ngay cong: ";
        cin >> emp.SoNgayCong;
        cout << "Nhap luong ngay: ";
        cin >> emp.LuongNgay;
        emp.ThucLinh = emp.SoNgayCong * emp.LuongNgay;
        cin.ignore();
        add_tail(l, emp);
    }
};

void output_employee(Employee emp)
{
    cout << "Ma NV: " << emp.EmployeeID << endl;
    cout << "Ten NV: " << emp.Name << endl;
    cout << "Ngay sinh: " << emp.DoB << endl;
    cout << "Email: " << emp.Email << endl;
    cout << "Dia chi: " << emp.Address << endl;
    cout << "So ngay cong: " << emp.SoNgayCong << endl;
    cout << "Luong ngay: " << emp.LuongNgay << endl;
    cout << "Thuc linh: " << emp.ThucLinh << endl;
    cout << "-----------------------------\n";
};

void output_list(LIST l)
{
    Node* Q = l;
    while (Q != NULL)
    {
        output_employee(Q->data);
        Q = Q->pNext;
    }
};

void write_file(string filename, fstream& f, LIST l)
{
    f.open(filename, ios::out);
    Node* Q = l;
    while (Q != NULL)
    {
        f << Q->data.EmployeeID << endl;
        f << Q->data.Name << endl;
        f << Q->data.DoB << endl;
        f << Q->data.Email << endl;
        f << Q->data.Address << endl;
        f << Q->data.SoNgayCong << endl;
        f << Q->data.LuongNgay << endl;
        f << Q->data.ThucLinh << endl;
        Q = Q->pNext;
    }
    f.close();
};

void read_file(string filename, fstream& f, LIST& l)
{
    f.open(filename, ios::in);
    string temp;
    while (getline(f, temp))
    {
        Employee emp;
        emp.EmployeeID = temp;
        getline(f, emp.Name);
        getline(f, emp.DoB);
        getline(f, emp.Email);
        getline(f, emp.Address);
        f >> emp.SoNgayCong;
        f >> emp.LuongNgay;
        f >> emp.ThucLinh;
        f.ignore();
        add_tail(l, emp);
    }
    f.close();
};

void search_by_id(LIST l)
{
    string id;
    cout << "Nhap ma nhan vien can tim: ";
    getline(cin, id);
    Node* Q = l;
    while (Q != NULL)
    {
        if (Q->data.EmployeeID == id)
        {
            cout << "\n=== Thong tin nhan vien ===\n";
            output_employee(Q->data);
            return;
        }
        Q = Q->pNext;
    }
    cout << "\nKhong tim thay nhan vien co ma: " << id << "\n";
};

void search_by_name(LIST l)
{
    string nameSearch;
    cout << "Nhap ten nhan vien can tim: ";
    getline(cin, nameSearch);
    for(char &c : nameSearch)
    {
        c = tolower(c);
    }
    Node* Q = l;
    vector<Employee> results;
    while (Q != NULL)
    {   
        string empname = Q->data.Name;
        for(char &c : empname)
        {
            c = tolower(c);
        }
        if (empname.find(nameSearch) != string::npos)
        {
            results.push_back(Q->data);
        }
        Q = Q->pNext;
    }
    if (results.empty())
    {
        cout << "\nKhong tim thay nhan vien co ten: " << nameSearch << "\n";
    }
    else
    {
        cout << "\n=== Danh sach nhan vien tim thay ===\n";
        for (const auto& emp : results)
        {
            output_employee(emp);
        }
    }
};

void display_lowestEmp(LIST l)
{   
    if(l == NULL)
    {
        cout << "Danh sach rong!\n";
        return;
    }
    Node* Q = l;
    double lowestSalary = Q->data.ThucLinh;
    while (Q != NULL)
    {
        if (Q->data.ThucLinh < lowestSalary)
        {
            lowestSalary = Q->data.ThucLinh;
        }
        Q = Q->pNext;
    }
    cout << "=== Thong tin nhan vien co luong thap nhat ==="<< endl;
    Q = l;
    while(Q != NULL)
    {
        if(Q->data.ThucLinh == lowestSalary)
        {
            output_employee(Q->data);
        }
        Q = Q->pNext;
    }
};

void swap(Employee &x, Employee &y)
{
	Employee t = x; 
	x = y; 
	y = t;
}

void sort_by_salary(LIST& l)
{
    Node* Q = l;
    while (Q != NULL)
    {
        Node* P = Q->pNext;
        while (P != NULL)
        {
            if (Q->data.ThucLinh < P->data.ThucLinh)
            {
                swap(Q->data, P->data);
            }
            P = P->pNext;
        }
        Q = Q->pNext;
    };
    cout << "\nDanh sach da sap xep theo luong (giam dan) duoc luu vao DSNV_SAPXEP.txt\n";
};

void delete_emp(LIST& l)
{
    string id;
    if (l == NULL)
        return;
    cout << "Nhap ma nhan vien can xoa: ";
    getline(cin, id);
    while (l != NULL && l->data.EmployeeID == id)
    {
        Node* temp = l;
        l = l->pNext;
            fstream file;
        LIST tempList;
        create_list(tempList);
        add_tail(tempList, temp->data);
        write_file("DSNV_XOA.txt", file, tempList);
        delete temp;
        cout << "Da xoa nhan vien co ma: " << id << endl;
        return;
    }
};

void add_emp(LIST& l)
{
    Employee emp;
    cout << "\nNhap thong tin nhan vien can them:\n";
    do
    {
        cout << "Nhap Ma NV: ";
        getline(cin, emp.EmployeeID);
        if (check_employee_id(l, emp.EmployeeID))
        {
            cout << "Loi: Ma NV da ton tai! Vui long nhap ma khac.\n";
        }
    } while (check_employee_id(l, emp.EmployeeID));
    cout << "Nhap Ten NV: ";
    getline(cin, emp.Name);
    cout << "Nhap Ngay sinh: ";
    getline(cin, emp.DoB);
    cout << "Nhap Email: ";
    getline(cin, emp.Email);
    cout << "Nhap Dia chi: ";
    getline(cin, emp.Address);
    cout << "Nhap so ngay cong: ";
    cin >> emp.SoNgayCong;
    cout << "Nhap luong ngay: ";
    cin >> emp.LuongNgay;
    cin.ignore();
    add_tail(l, emp);
    fstream file;
    LIST tempList;
    create_list(tempList);
    add_tail(tempList, emp);
    write_file("DSNV_THEM.txt", file, tempList);
    cout << "Da them nhan vien co ma: " << emp.EmployeeID << endl;
};

void update_emp(LIST& l)
{
    string id;
    if (l == NULL)
        return;
    cout << "Nhap ma nhan vien can sua: ";
    getline(cin, id);
    Node *Q = l;
    while (Q != NULL)
    {
        if (Q->data.EmployeeID == id)
        {
            cout << "\nNhap thong tin nhan vien can sua:\n";
            cout << "Nhap Ten NV: ";
            getline(cin, Q->data.Name);
            cout << "Nhap Ngay sinh: ";
            getline(cin, Q->data.DoB);
            cout << "Nhap Email: ";
            getline(cin, Q->data.Email);
            cout << "Nhap Dia chi: ";
            getline(cin, Q->data.Address);
            cout << "Nhap so ngay cong: ";
            cin >> Q->data.SoNgayCong;
            cout << "Nhap luong ngay: ";
            cin >> Q->data.LuongNgay;
            cin.ignore();
            cout << "Da sua thong tin nhan vien co ma: " << id << endl;
            fstream file;
            LIST tempList;
            create_list(tempList);
            add_tail(tempList, Q->data);
            write_file("DSNV_SUA.txt", file, tempList);
            return;
        }
        Q = Q->pNext;
    }
    cout << "Khong tim thay nhan vien co ma: " << id << endl;
}



void display_menu() {
    cout << "\tCHUONG TRINH QUAN LY NHAN VIEN"     << endl;
    cout << "========================================" << endl;
    cout << "1. Nhap danh sach nhan vien" << endl;
    cout << "2. Doc danh sach nhan vien tu file"    << endl;
    cout << "3. Tim kiem theo ma nhan vien" << endl;
    cout << "4. Tim kiem theo ten nhan vien" << endl;
    cout << "5. Xuat nhan vien co luong thap nhat" << endl;
    cout << "6. Sap xep theo luong (giam dan)" << endl;
    cout << "7. Xoa nhan vien" << endl;
    cout << "8. Them nhan vien" << endl;
    cout << "9. Sua thong tin nhan vien" << endl;
    cout << "0. Thoat chuong trinh" << endl;
    cout << "Chon tac vu (0-9): ";
}

int main()
{
    int choice;
    LIST employeeList;
    create_list(employeeList);
    fstream file;
    read_file("DSNV.txt", file, employeeList);
    do
    {
        display_menu();
        cin >> choice;
        cin.ignore();
        switch (choice)
        {
        case 1:
            input_list(employeeList);
            write_file("DSNV.txt", file, employeeList);
            break;
        case 2:
            output_list(employeeList);
            break;
        case 3:
            search_by_id(employeeList);
            break;
        case 4:
            search_by_name(employeeList);
            break;
        case 5:
            display_lowestEmp(employeeList);
            break;
        case 6:
            sort_by_salary(employeeList);
            write_file("DSNV_SAPXEP.txt", file, employeeList);
            cout << "\nDanh sach da sap xep theo luong (giam dan) duoc luu vao DSNV_SAPXEP.txt\n";
            break;
        case 7:
            delete_emp(employeeList);
            break;
        case 8:
            add_emp(employeeList);
            break;
        case 9:
            update_emp(employeeList);
            break;
        case 0:
            cout << "\nCam on ban da su dung chuong trinh!\n";
            break;
        default:
            cout << "\nLua chon khong hop le. Vui long chon lai!\n";
        }
    } while (choice != 0);
    write_file("DSNV.txt", file, employeeList);
    return 0;
}