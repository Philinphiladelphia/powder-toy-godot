// test/src/powder_toy_interface_test.cpp
#include <gtest/gtest.h>
#include "powder_toy_interface.h"

class PowderToyInterfaceTest : public ::testing::Test {
protected:
    // right now, this just runs a copy of the powder toy. I need to have frame by frame control

    void SetUp() override {
        // Add any necessary setup code here
    }

    void TearDown() override {
        // Add any necessary teardown code here
    }
};

TEST_F(PowderToyInterfaceTest, ActuallyProcessesParticles) {
    PowderToyInterface pti;
    PowderCircle circle = {10, 10, 5, 49}; // Example circle
    EXPECT_NO_THROW(pti.MakeCircle(circle));

    pti.RunSimFrame();

    int parts_array[XRES * YRES];
    pti.GetParticles(parts_array);
    
    int sum = 0;
    for (int i = 0; i < XRES*YRES; i++)
    {
        sum += parts_array[i];
    }

    std::cout << "Sum of particles: " << sum << std::endl;

}