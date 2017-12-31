#include <array>
#include <iostream>
#include <vector>

const int puzzleSize = 3;
const int count = 17;
std::array<int, count> lengths = {
    {3, 3, 3, 3, 2, 2, 2, 3, 3, 2, 2, 3, 2, 3, 2, 2, 3}};

enum class Dir { XP, XN, YP, YN, ZP, ZN };

std::ostream &operator<<(std::ostream &os, Dir dir) {
  switch (dir) {
  case Dir::XP:
    os << "X+";
    break;

  case Dir::YP:
    os << "Y+";
    break;

  case Dir::XN:
    os << "X-";
    break;

  case Dir::YN:
    os << "Y-";
    break;

  case Dir::ZN:
    os << "Z-";
    break;

  case Dir::ZP:
    os << "Z+";
    break;
  }

  return os;
}

class Shape {
private:
  bool filled[puzzleSize][puzzleSize][puzzleSize];

public:
  Shape() { clear(); }

  Shape(Shape &s) {
    for (int i = 0; i < puzzleSize; i++) {
      for (int j = 0; j < puzzleSize; j++) {
        for (int k = 0; k < puzzleSize; k++) {
          filled[i][j][k] = s.filled[i][j][k];
        }
      }
    }
  }

  ~Shape() {}

  void clear() {
    for (int i = 0; i < puzzleSize; i++) {
      for (int j = 0; j < puzzleSize; j++) {
        for (int k = 0; k < puzzleSize; k++) {
          filled[i][j][k] = false;
        }
      }
    }
  }

  void addCube(int x, int y, int z) {
    if (0 <= x && x < puzzleSize && 0 <= y && y < puzzleSize && 0 <= z &&
        z < puzzleSize) {
      filled[x][y][z] = true;
    }
  }

  void removeCube(int x, int y, int z) {

    if (0 <= x && x < puzzleSize && 0 <= y && y < puzzleSize && 0 <= z &&
        z < puzzleSize) {
      filled[x][y][z] = false;
    }
  }

  inline bool cubeAt(int x, int y, int z) {
    if (0 <= x && x < puzzleSize && 0 <= y && y < puzzleSize && 0 <= z &&
        z < puzzleSize) {
      return filled[x][y][z];
    }
    return false;
  }

  void fill(int x, int y, int z, Dir dir, int len) {
    // std::cout << "Fill called: " << x << ' ' << y << ' ' << z << ' ' << dir
    // << ' ' << len << ";\n";

    switch (dir) {
    case Dir::XP: {
      int i = 1;
      for (; i < len; i++) {
        // std::cout << i << std::endl;
        // std::cout << x + i << ' ' << y <<' ' << z << std::endl;
        addCube(x + i, y, z);
      }

      break;
    }

    case Dir::XN: {

      int i = 1;
      for (; i < len; i++) {
        addCube(x - i, y, z);
      }

      break;
    }

    case Dir::YP: {

      int i = 1;
      for (; i < len; i++) {
        addCube(x, y + i, z);
      }

      break;
    }

    case Dir::YN: {

      int i = 1;
      for (; i < len; i++) {
        addCube(x, y - i, z);
      }

      break;
    }

    case Dir::ZP: {

      int i = 1;
      for (; i < len; i++) {
        addCube(x, y, z + i);
      }

      break;
    }

    case Dir::ZN: {

      int i = 1;
      for (; i < len; i++) {
        addCube(x, y, z - i);
      }

      break;
    }

    default:
      return;
    }
  }

  friend std::ostream &operator<<(std::ostream &os, Shape &s);
};

std::ostream &operator<<(std::ostream &os, Shape &s) {
  for (int i = 0; i < puzzleSize; i++) {
    for (int j = 0; j < puzzleSize; j++) {
      for (int k = 0; k < puzzleSize; k++) {
        if (s.filled[i][j][k]) {
          os << "# ";
        } else {
          os << ". ";
        }
      }
      os << '\n';
    }
    os << '\n';
  }

  return os;
}

