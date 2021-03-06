#include "utility.hpp"
#include <cstddef>

TEST_CASE("Stack construction")
{
	const std::string first;
	const std::string second{ "Hello World!" };

	rapidstring s1;
	rs_init(&s1);

	VALIDATE_RS(&s1, first);

	rapidstring s2;
	rs_init(&s2);

	VALIDATE_RS(&s2, first);

	rapidstring s3;
	rs_init_w(&s3, second.data());

	VALIDATE_RS(&s3, second);

	rs_free(&s1);
	rs_free(&s2);
	rs_free(&s3);
}

TEST_CASE("Heap construction")
{
	const std::string first{ "A long string to get around SSO!" };

	rapidstring s;
	rs_init_w(&s, first.data());

	VALIDATE_RS(&s, first);

	rs_free(&s);
}

TEST_CASE("Capacity construction")
{
	constexpr std::size_t cap{ 100 };
	rapidstring s;
	rs_init_w_cap(&s, cap);

	REQUIRE(rs_is_heap(&s));
	REQUIRE(rs_cap(&s) >= cap);

	rs_free(&s);
}

TEST_CASE("rapidstring construction")
{
	const std::string first{ "Short!" };
	const std::string second{ "A very long string to get around SSO!" };

	rapidstring s1, s2;
	rs_init_w(&s1, first.data());
	rs_init_w_rs(&s2, &s1);

	VALIDATE_RS(&s2, first);

	rapidstring s3, s4;
	rs_init_w(&s3, second.data());
	rs_init_w_rs(&s4, &s3);

	VALIDATE_RS(&s4, second);

	rs_free(&s4);
	rs_free(&s3);
	rs_free(&s2);
	rs_free(&s1);
}
