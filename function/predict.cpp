// ทิ้งไว้ก่อน

//if (!worker->CancellationPending) {
		//worker->ReportProgress(10, String::Concat(title, rm->GetString("Progress_Analyze_Neuron")));
		CvMat input_nn = cvMat(input3Ch->height*input3Ch->width, 3, CV_32FC1, input3Ch->data.fl);
		CvMat output_nn = cvMat(output1Ch->height*output1Ch->width, 1, CV_32FC1, output1Ch->data.fl);

		neuron->predict(&input_nn, &output_nn);

		// Binarize cells/background
		cvThreshold(output1Ch, input_morph, -0.5, 255.0, CV_THRESH_BINARY);
	//}
