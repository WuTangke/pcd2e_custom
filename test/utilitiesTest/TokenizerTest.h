#ifndef TOKENIZER_TEST_H
#define TOKENIZER_TEST_H

#include <QtTest/QtTest>
#include <vector>
#include <string>

namespace pdCalc
{
	class LazyTokenizer;
	class GreedyTokenizer;
}

class TokenizerTest : public QObject
{
	Q_OBJECT
private slots:
	void testTokenizationFromStream();

private:
	void assertGreedyTokenizerMatches(const std::vector<std::string>&, pdCalc::GreedyTokenizer&);
	void assertLazyTokenizerMatches(const std::vector<std::string>&, pdCalc::LazyTokenizer&);
};

#endif
