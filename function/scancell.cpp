#include <iostream>
#include "cv.h"
#include "highgui.h"

int main (int argv, char** argc[])
{
    int ncell = 0, prev_ncontour = 0, same_count = 0;
	////while (!worker->CancellationPending) {
		////worker->ReportProgress(50, String::Format(rm->GetString("Progress_Analyze_FoundNCell"), title, ncell));
		cvConvert(input_morph, tmp8UC1);
		cvClearMemStorage(storage);
		int ncontour = cvFindContours(tmp8UC1, storage, &first_con, sizeof(CvContour), CV_RETR_EXTERNAL);
		if (ncontour == 0)
			break; // finish extract cell
		if (ncontour == prev_ncontour) {
			cvErode(input_morph, input_morph);
			same_count++;
		} else
			same_count = 0;
		prev_ncontour = ncontour;
		cur = first_con;
		while (cur != nullptr) {
			double area = fabs(cvContourArea(cur));
			if ((area < 3000.0) || (same_count > 10)) {
				int npts = cur->total;
				CvPoint *p = new CvPoint[npts];
				cvCvtSeqToArray(cur, p);
				cvFillPoly(out_single, &p, &npts, 1, cvScalar(255.0)); // move to single
				cvFillPoly(input_morph, &p, &npts, 1, cvScalar(0.0)); // remove from input
				delete[] p;
				ncell++;
			}
			cur = cur->h_next;
		}
	////}
}
