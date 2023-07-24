#include "Figures.h"

Life::cellGroup Life::makeGlider(int row, int col) {
  return { {row,     col},
           {row + 1, col + 1},
           {row + 1, col + 2},
           {row + 2, col    },
           {row + 2, col + 1} };
}

Life::cellGroup Life::makeStick(int row, int col) {
  return { {row,     col},
           {row + 1, col},
           {row + 2, col} };
}

Life::cellGroup Life::makePond(int row, int col)
{
  return { {row,     col + 1},
           {row,     col + 2},
           {row + 3, col + 1},
           {row + 3, col + 2},

           {row + 1, col + 3},
           {row + 2, col + 3},
           {row + 1, col    },
           {row + 2, col    } };
}

Life::cellGroup Life::makeSquare(int row, int col)
{
  return { {row,     col    },
           {row,     col + 1},
           {row + 1, col    },
           {row + 1, col + 1} };
}

Life::cellGroup Life::makeToad(int row, int col)
{
  return { {row,     col + 1},
           {row,     col + 2},
           {row,     col + 3},
           {row + 1, col    },
           {row + 1, col + 1},
           {row + 1, col + 2}, };
}

Life::cellGroup Life::makeBoat(int row, int col)
{
  return { {row,     col    },
           {row,     col + 1},
           {row + 1, col    },
           {row + 1, col + 2},
           {row + 2, col + 1} };
}
