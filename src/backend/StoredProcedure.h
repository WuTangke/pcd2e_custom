#ifndef STOREDPROCEDURE_H
#define STOREDPROCEDURE_H

#include <string>
#include <memory>
#include <fstream>
#include "Command.h"

using std::string;

namespace pdCalc {

	class StoredProcedure : public Command
	{
	public:
		StoredProcedure(class UserInterface& ui, const string& filename);
		~StoredProcedure() = default;

	private:
		StoredProcedure() = delete;
		StoredProcedure(StoredProcedure&&) = delete;
		StoredProcedure& operator=(const StoredProcedure&) = delete;
		StoredProcedure& operator=(StoredProcedure&&) = delete;
		StoredProcedure(const StoredProcedure&) = delete;

		void checkPreconditionsImpl() const override;
		void executeImpl() noexcept override;
		void undoImpl() noexcept override;
		Command* cloneImpl() const noexcept override;
		const char* helpMessageImpl() const noexcept override;

		mutable std::unique_ptr<class LazyTokenizer> tokenizer_;
		std::unique_ptr<class CommandInterpreter> ci_;
		std::string filename_;
		mutable std::ifstream ifs_;
		bool first_ = true;
	};
}
#endif
