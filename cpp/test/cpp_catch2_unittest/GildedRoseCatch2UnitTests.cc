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

// - Once the sell by date has passed, `Quality` degrades twice as fast
TEST_CASE("Once the sell by date has passed, Quality degrades twice as fast") {
  std::vector<Item> items;
  items.push_back(Item("Foo", 0, 10));
  GildedRose app(items);
  app.updateQuality();
  REQUIRE(8 == app.items[0].quality);
  REQUIRE(-1 == app.items[0].sellIn);
}
// - The `Quality` of an item is never negative
// - __"Aged Brie"__ actually increases in `Quality` the older it gets
// - The `Quality` of an item is never more than `50`
// - __"Sulfuras"__, being a legendary item, never has to be sold or decreases in `Quality`
// - __"Backstage passes"__, like aged brie, increases in `Quality` as its `SellIn` value approaches;
//     - `Quality` increases by `2` when there are `10` days or less and by `3` when there are `5` days or less but
//     - `Quality` drops to `0` after the concert

// We have recently signed a supplier of conjured items. This requires an update to our system:

// - __"Conjured"__ items degrade in `Quality` twice as fast as normal items