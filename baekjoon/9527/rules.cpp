#include <iostream>
using namespace std;

long long countTotalOnes(long long n) {
    long long count = 0;
    for (long long i = 1; i <= n; i <<= 1) {
        long long fullCycles = n / (i << 1);
        long long remainder = n % (i << 1);

        count += fullCycles * i;
        if (remainder >= i) count += remainder - i + 1;
    }
    return count;
}

int main() {
    long long a, b;
    cin >> a >> b;

    long long result = countTotalOnes(b) - countTotalOnes(a - 1);
    cout << result << endl;
    return 0;
}
