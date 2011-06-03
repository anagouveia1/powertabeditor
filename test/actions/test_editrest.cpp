#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>

#include <actions/editrest.h>
#include <powertabdocument/position.h>
#include <powertabdocument/note.h>

BOOST_AUTO_TEST_SUITE(TestEditRest)

    BOOST_AUTO_TEST_CASE(NoExistingRest)
    {
        Position pos;

        EditRest action(&pos, 16);

        action.redo();

        BOOST_CHECK(pos.IsRest());
        BOOST_CHECK_EQUAL(pos.GetDurationType(), 16);

        action.undo();

        BOOST_CHECK(!pos.IsRest());
        BOOST_CHECK_EQUAL(pos.GetNoteCount(), 0);
    }

    BOOST_AUTO_TEST_CASE(ModifyExistingRest)
    {
        Position pos;
        pos.SetRest(true);
        pos.SetDurationType(4);

        EditRest action(&pos, 16);

        action.redo();

        BOOST_CHECK(pos.IsRest());
        BOOST_CHECK_EQUAL(pos.GetDurationType(), 16);

        action.undo();

        BOOST_CHECK(pos.IsRest());
        BOOST_CHECK_EQUAL(pos.GetDurationType(), 4);
    }

    BOOST_AUTO_TEST_CASE(RemoveRest)
    {
        Position pos;
        pos.SetRest(true);
        pos.SetDurationType(4);

        EditRest action(&pos, 4);

        action.redo();

        BOOST_CHECK(pos.IsRest() == false);

        action.undo();

        BOOST_CHECK(pos.IsRest());
        BOOST_CHECK_EQUAL(pos.GetDurationType(), 4);
    }

BOOST_AUTO_TEST_SUITE_END()