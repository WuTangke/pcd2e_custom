#include "TokenizerTest.h"
#include <sstream>
#include <iostream>
#include "Utilities.h"

using std::vector;
using std::string;
using std::istringstream;

void TokenizerTest::assertGreedyTokenizerMatches(const std::vector<string>& tokens, pdCalc::GreedyTokenizer& tokenizer)
{
	QCOMPARE(tokens.size(), tokenizer.nTokens());

	auto j = tokens.begin();
	for (auto i : tokenizer)
	{
		QCOMPARE(i, *j);
		++j;
	}

	return;
}

void TokenizerTest::assertLazyTokenizerMatches(const std::vector<std::string>& tokens, pdCalc::LazyTokenizer& tokenizer)
{
	auto tk = tokens.begin();
	for (auto i : tokenizer)
	{
		QCOMPARE(i, *tk);
		++tk;
	}

	QCOMPARE(tokenizer.nTokens(), tokens.size());

	return;
}

void TokenizerTest::testTokenizationFromStream()
{
	vector<string> tokens = { "7.3454", "8.21", "SIn", "dUP", "dup", "/", "pow", "4.35", "ArCtaN" "-18.4" "neg" "root" };
	vector<string> tokensAns = { "7.3454", "8.21", "sin", "dup", "dup", "/", "pow", "4.35", "arctan" "-18.4" "neg" "root" };

	string t;
	for (size_t i = 0; i < tokens.size(); ++i)
	{
		t += tokens[i] + (i % 3 == 0 ? "\n" : " ");
	}

	istringstream iss(t);

	pdCalc::GreedyTokenizer feTokenizer{ iss };

	assertGreedyTokenizerMatches(tokensAns, feTokenizer);

	istringstream iss2(t);
	pdCalc::LazyTokenizer tokenizer{ iss2 };
	assertLazyTokenizerMatches(tokensAns, tokenizer);

	return;
}


