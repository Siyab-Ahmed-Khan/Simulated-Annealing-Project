#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <algorithm>
#include <numeric>
#include <chrono>

using namespace std;

using Coord = pair<double, double>;

// Calculate the total distance of a given route
double totalDistance(const vector<Coord>& coords, const vector<int>& route) {
    double dist = 0;
    int n = route.size();
    for (int i = 0; i < n; ++i) {
        auto [x1, y1] = coords[route[i]];
        auto [x2, y2] = coords[route[(i + 1) % n]];
        dist += hypot(x1 - x2, y1 - y2);
    }
    return dist;
}

// Perform one simulated annealing run and return the best route found
vector<int> simulatedAnnealing(
    const vector<Coord>& coords,
    double T0,            // Initial temperature
    double alpha,         // Cooling rate (0 < alpha < 1)
    double T_min,         // Minimum temperature to stop
    int iterPerTemp,      // Iterations per temperature step
    double& outBestDist   // Output: distance of best route
) {
    int n = coords.size();
    mt19937 rng(random_device{}());
    uniform_real_distribution<> randReal(0.0, 1.0);

    // Create initial random route [0,1,2,...,n-1]
    vector<int> current(n), best;
    iota(current.begin(), current.end(), 0);
    shuffle(current.begin(), current.end(), rng);
    best = current;
    double bestDist = totalDistance(coords, best);
    double T = T0;

    // Main annealing loop
    while (T > T_min) {
        for (int iter = 0; iter < iterPerTemp; ++iter) {
            // Generate neighbor by swapping two random positions
            vector<int> candidate = current;
            int i = rng() % n;
            int j = rng() % n;
            swap(candidate[i], candidate[j]);

            double currDist = totalDistance(coords, current);
            double candDist = totalDistance(coords, candidate);
            double delta = candDist - currDist;

            // Accept better solutions or worse ones with probability exp(-delta/T)
            if (delta < 0 || randReal(rng) < exp(-delta / T)) {
                current = candidate;
                if (candDist < bestDist) {
                    bestDist = candDist;
                    best = candidate;
                }
            }
        }
        T *= alpha;  // Cool down
    }
    outBestDist = bestDist;
    return best;
}

int main() {
    const int n = 20;               // Number of stops
    vector<Coord> coords(n);

    // Generate example random coordinates in a 100x100 area
    mt19937 rng(42);
    uniform_real_distribution<> dist100(0.0, 100.0);
    for (auto& p : coords) {
        p = {dist100(rng), dist100(rng)};
    }

    // Parameters for Simulated Annealing
    const double T0 = 1000.0;
    const double alpha = 0.95;
    const double T_min = 1.0;
    const int iterPerTemp = 1000;

    // Measure execution time
    auto start = chrono::high_resolution_clock::now();
    double bestDist;
    auto bestRoute = simulatedAnnealing(coords, T0, alpha, T_min, iterPerTemp, bestDist);
    auto end = chrono::high_resolution_clock::now();

    // Output results
    cout << "===== Simulated Annealing: Delivery Route Optimization =====" << endl;
    cout << "Best Distance Found: " << bestDist << " units" << endl;
    cout << "Optimal Route Order: ";
    for (int idx : bestRoute) {
        cout << idx << ' ';
    }
    cout << endl;

    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << "Computation Time: " << duration << " ms" << endl;

    return 0;
}