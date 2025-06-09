# Sudoku Solver (Enhanced Backtracking with Bitmask Optimization)

This C++ implementation combines backtracking with bitmask techniques to efficiently solve 9×9 Sudoku puzzles. Here's a detailed breakdown:

### Core Algorithm
**Bitmask Constraints Tracking**
- `takenRow[i]`: Bitmask for row `i` (bit 5 set = number 5 present)
- `takenCol[j]`: Bitmask for column `j`
- `takenGrid[i/3][j/3]`: Bitmask for 3×3 subgrid
- **Example**: If row 0 contains {1,3,5}, `takenRow[0] = 0b101010` (bits 1,3,5 set)

**Key Optimization: O(1) Validity Check**

```ruby
int getchoices(int row, int col) {
  int taken = takenRow[row] | takenCol[col] | takenGrid[row/3][col/3];
  return ((0x3FE ^ taken) & ~1); // 0x3FE = binary 1111111110 (bits 1-9)
}
```

### Execution Flow
1. **Input Handling** (`solve()`):
   - Reads 81 space-separated values (0 = empty)
   - Initializes constraints using `makemove()`

2. **Recursive Solver** (`rec()`):
   - Processes cells left-to-right, top-to-bottom
   - At each empty cell:
     - Generates valid numbers via bitmask
     - Tries numbers from LSB to MSB (1-9)
     - Backtracks immediately on invalid paths

3. **State Management**:
   - `makemove(ch, r, c)`:
     - Sets `board[r][c] = ch`
     - Toggles bit `ch` in row/column/grid masks using XOR
   - `revertmove()`: Exactly reverses `makemove()`

### Performance Characteristics
- **Space**: O(1) - fixed-size arrays (no heap allocation)
- **Time**: O(9^(n)) worst case (n = empty cells), but:
  - Bitmask pruning reduces branching factor
  - Early invalid path termination
  - Typical 9×9 puzzles solve instantly

### Advanced Features
- **Multiple Solution Detection**:
  - Continues searching after finding solutions
  - `ans` counter tracks total solutions
- **Efficient Grid Indexing**:
  - Subgrid calculated via integer division (`row/3`, `col/3`)
  
### Limitations
- **Fixed Size**: Hardcoded for 9×9 grids
- **No Input Validation**: Assumes valid initial puzzle
- **Printing Overhead**: Solution printing dominates runtime for hard puzzles

### Optimization Insights
1. **Bitwise Operations**:
   - Mask operations use native CPU instructions
   - ~3x faster than array-based checks
2. **Register-Friendly Data**:
   - Bitmask arrays fit in CPU cache
3. **Branch Prediction**:
   - LSB-first iteration benefits from sorted grids

Compile with `-O2` for automatic loop unrolling and inlining optimizations. For extreme puzzles, consider disabling solution printing.
