#include "gtest/gtest.h"
#include "Cell.h"

const int minimumNeighboursToComeALive = Life::lifeThreshold;
const int minimumNeighboursToLive = Life::minimumNeighboursToLive;
const int maximumNeighboursToLive = Life::lifeThreshold;

TEST(CellState, initState){
  Life::Cell cell;
  EXPECT_EQ(bool(cell), false);
}

TEST(CellState, toggleState){
  Life::Cell cell;
  EXPECT_EQ(cell.toggle(), true);
  EXPECT_EQ(bool(cell), true);

  EXPECT_EQ(cell.toggle(), false);
  EXPECT_EQ(bool(cell), false);
}

TEST(CellLifeRules, comeAliveFromDust){
  Life::Cell cell;
  for(int i = 0; i < minimumNeighboursToComeALive; ++i) {
    cell.increment();
  }

  cell.evolute();
  EXPECT_EQ(bool(cell), true);
}

TEST(CellLifeRules, liveItLifeMin){
  Life::Cell cell;

  cell.renew();
  for(int i = 0; i < minimumNeighboursToLive; ++i) {
    cell.increment();
  }
  cell.evolute();

  EXPECT_EQ(bool(cell), true);
}

TEST(CellLifeRules, liveItLifeMax){
  Life::Cell cell;

  cell.renew();
  for(int i = 0; i < maximumNeighboursToLive; ++i) {
    cell.increment();
  }
  cell.evolute();

  EXPECT_EQ(bool(cell), true);
}

TEST(CellLifeRules, dieInLoneliness){
  Life::Cell cell;

  cell.renew();
  for(int i = 0; i < minimumNeighboursToLive - 1; ++i) {
    cell.increment();
  }
  cell.evolute();

  EXPECT_EQ(bool(cell), false);
}

TEST(CellLifeRules, dieInCrowd){
  Life::Cell cell;

  cell.renew();
  for(int i = 0; i < maximumNeighboursToLive + 1; ++i) {
    cell.increment();
  }
  cell.evolute();

  EXPECT_EQ(bool(cell), false);
}

TEST(CellLifeRules, reborn){
  Life::Cell cell;
  for(int i = 0; i < minimumNeighboursToComeALive; ++i) {
    cell.increment();
  }
  cell.evolute();

  ASSERT_EQ(bool(cell), true) << "Cell birthday Failed";

  for(int i = 0; i < maximumNeighboursToLive + 1; ++i) {
    cell.increment();
  }
  cell.evolute();

  ASSERT_EQ(bool(cell), false) << "Cell death Failed";

  for(int i = 0; i < minimumNeighboursToComeALive; ++i) {
    cell.increment();
  }

  cell.evolute();
  ASSERT_EQ(bool(cell), true) << "Cell reborn Failed";
}
