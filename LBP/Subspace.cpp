/*
blockwise-Fisherface
*/

#include "Subspace.h"

static CFld *g_fld;
static int	g_blkCnt; // number of blocks
static int	g_totalPrjDim;
static int	g_totalInputDim, g_blkInputDim;
static double	*g_blkWeights;

void WriteStringLine(ofstream &os, CString str)
{
	os << str << endl;
}

void ReadStringLine(ifstream &is, CString &str)
{
	char t[100];
	is.getline(t, 100);
	str = t;
}

void WriteIntText(ofstream &os, int n, CString name /*= ""*/)
{
	if (!name.IsEmpty()) WriteStringLine(os, name);
	os << n << endl;
}

void ReadIntText(ifstream &is, int &n, bool hasName /*= true*/)
{
	if (hasName)
	{
		CString tmp;
		ReadStringLine(is, tmp);
	}
	int m;
	is >> m;
	n = m;
	//is>>n;
	char c;
	is.get(c);
}

void WriteCvMatBin(ofstream &os, CvMat *mat, CString name /*= ""*/)
{
	if (!name.IsEmpty()) WriteStringLine(os, name);
	os.write((char*)mat->data.ptr, mat->step * mat->rows);
	os.put('\n');
}

void ReadCvMatBin(ifstream &is, CvMat *mat, bool hasName /*= true*/)
{
	if (hasName)
	{
		CString tmp;
		ReadStringLine(is, tmp);
	}
	is.read((char*)mat->data.ptr, mat->step * mat->rows);
	char c;
	is.get(c);
}


int CalcSubspace(CvMat *inputs, int *trainIds)
{
	ReleaseSubspace();

	g_blkCnt = 40;
	int maxPrjDim = 200 * g_blkCnt;
	g_totalInputDim = inputs->rows;
	g_blkInputDim = g_totalInputDim / g_blkCnt;

	CvMat sub;
	g_fld = new CFld[g_blkCnt];
	int dim1 = 0;

	for (int i = 0; i < g_blkCnt; i++)
	{
		cvGetSubRect(inputs, &sub, cvRect(0, i*g_blkInputDim, inputs->width, g_blkInputDim));
		dim1 += g_fld[i].TrainFld(&sub, trainIds);
	}

	g_blkWeights = new double[g_blkCnt];

	double weight[40] = {
		0.91, 0.88, 0.88, 0.91,
		0.97, 0.98, 0.98, 0.97,
		0.93, 1.00, 1.00, 0.93,
		0.89, 0.97, 0.97, 0.89,
		0.84, 0.95, 0.95, 0.84,
		0.74, 0.91, 0.91, 0.74,
		0.77, 0.89, 0.89, 0.77,
		0.80, 0.85, 0.85, 0.80,
		0.81, 0.82, 0.82, 0.81,
		0.77, 0.80, 0.80, 0.77 };
	for (int i = 0; i<g_blkCnt; i++) g_blkWeights[i] = weight[i];
	g_totalPrjDim = dim1;

	return g_totalPrjDim;
}

void Project(CvMat *inputs, CvMat *results)
{
	CvMat subIn, subOut;
	int prjCnt = 0;
	for (int i = 0; i < g_blkCnt; i++)
	{
		cvGetRows(inputs, &subIn, i*g_blkInputDim, (i + 1)*g_blkInputDim);
		cvGetRows(results, &subOut, prjCnt, prjCnt + g_fld[i].m_postLdaDim);
		prjCnt += g_fld[i].m_postLdaDim;
		g_fld[i].ProjectFld(&subIn, &subOut);
	}
}

int GetModelSize(){ return g_totalPrjDim; }

int GetFtDim(){ return g_totalInputDim; }

double CalcVectorDist(CvMat *target, CvMat *query)
{
	double score = 0;
	CvMat subT, subQ;
	int subDim, prjCnt = 0;
	for (int i = 0; i < g_blkCnt; i++)
	{
		subDim = g_fld[i].m_postLdaDim;
		cvGetRows(target, &subT, prjCnt, prjCnt + subDim);
		cvGetRows(query, &subQ, prjCnt, prjCnt + subDim);
		prjCnt += subDim;
		score -= (cvDotProduct(&subT, &subQ) / cvNorm(&subT) / cvNorm(&subQ) * g_blkWeights[i]);
	}

	return (1 + score / g_blkCnt) / 2;
}

bool WriteDataToFile(ofstream &os)
{
	WriteIntText(os, g_fld[0].W_prjT->step / g_fld[0].W_prjT->cols, "dataBytes:");
	WriteIntText(os, g_blkCnt, "blockCount:");
	WriteIntText(os, g_totalInputDim, "totalInputFeatureDim:");
	WriteIntText(os, g_totalPrjDim, "totalProjectDim:");

	for (int i = 0; i < g_blkCnt; i++)
	{
		WriteIntText(os, i, "blockIndex:");
		WriteIntText(os, g_fld[i].m_inputDim, "inputDim:");
		WriteIntText(os, g_fld[i].m_postLdaDim, "postLdaDim:");
		WriteCvMatBin(os, g_fld[i].mu_total, "mu_total:");
		WriteCvMatBin(os, g_fld[i].W_prjT, "W_prjT:");
	}
	return true;
}

bool ReadDataFromFile(ifstream &is)
{
	ReleaseSubspace();

	int	dataBytes;
	ReadIntText(is, dataBytes);
	if ((dataBytes == 4 && CV_COEF_FC1 == CV_64FC1) ||
		(dataBytes == 8 && CV_COEF_FC1 == CV_32FC1))
	{
		return false;
	}

	ReadIntText(is, g_blkCnt);
	ReadIntText(is, g_totalInputDim);
	ReadIntText(is, g_totalPrjDim);

	int tmp;
	g_fld = new CFld[g_blkCnt];
	for (int i = 0; i < g_blkCnt; i++)
	{
		ReadIntText(is, tmp);

		ReadIntText(is, g_fld[i].m_inputDim);
		ReadIntText(is, g_fld[i].m_postLdaDim);
		g_fld[i].mu_total = cvCreateMat(g_fld[i].m_inputDim, 1, CV_COEF_FC1);
		ReadCvMatBin(is, g_fld[i].mu_total);
		g_fld[i].W_prjT = cvCreateMat(g_fld[i].m_postLdaDim, g_fld[i].m_inputDim, CV_COEF_FC1);
		ReadCvMatBin(is, g_fld[i].W_prjT);
	}

	double weight[40] = {
		0.91, 0.88, 0.88, 0.91,
		0.97, 0.98, 0.98, 0.97,
		0.93, 1.00, 1.00, 0.93,
		0.89, 0.97, 0.97, 0.89,
		0.84, 0.95, 0.95, 0.84,
		0.74, 0.91, 0.91, 0.74,
		0.77, 0.89, 0.89, 0.77,
		0.80, 0.85, 0.85, 0.80,
		0.81, 0.82, 0.82, 0.81,
		0.77, 0.80, 0.80, 0.77 };
	g_blkWeights = new double[g_blkCnt];
	for (int i = 0; i<g_blkCnt; i++) g_blkWeights[i] = weight[i];
	g_blkInputDim = g_totalInputDim / g_blkCnt;

	return true;
}

void ReleaseSubspace()
{
	if (g_fld) delete[]g_fld;
	if (g_blkWeights) delete[]g_blkWeights;
	g_blkCnt = g_totalPrjDim = g_totalInputDim = g_blkInputDim = 0;
	g_fld = NULL;
	g_blkWeights = NULL;
}
