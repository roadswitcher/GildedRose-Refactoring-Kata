#include "GildedRose.h"

#include <algorithm>

using namespace std;

GildedRose::GildedRose(vector<Item>& items) : items(items) {}

namespace {
constexpr int MIN_QUALITY = 0;
constexpr int MAX_QUALITY = 50;
constexpr int LEGENDARY_QUALITY = 80;

void increase_quality(Item& item, int delta = 1) {
  if (item.quality < MAX_QUALITY)
    item.quality = std::min(MAX_QUALITY, item.quality + delta);
}

void decrease_quality(Item& item, int delta = 1) {
  if (item.quality > MIN_QUALITY)
    item.quality = std::max(MIN_QUALITY, item.quality - delta);
}

bool isAgedBrie(const Item& item) { return item.name == "Aged Brie"; }

bool isSulfuras(const Item& item) {
  return item.name == "Sulfuras, Hand of Ragnaros";
}

bool isBackstagePass(const Item& item) {
  return item.name == "Backstage passes to a TAFKAL80ETC concert";
}

bool isConjuredItem(const Item& item) {
  return item.name == "Conjured Mana Cake";
}

bool itemAgesNormally(Item& item) {
  return !isAgedBrie(item) && !isBackstagePass(item) && !isSulfuras(item) &&
         !isConjuredItem(item);
}

int backstagePassUpdateQualityDelta(const Item& pass) {
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
  } else if (isConjuredItem(item)) {
    decrease_quality(item, 2);
  } else if (isSulfuras(item)) {
    // no-op
  } else {
    // Handle backstage pass
    auto delta =
        (isBackstagePass(item)) ? backstagePassUpdateQualityDelta(item) : 1;

    increase_quality(item, delta);
  }
}

void updateSellIn(Item& item) {
  if (!isSulfuras(item)) item.sellIn--;
}

void handleExpirationBehavior(Item& item) {
  if (item.sellIn >= 0) return;

  if (isAgedBrie(item)) {
    increase_quality(item);
  } else if (isSulfuras(item)) {
    // no-op
  } else if (isBackstagePass(item)) {
    item.quality = 0;
  } else if (isConjuredItem(item)) {
    decrease_quality(item, 2);
  } else {
    decrease_quality(item);
  }
}

}  // namespace

void GildedRose::updateQuality() {
  for (auto& item : items) {
    updateItemQuality(item);

    updateSellIn(item);

    handleExpirationBehavior(item);
  }
}