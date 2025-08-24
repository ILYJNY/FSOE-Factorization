#include <iterator>
#include <ctime>
#include "iostream"
#include "cmath"
#include "vector"


using namespace std;

struct prime_div {
    bool is_prime;
    unsigned long long int divisor;
};

struct panp {
    unsigned long long int P;
    unsigned long long int power;
};

long double log_a(long double a, long double b) {
    return log(b)/log(a);
}


unsigned long long int gcd(unsigned long long int a, unsigned long long int b) {
    int temp;
    if (a<b) {
        temp = a;
        a = b;
        b = temp;
    }
    int rest;
    while(b != 0) {
        rest = a%b;
        a = b;
        b = rest;
    }
    return a;

}

unsigned long long int exppow(unsigned long long int a, unsigned long long int b) {
    unsigned long long int result = 1;
    for (unsigned long long int i = 0;i<b;i++) result *= a;
    return result;
}



std::vector<unsigned long long int> element(std::vector<unsigned long long int> a) {
    std::vector<unsigned long long int> result = {a[0]};
    bool counter = false;
    for (unsigned long long & i : a) {
        for (unsigned long long & j : result) {
            if (i == j) counter = true;
        }
        if (!counter) result.push_back(i);
        counter = false;
    }
    return result;
}


//



prime_div is_prime_SOE(unsigned long long int a) {
    unsigned long long int b = 2;
    while (b<=sqrtl(a)) {
        if (a % b == 0) return {false, b};
        b++;
    }
    return {true, a};
}

std::vector<unsigned long long int> frac_SOEwith(unsigned long long int a) {
    prime_div aa = is_prime_SOE(a);
    unsigned long long int b = a;
    std::vector<unsigned long long int> return_1 = {};
    while (true) {
        if (aa.is_prime) {
            return_1.push_back(b);
            break;
        }
        return_1.push_back(aa.divisor);
        b = b / aa.divisor;
        aa = is_prime_SOE(b);
    }
    return element(return_1);
}






//finding powers to primes with log cal.
unsigned long long int frac_1(unsigned long long int a, unsigned long long int N) {
    unsigned long long int return_value = 0;
    unsigned long long int exp = floor(log_a(a, N));
    unsigned long long int counter = 0;
    while (true) {
        if (N % (exppow(a, counter)) != 0) {
            return_value = counter - 1;
            break;
        }
        counter++;
    }
    return return_value;
};

//일단은 이걸로 해봄



int main_FSOE() {
    clock_t start, end;
    long double duration;
    unsigned long long int N;
    cout << "Enter N(Max is 18446744073709551615 & 20 digits) :  ";
    cin >> N;
    start = clock();
    unsigned long long int a = 7;
    std::vector<unsigned long long int> primes = frac_SOEwith(N);
    vector<panp> sets_of_frac = {};
    while (not(empty(primes))) {
        a = primes.back();
        primes.pop_back();
        sets_of_frac.push_back({a, frac_1(a, N)});
    }
    std::vector<panp> sof_backup = sets_of_frac;
    for (int i = sets_of_frac.size() - 1;i >=0; i--) {
        cout << sets_of_frac[i].P;
        cout << "^";
        cout << sets_of_frac[i].power;
        if (i != 0) cout << " x ";
    }
    cout << endl;
    if (sets_of_frac.size() == 1) cout << "Prime" << endl;
    else cout << "Not Prime" << endl;
    end = clock();
    duration = (long double)(end - start) / CLOCKS_PER_SEC;
    cout << "Time : " << duration << "s" << endl;
    return 0;
}