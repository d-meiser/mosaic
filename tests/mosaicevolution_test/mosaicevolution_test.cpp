#include <gtest/gtest.h>
#include <mosaicevolution.h>
#include <mosaicmodel.h>
#include <mosaicupdate.h>
#include <tile.h>
#include <targetimage.h>


TEST(MoMosaicEvolution, CanBeConstructed) {
    MoMosaicEvolution* evolution = new MoMosaicEvolution;
    ASSERT_NE(evolution, nullptr);
    delete evolution;
}

struct MosaicEvolution : public ::testing::Test {
    MoMosaicEvolution evolution;
};

TEST_F(MosaicEvolution, ModelIsEmptyBeforeSettingInitialState) {
    MoMosaicModel* model = evolution.getCurrentModel();
    ASSERT_EQ(0, model->size());
}

TEST_F(MosaicEvolution, CanTakeStepWithoutUpdaters) {
    ASSERT_NO_THROW(evolution.takeStep());
}

TEST_F(MosaicEvolution, CanAddUpdate) {
    std::unique_ptr<MoMosaicUpdate> update(new MoMosaicUpdate);
    ASSERT_NO_THROW(evolution.addUpdate(std::move(update)));
}

TEST_F(MosaicEvolution, IdentityUpdateDoesNotChangeModel) {
    std::unique_ptr<MoMosaicUpdate> update(new MoMosaicUpdate);
    evolution.addUpdate(std::move(update));
    std::vector<MoTile> tiles;
    evolution.constructInitialState(MoTargetImage(),
                                    tiles);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
