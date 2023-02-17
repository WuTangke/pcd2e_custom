#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <sstream>
#include <string>
#include <vector>
#include <istream>
#include <compare>
#include "3rdParty/cppcoro/generator.hpp"
#include <iterator>
#include <algorithm>
#include <iostream>
#include <ranges>

using std::string;
using std::istream_iterator;
using std::back_inserter;
using std::vector;
using std::istream;
namespace ranges = std::ranges;
namespace views = std::views;

namespace pdCalc {

	class GreedyTokenizer
	{
	public:
		explicit GreedyTokenizer(istream&);
		~GreedyTokenizer() = default;

		size_t nTokens() const { return tokens_.size(); }

		auto begin() { return tokens_.begin(); }
		auto end() { return tokens_.end(); }

	private:
		void tokenize(istream&);

		GreedyTokenizer() = delete;
		GreedyTokenizer(const GreedyTokenizer&) = delete;
		GreedyTokenizer(GreedyTokenizer&&) = delete;
		GreedyTokenizer& operator=(const GreedyTokenizer&) = delete;
		GreedyTokenizer& operator=(GreedyTokenizer&&) = delete;

		vector<string> tokens_;
	};

	class LazyTokenizer
	{
	public:
		explicit LazyTokenizer(istream&);
		~LazyTokenizer() = default;

		auto begin() { return generator_.begin(); }
		auto end() { return generator_.end(); }

		size_t nTokens() const { return nTokens_; }

	private:
		cppcoro::generator<string> tokenize(istream& is) noexcept;

		LazyTokenizer() = delete;
		LazyTokenizer(const LazyTokenizer&) = delete;
		LazyTokenizer(LazyTokenizer&&) = delete;
		LazyTokenizer& operator=(const LazyTokenizer&) = delete;
		LazyTokenizer& operator=(LazyTokenizer&&) = delete;

		size_t nTokens_;
		cppcoro::generator<string> generator_;
	};
}

#endif