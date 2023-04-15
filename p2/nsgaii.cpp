#include <iostream>
#include <vector>
#include <algorithm>

struct Solution {
    std::vector<int> objectives;
    int rank;
    double crowding_distance;
};

bool dominates(const Solution& s1, const Solution& s2) {
    bool at_least_one_better = false;
    for (size_t i = 0; i < s1.objectives.size(); ++i) {
        if (s1.objectives[i] < s2.objectives[i]) {
            at_least_one_better = true;
        } else if (s1.objectives[i] > s2.objectives[i]) {
            return false;
        }
    }
    return at_least_one_better;
}

void fast_non_dominated_sort(std::vector<Solution>& solutions) {
    std::vector<std::vector<int>> S(solutions.size());
    std::vector<int> n(solutions.size());
    std::vector<std::vector<int>> F;
    for (size_t i = 0; i < solutions.size(); ++i) {
        for (size_t j = 0; j < solutions.size(); ++j) {
            if (dominates(solutions[i], solutions[j])) {
                S[i].push_back(j);
            } else if (dominates(solutions[j], solutions[i])) {
                ++n[i];
            }
        }
        if (n[i] == 0) {
            solutions[i].rank = 0;
            F[0].push_back(i);
        }
    }
    int i = 0;
    while (!F[i].empty()) {
        std::vector<int> Q;
        for (int p : F[i]) {
            for (int q : S[p]) {
                --n[q];
                if (n[q] == 0) {
                    solutions[q].rank = i + 1;
                    Q.push_back(q);
                }
            }
        }
        ++i;
        F.push_back(Q);
    }
}

void crowding_distance_assignment(std::vector<Solution>& solutions, int rank) {
    int num_objectives = solutions[0].objectives.size();
    for (int i = 0; i < num_objectives; ++i) {
        std::sort(solutions.begin(), solutions.end(),
                  [=](const Solution& s1, const Solution& s2) {
                      return s1.objectives[i]
