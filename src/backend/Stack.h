#ifndef STACK_H
#define STACK_H

#include "../utilities/Publisher.h"

#include <vector>
#include <string>
#include <deque>


using std::string;
using std::vector;
using std::deque;

namespace pdCalc {

	class StackErrorData
	{
	public:
		enum class ErrorConditions { Empty, TooFewArguments };
		explicit StackErrorData(ErrorConditions e) : err_(e) { }

		static const char* Message(ErrorConditions ec);
		const char* message() const;
		ErrorConditions error() const { return err_; }

	private:
		ErrorConditions err_;
	};

	class Stack : private Publisher
	{
	public:
		static Stack& Instance();
		void push(double, bool suppressChangeEvent = false);
		double pop(bool suppressChangeEvent = false);
		void swapTop();

		// returns first min(n, stackSize) elements of the stack with the top of stack at position 0
		vector<double> getElements(size_t n) const;
		void getElements(size_t n, std::vector<double>&) const;

		using Publisher::attach;
		using Publisher::detach;

		// these are just needed for testing
		size_t size() const { return stack_.size(); }
		void clear();

		static string StackChanged();
		static string StackError();

	private:
		Stack();
		~Stack() = default;
		Stack(const Stack&) = delete;
		Stack(Stack&&) = delete;
		Stack& operator=(const Stack&) = delete;
		Stack& operator=(const Stack&&) = delete;

		deque<double> stack_;
	};
}
#endif