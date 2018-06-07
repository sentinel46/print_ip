#define BOOST_TEST_MODULE test_print_ip

#include <boost/test/included/unit_test.hpp>

#include "print_ip.h"

struct cout_redirect
{
    cout_redirect(std::streambuf *new_buffer) : old(std::cout.rdbuf(new_buffer)) {}

    ~cout_redirect() { std::cout.rdbuf(old); }

private:
    std::streambuf *old;
};

BOOST_AUTO_TEST_SUITE(test_print_ip_suite)

BOOST_AUTO_TEST_CASE(test_has_const_iterator)
{
    BOOST_CHECK(my::has_const_iterator<std::vector<int>>::value == true);
    BOOST_CHECK(my::has_const_iterator<std::list<int>>::value == true);
    BOOST_CHECK(my::has_const_iterator<int>::value == false);
    BOOST_CHECK(my::has_const_iterator<char>::value == false);
}

BOOST_AUTO_TEST_CASE(test_has_begin_end)
{
    BOOST_CHECK(my::has_begin_end<std::vector<int>>::beg_value == true);
    BOOST_CHECK(my::has_begin_end<std::vector<int>>::end_value == true);
    BOOST_CHECK(my::has_begin_end<std::list<int>>::beg_value == true);
    BOOST_CHECK(my::has_begin_end<std::list<int>>::end_value == true);
    BOOST_CHECK(my::has_begin_end<int>::beg_value == false);
    BOOST_CHECK(my::has_begin_end<int>::end_value == false);
    BOOST_CHECK(my::has_begin_end<char>::beg_value == false);
    BOOST_CHECK(my::has_begin_end<char>::end_value == false);
}

BOOST_AUTO_TEST_CASE(test_is_container)
{
    BOOST_CHECK(my::is_container<std::vector<int>>::value == true);
    BOOST_CHECK(my::is_container<std::list<int>>::value == true);
    BOOST_CHECK(my::is_container<int>::value == false);
    BOOST_CHECK(my::is_container<char>::value == false);
}

BOOST_AUTO_TEST_CASE(test_print_ip)
{
    boost::test_tools::output_test_stream output;
    {
        cout_redirect guard(output.rdbuf());

        char c = -1;  // 255
        my::print_ip(c);
        BOOST_CHECK(output.is_equal("255\n"));

        short s = 0;  // 0.0
        my::print_ip(s);
        BOOST_CHECK(output.is_equal("0.0\n"));

        int i = 2130706433;  // 127.0.0.1
        my::print_ip(i);
        BOOST_CHECK(output.is_equal("127.0.0.1\n"));

        long l = 8875824491850138409;  // 123.45.67.89.101.112.131.41
        my::print_ip(l);
        BOOST_CHECK(output.is_equal("123.45.67.89.101.112.131.41\n"));

        std::string str = "192.168.0.1";
        my::print_ip(str);
        BOOST_CHECK(output.is_equal("192.168.0.1\n"));

        std::vector<int> vector = {10, 20, 0, 1};
        my::print_ip(vector);
        BOOST_CHECK(output.is_equal("10.20.0.1\n"));

        std::list<int> list = {10, 20, 0, 2};
        my::print_ip(list);
        BOOST_CHECK(output.is_equal("10.20.0.2\n"));

        auto tuple = std::make_tuple(10, 20, 0, 3);
        my::print_ip(tuple);
        BOOST_CHECK(output.is_equal("10.20.0.3\n"));
    }
}

BOOST_AUTO_TEST_SUITE_END()
