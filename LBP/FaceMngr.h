#pragma once

#include "FaceMngr_def.h"


class __declspec(dllexport) CFaceMngr // 
{
public:
	vector<SModel> m_lstModel;
	CvMat	 *tmodel;
	int		m_featureSz, m_modelSz;
	void SaveToModel(char *path, int classId, char *name);
	void FormTrainMat(CvMat *inputs, int *trainIds);
	void train();
	void TrainResSave2Model();
	void Recognize(CvMat *model, SMatch *info);
	void openc();
	void detect();
};
