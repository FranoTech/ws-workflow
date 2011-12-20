

	
	//## Scanning ##//
    
    //init 
	CvMat *input3Ch = nullptr;
	CvMat *output1Ch = nullptr;
    CvMat *input_morph = cvCreateMat(output1Ch->height, output1Ch->width, CV_32FC1);
	IplImage *tmp8UC1 = nullptr;
	CvMemStorage *storage = cvCreateMemStorage();
	CvSeq *first_con = nullptr;
	CvSeq *cur = nullptr;
	CvMat *out_single = nullptr;
	CvMat *output_morph = nullptr;
    
    
    
    
	// Convert image to 32F
	input3Ch = cvCreateMat(img->Height, img->Width, CV_32FC3);
	output1Ch = cvCreateMat(img->Height, img->Width, CV_32FC1);
    
	cvConvertScale(tmpImage, input3Ch);


	//## Predict ##//
	if (!worker->CancellationPending) {
		
		CvMat input_nn = cvMat(input3Ch->height*input3Ch->width, 3, CV_32FC1, input3Ch->data.fl);
		CvMat output_nn = cvMat(output1Ch->height*output1Ch->width, 1, CV_32FC1, output1Ch->data.fl);

		neuron->predict(&input_nn, &output_nn);

		// Binarize cells/background
		cvThreshold(output1Ch, input_morph, -0.5, 255.0, CV_THRESH_BINARY);
	}

	//## Remove Noise/Small Cells ##//
	if (!worker->CancellationPending) {
		
        
        //morph
		IplConvKernel *se1 = cvCreateStructuringElementEx(3, 3, 1, 1, CV_SHAPE_ELLIPSE);
		cvMorphologyEx(input_morph, input_morph, nullptr, se1, CV_MOP_OPEN); // remove noise
        //morph



        // remove small cells and fill holes.
		out_single = cvCreateMat(input_morph->height, input_morph->width, CV_32FC1);
		cvSetZero(out_single);
        
		tmp8UC1 = cvCreateImage(cvGetSize(input_morph), IPL_DEPTH_8U, 1);
		cvConvert(input_morph, tmp8UC1);
        
		cvFindContours(tmp8UC1, storage, &first_con, sizeof(CvContour), CV_RETR_EXTERNAL);
        cur = first_con;
		while (cur != nullptr) {
			double area = fabs(cvContourArea(cur));
			int npts = cur->total;
			CvPoint *p = new CvPoint[npts];
			cvCvtSeqToArray(cur, p);
			if (area < 1500.0) // remove small area
				cvFillPoly(input_morph, &p, &npts, 1, cvScalar(0.0)); // remove from input
			else if (area < 7500.0) {
				cvFillPoly(out_single, &p, &npts, 1, cvScalar(255.0)); // move to single
				cvFillPoly(input_morph, &p, &npts, 1, cvScalar(0.0)); // remove from input
			}else
				cvFillPoly(input_morph, &p, &npts, 1, cvScalar(255.0)); // fill hole
			delete[] p;
			cur = cur->h_next;
		}

		output_morph = cvCreateMat(input_morph->height, input_morph->width, CV_32FC1);
		cvOr(input_morph, out_single, output_morph);
		cvReleaseStructuringElement(&se1);
        // remove small cells and fill holes.
        
	}

	//## Scanning Cells ##//
	int ncell = 0, prev_ncontour = 0, same_count = 0;
	while (!worker->CancellationPending) {

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
	}

	//## Seperate Cells ##//
	if (worker->CancellationPending == false) {
		// Marker-Controlled Watershed
		
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

	//## Prepare Result ##//
	int ncount=0, pcount=0; // count negative and positive cells
	if (!worker->CancellationPending) {
        
		// Find result
		cvConvertScale(output_morph, tmp8UC1);
		cvClearMemStorage(storage);
		cvFindContours(tmp8UC1, storage, &first_con, sizeof(CvContour), CV_RETR_EXTERNAL);

		BitmapData^ resultBD = nullptr;
		if (result != nullptr) {
			// Lock result
			resultBD = result->LockBits(System::Drawing::Rectangle(0, 0, result->Width, result->Height), 
				ImageLockMode::ReadWrite, result->PixelFormat);
			cvReleaseImageHeader(&tmpImage);
			tmpImage = cvCreateImageHeader(cvSize(result->Width, result->Height), IPL_DEPTH_8U, 3);
			tmpImage->imageData = (char*)(void*)resultBD->Scan0;
			tmpImage->widthStep = resultBD->Stride;
			cvSet(tmpImage, CV_RGB(0,0,255)); // Background, blue
		} else
			tmpImage = nullptr;
		if (control != nullptr)
			control->RemoveAllFigures();

		cvSetZero(tmp8UC1);
		CvScalar pixel;
		cur = first_con;
		ncell = 0; // total cells
		while ((cur != nullptr) && (worker->CancellationPending == false)) {
			if ((cur->total > 2) && (fabs(cvContourArea(cur)) > 1500.0)) { // remove small area
				int npts = cur->total;
				CvPoint *p = new CvPoint[npts];
				cvCvtSeqToArray(cur, p);
				cvFillPoly(tmp8UC1, &p, &npts, 1, cvScalar(255)); // set mask
				pixel = cvAvg(output1Ch, tmp8UC1);
				cvFillPoly(tmp8UC1, &p, &npts, 1, cvScalar(0)); // clear mask
				if (pixel.val[0] > 0.5) { // Negative, green
					if (tmpImage != nullptr)
						cvFillPoly(tmpImage, &p, &npts, 1, CV_RGB(0,255,0));
					
				} else if (pixel.val[0] > -0.5) { // Positive, red
					if (tmpImage != nullptr)
						cvFillPoly(tmpImage, &p, &npts, 1, CV_RGB(255,0,0));
				}
				delete[] p;
			}
			cur = cur->h_next;
		}

		if (result != nullptr)
			result->UnlockBits(resultBD); // Unlock result
	}
	
	if (tmp8UC1 != nullptr) cvReleaseImage(&tmp8UC1);
	if (input_morph != nullptr) cvReleaseMat(&input_morph);
	if (out_single != nullptr) cvReleaseMat(&out_single);
	if (output_morph != nullptr) cvReleaseMat(&output_morph);
	if (input3Ch != nullptr) cvReleaseMat(&input3Ch);
	if (output1Ch != nullptr) cvReleaseMat(&output1Ch);
	if (tmpImage != nullptr) cvReleaseImageHeader(&tmpImage);
	if (storage != nullptr) cvReleaseMemStorage(&storage);
	
}
