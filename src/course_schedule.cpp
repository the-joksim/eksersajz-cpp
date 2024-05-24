// There are a total of numCourses courses you have to take, labeled from 0 to
// numCourses - 1. You are given an array prerequisites where prerequisites[i] =
// [ai, bi] indicates that you must take course bi first if you want to take
// course ai.

// For example, the pair [0, 1], indicates that to take course 0 you have to
// first take course 1.

// Return true if you can finish all courses. Otherwise, return false.

// Example 1:

// Input: numCourses = 2, prerequisites = [[1,0]]
// Output: true
// Explanation: There are a total of 2 courses to take.
// To take course 1 you should have finished course 0. So it is possible.

// Example 2:

// Input: numCourses = 2, prerequisites = [[1,0],[0,1]]
// Output: false
// Explanation: There are a total of 2 courses to take.
// To take course 1 you should have finished course 0, and to take course 0 you
// should also have finished course 1. So it is impossible.

// Constraints:

// 1 <= numCourses <= 2000
// 0 <= prerequisites.length <= 5000
// prerequisites[i].length == 2
// 0 <= ai, bi < numCourses
// All the pairs prerequisites[i] are unique.

#include "eksersajz/course_schedule.hpp"
#include "eksersajz/utils.hpp"

/*  Idea:
 *    - a cycle indicates that the requirements are impossible to satisfy
 *    - build a graph from the adjacency list (Q: is building the graph
 * necessary?)
 *    - the graph should be a tree => no cycles!
 *    - try the dfs with cycle detection approach (see Skiena)
 */

using Prereqs = std::vector<std::vector<int>>;

namespace {

class CourseDeps {
public:
  CourseDeps(int num_courses, const Prereqs &prereqs)
      : num_courses(num_courses), prereqs(prereqs) {
    discovered = processed = std::vector<bool>(num_courses, false);
    parent = std::vector<int>(num_courses, -1);
  }

  bool can_be_fulfilled() {
    // do a dfs with back edge detection starting on course
    std::vector<int> dfs_stack{};

    for (int i = 0; i < num_courses; i++) {

      dfs_stack.push_back(i);

      while (!dfs_stack.empty()) {
        auto node = dfs_stack.back();
        dfs_stack.pop_back();

        auto course_prereqs = get_course_prereqs(node);

        for (const auto &p : course_prereqs) {
          auto neighbor = p[1];

          if (!discovered[neighbor]) {
            discovered[neighbor] = true;
            parent[neighbor] = node;

            process_edge(p);

            dfs_stack.push_back(neighbor);
          } else if ((!processed[neighbor] && (parent[node] != neighbor)) ||
                     directed) {
            process_edge(p);
          }

          if (traversal_terminated) {
            return !has_cycle;
          }
        }
      }

      processed[i] = true;
    }

    return !has_cycle;
  }

private:
  int num_courses{0};
  Prereqs prereqs{};

  std::vector<int> parent{};
  std::vector<bool> discovered{};
  std::vector<bool> processed{};

  bool directed{true};
  bool has_cycle{false};
  bool traversal_terminated{false};

  void process_edge(const std::vector<int> &edge) {
    assert(edge.size() == 2);
    if (parent[edge[1]] != edge[0]) {
      has_cycle = true;
      traversal_terminated = true;
    }
  }

  Prereqs get_course_prereqs(int course) {
    assert(course < num_courses);

    auto course_prereqs = Prereqs{};

    for (const auto &p : prereqs) {
      if (p[0] == course) {
        course_prereqs.push_back(p);
      }
    }

    return course_prereqs;
  }
};

} // namespace

bool can_finish(int num_courses, const Prereqs &prereqs) {
  auto course_deps = CourseDeps{num_courses, prereqs};
  return course_deps.can_be_fulfilled();
}
