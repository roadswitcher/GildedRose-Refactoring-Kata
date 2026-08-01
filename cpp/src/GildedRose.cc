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

bool itemAgesNormally(Item& item) {
  return !isAgedBrie(item) && !isBackstagePass(item) && !isSulfuras(item);
}

int backstagePassQualityDelta(const Item& pass) {
  // drop to zero after concert
  if (pass.sellIn < 0) {
    return -pass.quality;
  }
  if (pass.sellIn <= 5) {
    return 3;
  }
  if (pass.sellIn <= 10) {
    return 2;
  }
  return 1;
}

void updateItemQuality(Item& item) {
  if (itemAgesNormally(item)) {
    decrease_quality(item);
  } else {
    if (item.quality < MAX_QUALITY) {
      auto delta =
          (isBackstagePass(item)) ? backstagePassQualityDelta(item) : 1;

      item.quality = item.quality + delta;
    }
  }
}

void updateSellIn(Item& item) {
  if (!isSulfuras(item)) item.sellIn--;
}

}  // namespace

void GildedRose::updateQuality() {
  for (auto& item : items) {
    updateItemQuality(item);

    updateSellIn(item);

    if (item.sellIn < 0) {
      if (!isAgedBrie(item)) {
        if (!isBackstagePass(item)) {
          if (!isSulfuras(item)) {
            decrease_quality(item);
          }
        } else {
          item.quality = 0;
        }
      } else {
        increase_quality(item);
      }
    }
  }
}