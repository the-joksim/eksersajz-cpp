// Given an m x n 2D binary grid grid which represents a map of '1's (land) and
// '0's (water), return the number of islands.

// An island is surrounded by water and is formed by connecting adjacent lands
// horizontally or vertically. You may assume all four edges of the grid are all
// surrounded by water.

// Example 1:

// Input: grid = [
//["1","1","1","1","0"],
//["1","1","0","1","0"],
//["1","1","0","0","0"],
//["0","0","0","0","0"]
//]
// Output: 1

// Example 2:

// Input: grid = [
//["1","1","0","0","0"],
//["1","1","0","0","0"],
//["0","0","1","0","0"],
//["0","0","0","1","1"]
//]
// Output: 3

// Constraints:

// m == grid.length
// n == grid[i].length
// 1 <= m, n <= 300
// grid[i][j] is '0' or '1'.

#include "eksersajz/number_of_islands.hpp"
#include <deque>
#include <vector>

// Adjacency list for each "node" (m,n) (a '1' char) can be looked up by
// checking:
// - for nodes not lying on the grid boundary, we check if positions to the
//   - left, i.e. (m, n - 1),
//   - down, i.e. (m + 1, n),
//   - right, i.e. (m, n + 1), and
//   - up, i.e. (m - 1, n)
//  hold a '1'.
// - for nodes lying on the boundary, we assume that there's a '0' accross the
//   boundary
//
// We can initialize the "discovered" grid, which we'll use in the connected
// components part. Next, we traverse the grid, and do a bfs on each node. Each
// bfs should find all the nodes that belong to the component the node we're
// starting the bfs from belongs.
//
// Whenever we encounter an undiscovered node, we increase the number of
// components.

namespace {

class NumIslandsSolution {
private:
  const std::vector<std::vector<char>> &grid;

  const size_t rows = grid.size();
  const size_t columns = rows > 0 ? grid[0].size() : 0;

  std::vector<std::vector<bool>> visited{rows,
                                         std::vector<bool>(columns, false)};

  std::deque<std::tuple<int, int>> bfs_q{};

  bool should_process_node(const int i, const int j) const {
    return grid[i][j] == '1' and !visited[i][j];
  }

  void add_neighbors(const std::tuple<int, int> pos) {
    const auto &[i, j] = pos;

    if (j > 0 and should_process_node(i, j - 1)) {
      bfs_q.push_back({i, j - 1}); // left
    }

    if (i < (rows - 1) and should_process_node(i + 1, j)) {
      bfs_q.push_back({i + 1, j}); // down
    }

    if (j < (columns - 1) and should_process_node(i, j + 1)) {
      bfs_q.push_back({i, j + 1}); // right
    }

    if (i > 0 and should_process_node(i - 1, j)) {
      bfs_q.push_back({i - 1, j}); // up
    }
  }

  void bfs(std::tuple<int, int> pos) {
    bfs_q.push_front(pos);

    while (!bfs_q.empty()) {
      auto p = bfs_q.front();
      const auto &[i, j] = p;

      if (!visited[i][j]) {
        visited[i][j] = true;
      }

      add_neighbors(p);

      bfs_q.pop_front();
    }
  }

public:
  NumIslandsSolution(std::vector<std::vector<char>> &grid) : grid(grid) {}
  ~NumIslandsSolution() = default;

  int num_islands() {
    int c = 0;

    for (size_t i = 0; i < rows; i++) {
      for (size_t j = 0; j < columns; j++) {
        if (grid[i][j] == '0') {
          continue;
        }

        if (!visited[i][j]) {
          c++;
          bfs({i, j});
        }
      }
    }

    return c;
  }
};

} // namespace

int num_islands(std::vector<std::vector<char>> &grid) {
  auto solution = NumIslandsSolution(grid);
  return solution.num_islands();
}
