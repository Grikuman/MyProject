#pragma once
#ifndef IBEHAVIOR_DEFINED
#define IBEHAVIOR_DEFINED
enum class Status { SUCCESS, FAILURE, RUNNING};

class IBehavior
{
public:
	// デストラクタ
	virtual ~IBehavior() = default;
	virtual Status Tick()  = 0;
};

#endif		// IBEHAVIOR_DEFINED
