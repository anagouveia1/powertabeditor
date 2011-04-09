#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <audio/midievent.h>

class MockMidiEvent : public MidiEvent
{
public:
    MockMidiEvent(uint8_t channel, double startTime, double duration,
                  uint32_t positionIndex, uint32_t systemIndex) :
        MidiEvent(channel, startTime, duration, positionIndex, systemIndex)
    {
    }

    void performEvent(RtMidiWrapper&) const {}
};

// Test the ordering of midi events
BOOST_AUTO_TEST_SUITE(Ordering)

    // Order by timestamp
    BOOST_AUTO_TEST_CASE(StartTime)
    {
        MockMidiEvent event1(0, 100, 100, 4, 0);
        MockMidiEvent event2(0, 50, 100, 4, 0);

        BOOST_CHECK(event2 < event1);
    }

    // Additional tests for close timestamps
    BOOST_AUTO_TEST_CASE(CloseTimeStamps)
    {
        MockMidiEvent event1(0, 100, 100, 4, 0);
        MockMidiEvent event2(0, 100.15, 100, 4, 0);

        BOOST_CHECK(event1 < event2);

        // timestamps that are extremely close are considered equal
        MockMidiEvent event3(0, 100.000001, 100, 4, 0);
        BOOST_CHECK(!(event1 < event3) && !(event3 < event1));
    }

    // order by system index
    BOOST_AUTO_TEST_CASE(SystemIndex)
    {
        MockMidiEvent event1(0, 100, 100, 4, 0);
        MockMidiEvent event2(0, 100, 100, 4, 1);

        BOOST_CHECK(event1 < event2);
    }

    // order by position index
    BOOST_AUTO_TEST_CASE(PositionIndex)
    {
        MockMidiEvent event1(0, 100, 100, 5, 1);
        MockMidiEvent event2(0, 100, 100, 4, 1);

        BOOST_CHECK(event2 < event1);
    }

BOOST_AUTO_TEST_SUITE_END()

