#include <algorithm>
#include <ranges>
#include <memory>
#include <fstream>
#include "StoredProcedure.h"
#include "Utilities.h"
#include "CommandInterpreter.h"

namespace ranges = std::ranges;
namespace views = std::views;

using std::string;

namespace pdCalc {

	StoredProcedure::StoredProcedure(UserInterface& ui, const string& filename)
		: filename_{ filename }
	{
		ci_ = std::make_unique<CommandInterpreter>(ui);
	}

	void StoredProcedure::checkPreconditionsImpl() const
	{
		if (first_)
		{
			try
			{
				ifs_.open(filename_.c_str());
				if (!ifs_)
					throw Exception{ "Could not open procedure" };

				tokenizer_ = std::make_unique<LazyTokenizer>(ifs_);
			}
			catch (...)
			{
				throw Exception{ "Could not open procedure" };
			}
		}

		return;
	}

	void StoredProcedure::executeImpl() noexcept
	{
		if (first_)
		{
			ranges::for_each(*tokenizer_, [this](auto c) {ci_->commandEntered(c); });
			first_ = false;
		}
		else
		{
			for (auto i = 0u; i < tokenizer_->nTokens(); ++i)
				ci_->commandEntered("redo");
		}

		return;
	}

	void StoredProcedure::undoImpl() noexcept
	{
		for (auto i = 0u; i < tokenizer_->nTokens(); ++i)
			ci_->commandEntered("undo");

		return;
	}

	Command* StoredProcedure::cloneImpl() const noexcept
	{
		return 0;
	}

	const char* StoredProcedure::helpMessageImpl() const noexcept
	{
		return "Executes a stored procedure from disk";
	}
}

