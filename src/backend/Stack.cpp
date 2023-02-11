#include "Stack.h"

namespace pdCalc {
	string Stack::StackChanged()
	{
		return "stackChanged";
	}

	string Stack::StackError()
	{
		return "error";
	}

	const char* StackErrorData::Message(StackErrorData::ErrorConditions ec)
	{
		switch (ec)
		{
		case ErrorConditions::Empty: return "Attempting to pop empty stack";
		case ErrorConditions::TooFewArguments: return "Need at least two stack elements to swap top";
		default: return "Unknown error";
		};
	}

	const char* StackErrorData::message() const
	{
		return Message(err_);
	}


	void Stack::push(double d, bool suppressChangeEvent)
	{
		stack_.push_back(d);
		if (!suppressChangeEvent) raise(Stack::StackChanged(), nullptr);

		return;
	}

	double Stack::pop(bool suppressChangeEvent)
	{
		if (stack_.empty())
		{
			raise(Stack::StackError(), StackErrorData{ StackErrorData::ErrorConditions::Empty });

			throw Exception{ StackErrorData::Message(StackErrorData::ErrorConditions::Empty) };
		}
		else
		{
			auto val = stack_.back();
			stack_.pop_back();
			if (!suppressChangeEvent) raise(Stack::StackChanged(), nullptr);
			return val;
		}
	}

	void Stack::swapTop()
	{
		if (stack_.size() < 2)
		{
			raise(Stack::StackError(), StackErrorData{ StackErrorData::ErrorConditions::TooFewArguments });

			throw Exception{ StackErrorData::Message(StackErrorData::ErrorConditions::TooFewArguments) };
		}
		else
		{
			auto first = stack_.back();
			stack_.pop_back();
			auto second = stack_.back();
			stack_.pop_back();
			stack_.push_back(first);
			stack_.push_back(second);

			raise(Stack::StackChanged(), nullptr);
		}

		return;
	}

	vector<double> Stack::getElements(size_t n) const
	{
		vector<double> v;
		getElements(n, v);
		return v;
	}

	void Stack::getElements(size_t n, vector<double>& v) const
	{
		// if n is > stack's size, just return size of stack
		if (n > stack_.size()) n = stack_.size();

		v.insert(v.end(), stack_.rbegin(), stack_.rbegin() + n);

		return;
	}

	void Stack::clear()
	{
		stack_.clear();

		raise(Stack::StackChanged(), nullptr);

		return;
	}

	Stack& Stack::Instance()
	{
		static Stack instance;
		return instance;
	}

	Stack::Stack()
	{
		registerEvent(StackChanged());
		registerEvent(StackError());
	}
}