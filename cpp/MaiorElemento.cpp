#include <iostream>

void stdoutMaiorInput(int n) {
    int i, input, maior, maior_index;
    std::cin >> maior;
    maior_index = 0;
    for (i = 1; i < n; i++){
        std::cin >> input;
        if (input > maior) {
            maior = input;
            maior_index = i;
        }
    }

    std::cout << maior_index << ' ' << maior << std::endl;
}

int main() {
    int n;

    while (std::cin >> n && n != 0) {
        stdoutMaiorInput(n);
    }
    
    return 0;
}