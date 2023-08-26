#include "gtest/gtest.h"
#include "LifeModel.h"
#include "Figures.h"

//*****
//**+**
//**+**
//**+**
//*****

class LifeModelFixture: public ::testing::TestWithParam<Life::EngineType> {
protected:

    Life::LifeModel  model{5, 5};

};

TEST_P(LifeModelFixture, StickTest){

    model.setEngine(GetParam());

    auto stick = Life::makeStick(1, 2);
    for(auto& cell: stick){
        model.toggleCell(cell.first, cell.second);
    }

    int counter = 0;
    auto evenCounter = [&](){
        ++counter;
        if(counter == 100){
            model.stop();
        }
    };

    model.run(evenCounter);
    auto& data = model.readData();

    for(int i = 0; i < 5; ++i){
        for(int j = 0; j < 5; ++j){
            std::cout << (data(i,j) ? "+" : "*");
        }
        std::cout << std::endl;
    }

    ASSERT_TRUE(data(1, 2));
    ASSERT_TRUE(data(2, 2));
    ASSERT_TRUE(data(3, 2));
}

INSTANTIATE_TEST_SUITE_P(Engines,
                         LifeModelFixture,
                         ::testing::Values(
                         Life::EngineType::common, Life::EngineType::openmp, Life::EngineType::thread
                        ));



