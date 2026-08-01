#include "GildedRose.h"

using namespace std;

GildedRose::GildedRose(vector<Item> & items) : items(items)
{}

namespace {
    constexpr int MIN_QUALITY = 0;
    constexpr int MAX_QUALITY = 50;
    constexpr int LEGENDARY_QUALITY = 80;
}

void GildedRose::updateQuality() 
{
    for ( auto& item : items )
    {
        if (item.name != "Aged Brie" && item.name != "Backstage passes to a TAFKAL80ETC concert")
        {
            if (item.quality > MIN_QUALITY)
            {
                if (item.name != "Sulfuras, Hand of Ragnaros")
                {
                    item.quality = item.quality - 1;
                }
            }
        }
        else
        {
            if (item.quality < MAX_QUALITY)
            {
                item.quality = item.quality + 1;

                if (item.name == "Backstage passes to a TAFKAL80ETC concert")
                {
                    if (item.sellIn < 11)
                    {
                        if (item.quality < MAX_QUALITY)
                        {
                            item.quality = item.quality + 1;
                        }
                    }

                    if (item.sellIn < 6)
                    {
                        if (item.quality < MAX_QUALITY)
                        {
                            item.quality = item.quality + 1;
                        }
                    }
                }
            }
        }

        if (item.name != "Sulfuras, Hand of Ragnaros")
        {
            item.sellIn = item.sellIn - 1;
        }

        if (item.sellIn < 0)
        {
            if (item.name != "Aged Brie")
            {
                if (item.name != "Backstage passes to a TAFKAL80ETC concert")
                {
                    if (item.quality > MIN_QUALITY)
                    {
                        if (item.name != "Sulfuras, Hand of Ragnaros")
                        {
                            item.quality = item.quality - 1;
                        }
                    }
                }
                else
                {
                    item.quality = item.quality - item.quality;
                }
            }
            else
            {
                if (item.quality < MAX_QUALITY)
                {
                    item.quality = item.quality + 1;
                }
            }
        }
    }
}