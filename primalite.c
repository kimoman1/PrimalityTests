#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <assert.h>

long long int gcd(long long int a, long long int b) {
    while (b != 0) {
        long long int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int jacobi(int a, int n) {
    assert(n > 0 && n%2 == 1);
    a = (a % n + n) % n;
    int t = 0;
    while (a != 0) {
        while (a % 4 == 0)
            a /= 4;
        if (a % 2 == 0) {
            t ^= n;
            a /= 2;
        }
        t ^= a & n & 2;
        int r = n % a;
        n = a;
        a = r;
    }
    if (n != 1)
        return 0;
    else if ((t ^ (t >> 1)) & 2)
        return -1;
    else
        return 1;
}


long long int mod_pow(long long int base, long long int exp, long long int mod) {
    long long int result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) { 
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}


int solovayStrassen(long long int n, int k) {
    if (n < 2) return 0;
    if (n == 2) return 1;
    if (n % 2 == 0) return 0;

    for (int i = 0; i < k; i++) {
        long long int bi = rand() % (n - 1) + 1;

        if (gcd(n, bi) != 1) {
            return 0;
        }

        int jacobiSymbol = jacobi(bi, n) % n;
        long long int modResult = mod_pow(bi, (n - 1) / 2, n);

        if (jacobiSymbol < 0) {
            jacobiSymbol += n;
        }

        if (jacobiSymbol != modResult) {
            return 0;
        }
    }

    return 1;
}


int naive(long long int n) {
    if (n <= 1) {
        return 0;
    }

    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) {
            return 0;
        }
    }

    return 1;
}

int fermatPrime(long long int n, int k){
    if (n <= 1) {
        return 0;
    }

    srand(time(NULL));

    for (int i = 0; i < k; i++) {

        long long ai = rand() % (n - 1) + 1;
        long long result = mod_pow(ai, n - 1, n);
        if (result != 1) {
            return 0;
        }
    }

    return 1;
}


int millerTest(long long n, long long d, long long a) {
    long long x = mod_pow(a, d, n);
    if (x == 1 || x == n - 1) {
        return 1;
    }
    while (d != n - 1) {
        x = (x * x) % n;
        d *= 2;

        if (x == 1) return 0;
        if (x == n - 1) return 1;
    }

    return 0;
}

int rabinMiller(long long n, int k) {
    if (n <= 1) return 0;
    if (n <= 3) return 1;
    if (n % 2 == 0) return 0;

    long long d = n - 1;
    int r = 0;
    while (d % 2 == 0) {
        d /= 2;
        r++;
    }

    for (int i = 0; i < k; i++) {
        long long a = rand() % (n - 4) + 2;
        if (!millerTest(n, d, a)) {
            return 0;
        }
    }

    return 1;
}

int main() {
    for (int i=2; i<10000000; i++){
        if (rabinMiller(i, 10) != naive(i)){
            printf("%d is %d \n", i, naive(i));
            printf("Fermat says it's %d \n", fermatPrime(i, 10));
            printf("Solovay-Strassen says it's %d \n", solovayStrassen(i, 10));
            printf("Rabin-Miller says it's %d \n", rabinMiller(i, 10));

    }}
    return 0;
}