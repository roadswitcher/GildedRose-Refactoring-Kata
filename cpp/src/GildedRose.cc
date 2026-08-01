#include "GildedRose.h"

#include <algorithm>
#include <array>

using namespace std;

GildedRose::GildedRose(vector<Item>& items) : items(items) {}

namespace {
constexpr int MIN_QUALITY = 0;
constexpr int MAX_QUALITY = 50;
constexpr int LEGENDARY_QUALITY = 80;

void increase_quality(Item& item, int delta = 1) {
  if (item.quality < MAX_QUALITY) item.quality += delta;
}

void decrease_quality(Item& item, int delta = -1) {
  if (item.quality > MIN_QUALITY) item.quality += delta;
}

bool isAgedBrie(const Item& item) { return item.name == "Aged Brie"; }

bool isSulfuras(const Item& item) {
  return item.name == "Sulfuras, Hand of Ragnaros";
}

bool isBackstagePass(const Item& item) {
  return item.name == "Backstage passes to a TAFKAL80ETC concert";
}

}  // namespace

void GildedRose::updateQuality() {
  for (auto& item : items) {
    if (!isAgedBrie(item) && !isBackstagePass(item)) {
      if (item.quality > MIN_QUALITY) {
        if (!isSulfuras(item)) {
          item.quality = item.quality - 1;
        }
      }
    } else {
      if (item.quality < MAX_QUALITY) {
        item.quality = item.quality + 1;

        if (isBackstagePass(item)) {
          if (item.sellIn < 11) {
            increase_quality(item);
          }

          if (item.sellIn < 6) {
            increase_quality(item);
          }
        }
      }
    }

    if (!isSulfuras(item)) {
      item.sellIn = item.sellIn - 1;
    }

    if (item.sellIn < 0) {
      if (!isAgedBrie(item)) {
        if (!isBackstagePass(item)) {
          if (!isSulfuras(item)) {
            decrease_quality(item);
          }
        } else {
          item.quality = item.quality - item.quality;
        }
      } else {
        increase_quality(item);
      }
    }
  }
}