#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <list>

using namespace std;

// Lớp Tree đại diện cho thông tin của một cây
class Tree {
private:
    int id;         // Mã cây
    string name;    // Tên của cây
    int age;        // Tuổi của cây
    double height;  // Chiều cao của cây, đơn vị là mét

public:
    // Constructor mặc định
    Tree() : id(0), name(""), age(0), height(0.0) {}

    // Nap chong toan tu >> de nhap thong tin cay
    friend istream& operator>>(istream& in, Tree& tree) {
        cout << "Enter tree ID: ";
        in >> tree.id;

        cout << "Enter tree Name: ";
        in.ignore();
        getline(in, tree.name);

        cout << "Enter tree Age: ";
        in >> tree.age;

        cout << "Enter tree height (m): ";
        in >> tree.height;

        return in;
    }

    // Nap chong toan tu << de xuat thong tin cay
    friend ostream& operator<<(ostream& out, const Tree& tree) {
        out << "ID: " << tree.id << ",  Tree Name: " << tree.name
            << ",  Age: " << tree.age << ",  Height: " << tree.height << "m";
        return out;
    }

    // Nap chong toan tu < de so sanh dua tren chieu cao
    bool operator<(const Tree& other) const {
        return this->height < other.height;
    }

    // Lấy mã cây
    int getId() const {
        return id;
    }
};  // oke

// Lớp TreeList để quản lý danh sách cây
class TreeList {
private:
    vector<Tree> trees;  // Danh sách các cây

public:
    // Thêm cây vào danh sách
    void addTree(const Tree& tree) {
        trees.push_back(tree);
    }

    // Hiển thị danh sách cây
    void displayTrees() const {
        for (const auto& tree : trees) {
            cout << tree << endl;
        }
    }

    // Sắp xếp danh sách cây theo chiều cao
    void sortTrees() {
        sort(trees.begin(), trees.end());
    }

    // Tìm cây có chiều cao lớn nhất
    Tree findTallestTree() const {
        return *max_element(trees.begin(), trees.end());
    }

    // Tìm cây có chiều cao nhỏ nhất
    Tree findShortestTree() const {
        return *min_element(trees.begin(), trees.end());
    }

    // Xóa cây theo mã cây
    void deleteTreeById(int id) {
        trees.erase(remove_if(trees.begin(), trees.end(),
                              [id](const Tree& tree) { return tree.getId() == id; }),
                    trees.end());
    }
};

// Lớp App để quản lý ứng dụng
class App : public TreeList {
public:
    void menu() {
        int check;
        do {
            cout << "\n[=============== MEMU QUAN LY CAY ====================]\n";
            cout << "1. THEM CAY\n";
            cout << "2. HIEN THI DANH SACH CAY\n";
            cout << "3. SAP XEP CAY THEO CHIEU CAO \n";
            cout << "4. TIM CAY CAO NHAT\n";
            cout << "5. TIM CAY THAP NHAT\n";
            cout << "6. XOA CAY THEO ID\n";
            cout << "0. THOAT\n";
            cout<<"[=====================================================]\n";
            cout << " ==> LUA CHON CUA BAN : ";
            cin >> check;

            switch (check) {
                case 1: {
                    Tree tree;
                    cin >> tree;
                    addTree(tree);  // Sử dụng phương thức từ lớp TreeList
                    break;
                }
                case 2:
                    displayTrees();  // Sử dụng phương thức từ lớp TreeList
                    break;
                case 3:
                    sortTrees();  // Sử dụng phương thức từ lớp TreeList
                    cout << "DANH SACH CAY DA DUOC SAP XEP THEO CHIEU CAO .\n";
                    break;
                case 4: {
                    Tree tallest = findTallestTree();
                    cout << "CAY CAO NHAT : " << tallest << endl;
                    break;
                }
                case 5: {
                    Tree shortest = findShortestTree();
                    cout<<"CAY THAP NHAT : "<<shortest<<endl;
                }
                case 6: {
                    int id;
                    cout << "NHAP ID CAY MUON XOA : ";
                    cin >> id;
                    deleteTreeById(id);  // Sử dụng phương thức từ lớp TreeList
                    cout << "DA XOA CAY CO ID ID: " << id << endl;
                    break;
                }
                case 0:
                    cout << "THOAT CHUONG TRINH !.\n";
                    break;
                default:
                    cout << "LUA CHON KHONG HOP LE !.\n";
            }
        } while (check != 0);
    }
};

// Chương trình chính
int main() {
    App app;
    app.menu();
    return 0;
}
