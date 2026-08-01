#include <catch2/catch_all.hpp>

#include "GildedRose.h"

TEST_CASE("Fix default unit test to verify unit tests/gcovr") {
  std::vector<Item> items;
  items.push_back(Item("Dave's Arbitrary Item", 0, 0));
  GildedRose app(items);
  app.updateQuality();
  REQUIRE("Dave's Arbitrary Item" == app.items[0].name);
}

TEST_CASE("Once the sell by date has passed, Quality degrades twice as fast") {
  std::vector<Item> items;
  items.push_back(Item("Foo", 0, 10));
  GildedRose app(items);
  app.updateQuality();
  REQUIRE(8 == app.items[0].quality);
  REQUIRE(-1 == app.items[0].sellIn);
}

TEST_CASE("The Quality of an item is never negative") {
  std::vector<Item> items;
  items.push_back(Item("Foo", 5, 1));
  GildedRose app(items);
  app.updateQuality();
  app.updateQuality();
  REQUIRE(app.items[0].quality == 0);
}

TEST_CASE("Aged Brie actually increases in Quality the older it gets") {
  std::vector<Item> items;
  items.push_back(Item("Aged Brie", 38, 1));
  GildedRose app(items);
  app.updateQuality();
  REQUIRE(2 == app.items[0].quality);
}

// NOTE:
// The original requirements.md file never calls out this behavior explicitly
// It's legacy code, the code is the documentation, therefore refactors should
// probably preserve behavior until a stakeholder weighs in.
TEST_CASE("Aged Brie increases in Quality twice as fast once expired") {
  std::vector<Item> items;
  items.push_back(Item("Aged Brie", 0, 10));
  GildedRose app(items);
  app.updateQuality();
  REQUIRE(12 == app.items[0].quality);
  REQUIRE(-1 == app.items[0].sellIn);
}

TEST_CASE("The Quality of an item is never more than 50") {
  std::vector<Item> items;
  items.push_back(Item("Aged Brie", 48, 48));
  GildedRose app(items);
  app.updateQuality();
  REQUIRE(49 == app.items[0].quality);
  app.updateQuality();
  REQUIRE(50 == app.items[0].quality);
  app.updateQuality();
  REQUIRE(50 == app.items[0].quality);
}

TEST_CASE("Sulfuras never has to be sold or decreases in Quality") {
  std::vector<Item> items;
  items.push_back(Item("Sulfuras, Hand of Ragnaros", 5, 80));
  items.push_back(Item("Sulfuras, Hand of Ragnaros", 0, 80));
  GildedRose app(items);
  app.updateQuality();
  REQUIRE(5 == app.items[0].sellIn);
  REQUIRE(80 == app.items[0].quality);
  REQUIRE(0 == app.items[1].sellIn);
  REQUIRE(80 == app.items[1].quality);
}

TEST_CASE(
    "Backstage passes increase in Quality as SellIn approaches at normal "
    "rate") {
  std::vector<Item> items;
  items.push_back(Item("Backstage passes to a TAFKAL80ETC concert", 15, 20));
  GildedRose app(items);
  app.updateQuality();
  REQUIRE(21 == app.items[0].quality);
  REQUIRE(14 == app.items[0].sellIn);
}

TEST_CASE("Backstage passes increase in Quality by 2 at sellin <= 10 days") {
  std::vector<Item> items;
  items.push_back(Item("Backstage passes to a TAFKAL80ETC concert", 10, 20));
  GildedRose app(items);
  app.updateQuality();
  REQUIRE(22 == app.items[0].quality);
  REQUIRE(9 == app.items[0].sellIn);
}

TEST_CASE("Backstage passes increase in Quality by 3 at sellin <= 5 days") {
  std::vector<Item> items;
  items.push_back(Item("Backstage passes to a TAFKAL80ETC concert", 5, 20));
  GildedRose app(items);
  app.updateQuality();
  REQUIRE(23 == app.items[0].quality);
  REQUIRE(4 == app.items[0].sellIn);
}

TEST_CASE("Backstage passes drop to zero quality after concert") {
  std::vector<Item> items;
  items.push_back(Item("Backstage passes to a TAFKAL80ETC concert", 0, 20));
  GildedRose app(items);
  app.updateQuality();
  REQUIRE(0 == app.items[0].quality);
  REQUIRE(-1 == app.items[0].sellIn);
}

TEST_CASE("Conjured items degrade in quality twice as fast as normal items") {
  std::vector<Item> items;
  items.push_back(Item("Conjured Mana Cake", 5, 10));
  items.push_back(Item("Standard Totally Normal Item", 5, 10));
  GildedRose app(items);
  app.updateQuality();
  REQUIRE(8 == app.items[0].quality);
  REQUIRE(9 == app.items[1].quality);
}