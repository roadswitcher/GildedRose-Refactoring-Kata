#include <catch2/catch_all.hpp>
#include "GildedRose.h"

TEST_CASE("Fix default unit test to verify unit tests/gcovr")
{
    std::vector<Item> items;
    items.push_back(Item("Dave's Arbitrary Item", 0, 0));
    GildedRose app(items);
    app.updateQuality();
    REQUIRE("Dave's Arbitrary Item" == app.items[0].name);
}
