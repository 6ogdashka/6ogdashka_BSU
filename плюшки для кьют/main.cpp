#include <fstream>

int main() {
    std::ifstream in("med.txt", std::ios::binary);
    std::ofstream out("med.bin", std::ios::binary);
    
    if (in && out) {
        out << in.rdbuf();
    }
    
    return 0;
}