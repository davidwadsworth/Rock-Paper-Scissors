#pragma once

class PathBranch;
class Navigator
{
public:
	PathBranch * branch;

	virtual ~Navigator() {};
	virtual void init() {}
	virtual void close() {}
	virtual int choose_path() { return 1; };
};