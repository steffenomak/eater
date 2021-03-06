#include "eater/db.hpp"
#include "format.h"
#include "eater/sql.hpp"

namespace Eater
{

DB::DB() : food_items(nullptr)
{
}

DB::~DB()
{
    close();
}

bool DB::open(const std::string &data_base)
{
    if (db == nullptr) {
        LOGG_MESSAGE("shared db ptr null");
        db = std::shared_ptr<DB_Driver>(new Sql());
    }

    if (!db->open(data_base)) {
        LOGG_ERROR(__PRETTY_FUNCTION__);
        return false;
    }
    LOGG_MESSAGE("Opened databse: " << data_base);

    if (!init()) {
        LOGG_ERROR(__PRETTY_FUNCTION__ << " - WHAAAAAY!!!!!!!");

        return false;
    }

    return true;
}

bool DB::init()
{
    if (db == nullptr) {
        LOGG_ERROR(__PRETTY_FUNCTION__ << " - database pointer is null.");

        return false;
    }

    if (food_items == nullptr) {
        food_items = std::shared_ptr<TblFoodItems>(new TblFoodItems(db));
    }

    if (tags == nullptr) {
        tags = std::shared_ptr<TblTags>(new TblTags(db));
    }

    if (!food_items->init()) {
        LOGG_ERROR(__PRETTY_FUNCTION__ << " - failed to initialize table fooditems.");
        return false;
    }

    if (!tags->init()) {
        LOGG_ERROR(__PRETTY_FUNCTION__ << " - failed to initialize table tags.");
        return false;
    }

    LOGG_MESSAGE("Init was successfull.");

    return true;
}

void DB::close()
{
    food_items->close();
    food_items.reset();
    tags->close();
    tags.reset();
    db->close();
    db.reset();
}

} /* Eater */
