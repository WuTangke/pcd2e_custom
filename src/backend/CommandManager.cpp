#include "CommandManager.h"

namespace pdCalc {

	class CommandManager::CommandManagerStrategy
	{
	public:
		virtual ~CommandManagerStrategy() = default;

		virtual size_t getUndoSize() const = 0;
		virtual size_t getRedoSize() const = 0;

		virtual void executeCommand(CommandPtr c) = 0;
		virtual void undo() = 0;
		virtual void redo() = 0;
	};

	class CommandManager::UndoRedoStackStrategy : public CommandManager::CommandManagerStrategy
	{
	public:
		size_t getUndoSize() const override { return undoStack_.size(); }
		size_t getRedoSize() const override { return redoStack_.size(); }

		void executeCommand(CommandPtr c) override;
		void undo() override;
		void redo() override;

	private:
		void flushStack(stack<CommandPtr>& st);

		stack<CommandPtr> undoStack_;
		stack<CommandPtr> redoStack_;
	};

	void CommandManager::UndoRedoStackStrategy::executeCommand(CommandPtr c)
	{
		c->execute();

		undoStack_.push(std::move(c));
		flushStack(redoStack_);

		return;
	}

	void CommandManager::UndoRedoStackStrategy::undo()
	{
		if (getUndoSize() == 0) return;

		auto& c = undoStack_.top();
		c->undo();

		redoStack_.push(std::move(c));
		undoStack_.pop();

		return;
	}

	void CommandManager::UndoRedoStackStrategy::redo()
	{
		if (getRedoSize() == 0) return;

		auto& c = redoStack_.top();
		c->execute();

		undoStack_.push(std::move(c));
		redoStack_.pop();

		return;
	}

	void CommandManager::UndoRedoStackStrategy::flushStack(stack<CommandPtr>& st)
	{
		while (!st.empty())
		{
			st.pop();
		}

		return;
	}

	class CommandManager::UndoRedoListStrategyVector : public CommandManager::CommandManagerStrategy
	{
	public:
		UndoRedoListStrategyVector() : cur_{ -1 }, undoSize_{ 0 }, redoSize_{ 0 } { }

		size_t getUndoSize() const override { return undoSize_; }
		size_t getRedoSize() const override { return redoSize_; }

		void executeCommand(CommandPtr c) override;
		void undo() override;
		void redo() override;

	private:
		void flush();

		int cur_;
		size_t undoSize_;
		size_t redoSize_;
		vector<CommandPtr> undoRedoList_;
	};

	void CommandManager::UndoRedoListStrategyVector::executeCommand(CommandPtr c)
	{
		c->execute();

		flush();
		undoRedoList_.emplace_back(std::move(c));
		cur_ = undoRedoList_.size() - 1;
		++undoSize_;
		redoSize_ = 0;

		return;
	}

	void CommandManager::UndoRedoListStrategyVector::undo()
	{
		if (getUndoSize() == 0) return;

		undoRedoList_[cur_]->undo();
		--cur_;
		--undoSize_;
		++redoSize_;

		return;
	}

	void CommandManager::UndoRedoListStrategyVector::redo()
	{
		if (getRedoSize() == 0) return;

		++cur_;
		undoRedoList_[cur_]->execute();
		--redoSize_;
		++undoSize_;

		return;
	}

	void CommandManager::UndoRedoListStrategyVector::flush()
	{
		if (!undoRedoList_.empty()) undoRedoList_.erase(undoRedoList_.begin() + cur_ + 1, undoRedoList_.end());

		return;
	}

	class CommandManager::UndoRedoListStrategy : public CommandManager::CommandManagerStrategy
	{
	public:
		UndoRedoListStrategy();

		size_t getUndoSize() const override { return undoSize_; }
		size_t getRedoSize() const override { return redoSize_; }

		void executeCommand(CommandPtr c) override;
		void undo() override;
		void redo() override;

	private:
		void flush();

		size_t undoSize_;
		size_t redoSize_;
		list<CommandPtr> undoRedoList_;
		list<CommandPtr>::iterator cur_;
	};

	CommandManager::~CommandManager() = default;

	CommandManager::UndoRedoListStrategy::UndoRedoListStrategy()
		: undoSize_{ 0 }
		, redoSize_{ 0 }
	{
		// We need an empty spot in the front so the pointer can reverse beyond the front of the
		// list or real commands
		undoRedoList_.push_back(MakeCommandPtr(nullptr));
		cur_ = undoRedoList_.end();
	}

	void CommandManager::UndoRedoListStrategy::executeCommand(CommandPtr c)
	{
		c->execute();

		flush();
		undoRedoList_.emplace_back(std::move(c));
		++undoSize_;
		redoSize_ = 0;
		cur_ = undoRedoList_.end();
		--cur_;

		return;
	}

	void CommandManager::UndoRedoListStrategy::undo()
	{
		if (undoSize_ == 0) return;

		--undoSize_;
		++redoSize_;
		(*cur_)->undo();
		--cur_;

		return;
	}

	void CommandManager::UndoRedoListStrategy::redo()
	{
		if (redoSize_ == 0) return;

		--redoSize_;
		++undoSize_;
		++cur_;
		(*cur_)->execute();

		return;
	}

	void CommandManager::UndoRedoListStrategy::flush()
	{
		if (cur_ != undoRedoList_.end())
		{
			auto i = cur_;
			++i;
			undoRedoList_.erase(i, undoRedoList_.end());
		}

		return;
	}

	CommandManager::CommandManager(UndoRedoStrategy st)
	{
		switch (st)
		{
		case UndoRedoStrategy::ListStrategy:
			strategy_ = make_unique<UndoRedoListStrategy>();
			break;

		case UndoRedoStrategy::StackStrategy:
			strategy_ = make_unique<UndoRedoStackStrategy>();
			break;

		case UndoRedoStrategy::ListStrategyVector:
			strategy_ = make_unique<UndoRedoListStrategyVector>();
			break;
		}
	}

	size_t CommandManager::getUndoSize() const
	{
		return strategy_->getUndoSize();
	}

	size_t CommandManager::getRedoSize() const
	{
		return strategy_->getRedoSize();
	}

	void CommandManager::executeCommand(CommandPtr c)
	{
		strategy_->executeCommand(std::move(c));
		return;
	}

	void CommandManager::undo()
	{
		strategy_->undo();
		return;
	}

	void CommandManager::redo()
	{
		strategy_->redo();
		return;
	}
}
