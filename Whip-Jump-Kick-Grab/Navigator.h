#pragma once

/**
 * @author David Wadsworth
 * 
 * A "guide" which chooses what path the user should go down next
 */

class PathBranch;
class Navigator
{
public:
	PathBranch * branch = nullptr;

	virtual ~Navigator() {};
	virtual void init() {}
	virtual void close() {}
	virtual int choose_path() { return 1; };
};