#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <string>
#include <string_view>

using std::string;
using std::string_view;

namespace pdCalc {

	class Exception
	{
	public:
		explicit Exception(string_view msg) : msg_{ msg } { }
		const string& what() const { return msg_; }

	private:
		string msg_;
	};

}
#endif