inline bool inBoundsP(int coord) { return (coord < puzzleSize); }

inline bool inBoundsN(int coord) { return (coord >= 0); }

bool isFree(Shape &s, int x, int y, int z, Dir dir, int len) {
  bool valid = true;

  switch (dir) {
  case Dir::XP:

    for (int i = 1; i < len; i++) {
      if (!inBoundsP(x + i) || s.cubeAt(x + i, y, z)) {
        valid = false;
        break;
      }
    }

    break;

  case Dir::XN:

    for (int i = 1; i < len; i++) {
      if (!inBoundsN(x - i) || s.cubeAt(x - i, y, z)) {
        valid = false;
        break;
      }
    }

    break;

  case Dir::YP:

    for (int i = 1; i < len; i++) {
      if (!inBoundsP(y + i) || s.cubeAt(x, y + i, z)) {
        valid = false;
        break;
      }
    }

    break;

  case Dir::YN:

    for (int i = 1; i < len; i++) {
      if (!inBoundsN(y - i) || s.cubeAt(x, y - i, z)) {
        valid = false;
        break;
      }
    }
    break;

  case Dir::ZP:

    for (int i = 1; i < len; i++) {
      if (!inBoundsP(z + i) || s.cubeAt(x, y, z + i)) {
        valid = false;
        break;
      }
    }
    break;

  case Dir::ZN:

    for (int i = 1; i < len; i++) {
      if (!inBoundsN(z - i) || s.cubeAt(x, y, z - i)) {
        valid = false;
        break;
      }
    }
    break;

  default:
    return false;
  }

  return valid;
}

int projectX(int x, int len, Dir dir) {
  switch (dir) {
  case Dir::XP:
    return x + len - 1;

  case Dir::XN:
    return x - len + 1;

  default:
    return x;
  }
}

int projectY(int y, int len, Dir dir) {
  switch (dir) {
  case Dir::YP:
    return y + len - 1;

  case Dir::YN:
    return y - len + 1;

  default:
    return y;
  }
}

int projectZ(int z, int len, Dir dir) {
  switch (dir) {
  case Dir::ZP:
    return z + len - 1;

  case Dir::ZN:
    return z - len + 1;

  default:
    return z;
  }
}

std::vector<Dir> history = {Dir::XP};

int solutionCount = 0;

void recurse(int depth, Shape s, int x = 0, int y = 0, int z = 0,
             Dir dir = Dir::XP) {

  if (depth >= count) {
    solutionCount++;
    std::cout << "Solution:\n\n";
    std::cout << "Worm starts at 0, 0, 0 facing X+.\n";

    int index = 0;

    for (Dir &dir : history) {
      std::cout << "Travel " << lengths[index] << " units in direction " << dir
                << ".\n";
      index++;
    }

    std::cout << '\n';
    exit(0);
  }

  std::array<Dir, 4> nf;

  switch (dir) {
  case Dir::XP:
  case Dir::XN:

    nf = {{Dir::YP, Dir::YN, Dir::ZP, Dir::ZN}};
    break;

  case Dir::YP:
  case Dir::YN:

    nf = {{Dir::XP, Dir::XN, Dir::ZP, Dir::ZN}};
    break;

  case Dir::ZP:
  case Dir::ZN:

    nf = {{Dir::XP, Dir::XN, Dir::YP, Dir::YN}};
    break;

  default:
    break;
  }

  for (const Dir &testdir : nf) {
    int len = lengths[depth];
    if (isFree(s, x, y, z, testdir, len)) {
      Shape potentialNext = s;

      potentialNext.fill(x, y, z, testdir, len);

      history.push_back(testdir);
      recurse(depth + 1, potentialNext, projectX(x, len, testdir),
              projectY(y, len, testdir), projectZ(z, len, testdir), testdir);
      history.pop_back();
    }
  }
}

int main() {
  Shape k;
  k.addCube(0, 0, 0);

  recurse(0, k);
}
