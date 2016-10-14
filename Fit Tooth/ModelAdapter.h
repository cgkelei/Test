#include "stdafx.h"
#ifndef MODELADAPTER_H_
#define MODELADAPTER_H_
#include "obj.h"
#include "Model.h"
class ModelAdapter
{
public:
	ModelAdapter();
	~ModelAdapter();
	static bool FitEyes( const CModel& _head, const CModel& _leftEyes, const CModel& _rightEyes );
	static bool FitTooth( const CModel& _head, const CModel& _tooth );
private:
};


#endif // !MODELADAPTER_H_
