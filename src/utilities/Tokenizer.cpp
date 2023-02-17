#include "Tokenizer.h"

namespace pdCalc {

	GreedyTokenizer::GreedyTokenizer(istream& is)
	{
		tokenize(is);
	}

	void GreedyTokenizer::tokenize(istream& is)
	{
		for (istream_iterator<string> i{ is }; i != istream_iterator<string>{}; ++i)
		{
			string t;
			ranges::transform(*i, back_inserter<string>(t), ::tolower);
			tokens_.push_back(std::move(t));
		}

		return;
	}

	LazyTokenizer::LazyTokenizer(istream& is)
		: nTokens_{ 0 }
		, generator_{ tokenize(is) }
	{ }

	cppcoro::generator<string> LazyTokenizer::tokenize(istream& is) noexcept
	{
		for (istream_iterator<string> i{ is }; i != istream_iterator<string>{}; ++i)
		{
			string t;
			ranges::transform(*i, back_inserter<string>(t), ::tolower);
			++nTokens_;
			co_yield t;
		}

		co_return;
	}
}