#include<bits/stdc++.h>
#define endl "\n"
using namespace std;
#ifdef ENABLE_TIMING
    #include<chrono>
    using namespace std::chrono;
    auto start = high_resolution_clock::now();
    auto stop = high_resolution_clock::now();
    auto durat = duration_cast<nanoseconds>(stop - start);
#endif
int main() {
    cin.tie(0)->sync_with_stdio(0);
    cout.tie(0);
    #ifdef ENABLE_TIMING
        start = high_resolution_clock::now();
    #endif
    
    cout << "Hello, World!" << endl;

    #ifdef ENABLE_TIMING
        stop = high_resolution_clock::now();
        durat = duration_cast<nanoseconds>(stop - start);
        cout << "\nTotal time taken: " << double (durat.count())/1000000.0 << " ms.\n";
    #endif

    return 0;
}