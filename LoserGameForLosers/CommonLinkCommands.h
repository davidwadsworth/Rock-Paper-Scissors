#pragma once
#include "LinkCommand.h"
#include "Targetable.h"

class ChangeStateLink : public LinkCommand
{
	int state_, previous_state_;
	Entity * entity_;
public:
	explicit ChangeStateLink(const std::string new_state)
		: state_(std::stoi(new_state))
	{}

	void execute(Entity* entity) override;

	void undo() override;

};

class ChangeScreenLink : public LinkCommand
{
public:
	ChangeScreenLink() {}

	void execute(Entity * entity) override
	{}

	void undo() override {}
};

class SelectAttackLink : public LinkCommand, public Targetable
{
	int attack_id_, previous_attack_id_;
	Entity * target_, * entity_;
public:
	SelectAttackLink(const std::string command_val)
		: attack_id_(stoi(command_val)), target_(nullptr)
	{}
	void change_target(Entity* target) override;

	void execute(Entity * entity) override;

	void undo() override;
};


class NothingLink : public LinkCommand
{
public:
	NothingLink()
	{}

	void execute(Entity* entity) override {}

	void undo() override {}
};

class UndoLink : public LinkCommand
{
	
public:
	UndoLink() = default;

	void execute(Entity * entity) override;

	void undo() override {}
};

class ChooseCharacterLink : public LinkCommand
{
	Entity * entity_;
	int character_id_, previous_id_;
public:
	ChooseCharacterLink(const std::string command_value)
		: character_id_(stoi(command_value)), entity_(nullptr)
	{}
	void execute(Entity* entity) override;
	void undo() override;
};

class ChooseBackgroundLink : public LinkCommand
{
	int background_id_, previous_id_;
public:
	explicit ChooseBackgroundLink(const std::string command_value)
		: background_id_(stoi(command_value)), previous_id_(0)
	{}

	void execute(Entity* entity) override;
	void undo() override {}
};

class SinglePlayerLink : public LinkCommand
{
	Entity * entity_;
public:
	SinglePlayerLink()
	{}

	void execute(Entity* entity) override;
	void undo() override;
};

class TwoPlayerLink : public LinkCommand
{
	Entity * p1_entity_, * p2_entity_;
public:
	TwoPlayerLink()
	{}

	void execute(Entity* entity) override;
	void undo() override;
};

class SetDifficultyLink : public LinkCommand
{
	int difficulty_id_;
	Entity * entity_;
public:
	SetDifficultyLink(const std::string command_value)
		: difficulty_id_(stoi(command_value))
	{}

	void execute(Entity* entity) override;
	void undo() override;
};