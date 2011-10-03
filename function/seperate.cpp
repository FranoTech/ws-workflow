	//## Seperate Cells ##//
	if (worker->CancellationPending == false) {
		// Marker-Controlled Watershed
		worker->ReportProgress(60, String::Concat(title, rm->GetString("Progress_Analyze_SeperateCell")));
		// Label each cells.
		cvConvert(out_single, tmp8UC1);
		cvClearMemStorage(storage);
		cvFindContours(tmp8UC1, storage, &first_con, sizeof(CvContour), CV_RETR_EXTERNAL);
		int count = 1;
		cur = first_con;
		while (cur != nullptr) {
			int npts = cur->total;
			CvPoint *p = new CvPoint[npts];
			cvCvtSeqToArray(cur, p);
			cvFillPoly(out_single, &p, &npts, 1, cvScalar((count++%254)+1)); // fill label, must be 1-255
			delete[] p;
			cur = cur->h_next;
		}

		cvConvertScale(output_morph, tmp8UC1);

		CvMat *inwater = cvCreateMat(out_single->height, out_single->width, CV_8UC3);
		CvMat outwater = cvMat(out_single->height, out_single->width, CV_32SC1, out_single->data.fl);

		cvMerge(tmp8UC1, tmp8UC1, tmp8UC1, nullptr, inwater);

		cvWatershed(inwater, &outwater);
		cvErode(out_single, out_single, nullptr, 2);
		cvConvertScale(output_morph, tmp8UC1);
		cvSub(output_morph, out_single, output_morph, tmp8UC1);

		cvReleaseMat(&inwater);
	}
