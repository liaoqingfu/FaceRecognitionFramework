#include "facerecognition.h"
#include "ui_facerecognition.h"

FaceRecognition::FaceRecognition(QWidget *parent) :
QMainWindow(parent),
ui(new Ui::FaceRecognition)
{
	ui->setupUi(this);
	//    this->setWindowFlags(this->windowFlags() | Qt::Tool);
	QDir *dir = new QDir();

	if (!dir->exists("history/" + QString::fromStdString(PubFun::GetRootDir())))
	{
		dir->mkdir("history/" + QString::fromStdString(PubFun::GetRootDir()));
	}

	max_score = 0.0f;
	downSampleRate = 1;


	// LogWrite, used by every object
	logWriter = new LogWriter(NULL);
	logWriterThd = new QThread(this);
	logWriter->moveToThread(logWriterThd);
	logWriterThd->start();
	// connect signals and slots
	connect(this, SIGNAL(WriteLogSig(QString)), logWriter, SLOT(WriteLogSlot(QString)));

	// Read configuration file
	qRegisterMetaType<cv::Mat>("cv::Mat");
	ReadConFile("conf.xml");

	// 人脸注册
	//peopleRegister = new PeopleRegister(NULL);
	// Video
	videoReader = new VideoReader(NULL);
	connect(videoReader, SIGNAL(SendPlayErrorSig(QString)), this, SLOT(ErrorMsgSlot(QString)));
	connect(videoReader, SIGNAL(WriteLogSig(QString)), logWriter, SLOT(WriteLogSlot(QString)));
	connect(ui->leftWg, SIGNAL(VideoStartSig()), videoReader, SLOT(PlayVideo()));
	connect(ui->leftWg, SIGNAL(VideoPauseSig()), videoReader, SLOT(PauseVideo()));
	connect(ui->leftWg, SIGNAL(VideoClearSig()), videoReader, SLOT(StopVideo()));
	// Move Video Player to Another Thread.
	videoReaderThd = new QThread(this);
	videoReader->moveToThread(videoReaderThd);
	videoReaderThd->start();

	// Camera
	myCamera = new MyCamera(this);
	connect(myCamera, SIGNAL(SendPlayErrorSig(QString)), this, SLOT(ErrorMsgSlot(QString)));
	connect(myCamera, SIGNAL(WriteLogSig(QString)), logWriter, SLOT(WriteLogSlot(QString)));
	connect(this, SIGNAL(SendStartCameraSig()), myCamera, SLOT(StartCameraTimer()));
	connect(ui->leftWg, SIGNAL(VideoClearSig()), myCamera, SLOT(CloseCameraSlot()));
	connect(ui->leftWg, SIGNAL(VideoStartSig()), myCamera, SLOT(CloseCameraSlot()));

	videoSizeFlagForStart = true;

	for (int i = 0; i < 9; i++)
	{
		scene[i] = new QGraphicsScene;
	}
	faceScene = new QGraphicsScene;

	(void *)startTimer(1000);
	// connect signals and slots

	connect(ui->leftWg, SIGNAL(VideoChooseSig()), this, SLOT(VideoChooseSlot()));
	connect(ui->leftWg, SIGNAL(CameraStartSig()), this, SLOT(CameraStartSlot()));
	connect(ui->leftWg, SIGNAL(ImgChooseSig()), this, SLOT(ImgChooseSlot()));
	connect(ui->leftWg, SIGNAL(VideoClearSig()), this, SLOT(ClearVideoWindowSlot()));
	connect(ui->leftWg, SIGNAL(StartRegisterSig()), this, SLOT(StartPeopleRegiste()));
	connect(ui->leftWg, SIGNAL(StartRecogSig()), this, SLOT(StartRecogSlot()));

	cameraPickerStartFlag = false;

	ipCameraHandler = new IpCameraHandler(this);
	faceImageProcess = new FaceImageProcess(NULL);
	faceImageProcessThd = new QThread(this);
	faceImageProcess->moveToThread(faceImageProcessThd);
	faceImageProcessThd->start();
	connect(ipCameraHandler, SIGNAL(SendFrameMat(cv::Mat)), faceImageProcess, SLOT(DataProcessing(cv::Mat)));
	//    if(!faceImageProcess->Init())
	//    {
	//        emit WriteLogSig("[FaceRecognition] FaceImageProcess init FAILED!");
	//        cout << "[FaceRecognition] FaceImageProcess init FAILED!" << endl;
	//        exit(1);
	//    }

	connect(myCamera, SIGNAL(SendFrameMat(cv::Mat)), faceImageProcess, SLOT(DataProcessing(cv::Mat)));
	connect(faceImageProcess, SIGNAL(SendFrameForMainWindow(cv::Mat)), this, SLOT(SetVideoFrameMat(cv::Mat)));
    connect(faceImageProcess, SIGNAL(SendFrameShow(cv::Mat)), this, SLOT(SetFaceDetectedSlot(cv::Mat)));
	connect(this, SIGNAL(SendSingleImgMat(cv::Mat)), faceImageProcess, SLOT(SingleImageProcessing(cv::Mat)));
	connect(videoReader, SIGNAL(SendFrameMat(cv::Mat)), faceImageProcess, SLOT(DataProcessing(cv::Mat)));
	connect(faceImageProcess, SIGNAL(WriteLogSig(QString)), logWriter, SLOT(WriteLogSlot(QString)));
	connect(faceImageProcess, SIGNAL(SendFaceTrueOrFake(bool)), this, SLOT(SetFaceTrueOrFake(bool)));

	recogniseCore = new RecogniseCore(NULL);
	recogniseCoreThd = new QThread(this);
	//    recogniseCore->moveToThread(recogniseCoreThd);
	recogniseCoreThd->start();
	recogniseCoreThd->setPriority(QThread::HighestPriority);
	recogniseCore->SetThd(max_score);
	//    if(!recogniseCore->Init())
	//    {
	//        emit WriteLogSig("[FaceRecognition] RecogniseCore init FAILED!");
	//        exit(1);
	//    }

	connect(faceImageProcess, SIGNAL(SendFrameToRecognise(cv::Mat)), recogniseCore, SLOT(RecogniseSlot(cv::Mat)));
	connect(recogniseCore, SIGNAL(SendAvaliable()), faceImageProcess, SLOT(SetRecogniseCoreAvaliable()));

	//    connect(recogniseCore, SIGNAL(SendResult(QVector<QString>)), ui->resultWg, SLOT(SetResult(QVector<QString>)));
	connect(recogniseCore, SIGNAL(SendResult(cv::Mat, QString, QString, float, bool)), ui->resultWg, SLOT(SetResult(cv::Mat, QString, QString, float, bool)));
	//    connect(ui->resultWg, SIGNAL(SendLogSig(QString)), logWriter, SLOT(WriteLogSlot(QString)));
	connect(recogniseCore, SIGNAL(SendResultLog(QString)), this, SLOT(SetResultLog(QString)));
	connect(recogniseCore, SIGNAL(SendLog(QString)), logWriter, SLOT(WriteLogSlot(QString)));

	connect(faceImageProcess, SIGNAL(SendCurrRegFace(cv::Mat)), this, SLOT(SetCurrRegFace(cv::Mat)));
	// for debug
	connect(faceImageProcess, SIGNAL(WriteLogSig(QString)), this, SLOT(SetResultLog(QString)));
	videoName = "";
	imgName = "";
	ui->mainVideoGv->setScene(scene[0]);

	loadingDialogThd = new QThread(this);
	loadingDialog = new LoadingDialog(NULL);
	loadingDialogThd->start();

	QGraphicsScene *scene = new QGraphicsScene;

	QGraphicsScene *scene1 = new QGraphicsScene;
	ui->mainVideoGv->setScene(scene1);
	ui->mainVideoGv->setAlignment(Qt::AlignHCenter);

	connect(ui->leftWg, SIGNAL(InitRogCoreSig()), this, SLOT(InitRogCoreSlot()));

	program_init_timer = new QTimer(this);
	connect(program_init_timer, SIGNAL(timeout()), this, SLOT(InitRogCoreSlot()));
	program_init_timer->start(500);
	loadingDialog->show();
	//    this->showMaximized();
	this->showMinimized();
}

void FaceRecognition::SetResultLog(QString info)
{
	ui->logTB->append(info);
	if (ui->logTB->document()->toPlainText().size() > 10 * 1024)
	{
		ui->logTB->clear();
	}
}

void FaceRecognition::StartPeopleRegiste()
{
	// First, close ipcamera
	ipCameraHandler->StopRealPlayAndLogout();
	myCamera->CloseCameraSlot();

	faceImageProcess->registerFlag = true;

	ui->mainVideoGv->scene()->clear();

	disconnect(faceImageProcess, SIGNAL(SendFrameForMainWindow(cv::Mat)), this, SLOT(SetVideoFrameMat(cv::Mat)));
	disconnect(faceImageProcess, SIGNAL(SendFrameShow(cv::Mat)), this, SLOT(SetFaceDetectedSlot(cv::Mat)));
	disconnect(faceImageProcess, SIGNAL(SendFaceTrueOrFake(bool)), this, SLOT(SetFaceTrueOrFake(bool)));
	disconnect(faceImageProcess, SIGNAL(SendCurrRegFace(cv::Mat)), this, SLOT(SetCurrRegFace(cv::Mat)));
}

void FaceRecognition::StartRecogSlot()
{
	cout << "Start Recognition..." << endl;
	connect(faceImageProcess, SIGNAL(SendFrameForMainWindow(cv::Mat)), this, SLOT(SetVideoFrameMat(cv::Mat)));
	connect(faceImageProcess, SIGNAL(SendFrameShow(cv::Mat)), this, SLOT(SetFaceDetectedSlot(cv::Mat)));
	connect(faceImageProcess, SIGNAL(SendFaceTrueOrFake(bool)), this, SLOT(SetFaceTrueOrFake(bool)));
	connect(faceImageProcess, SIGNAL(SendCurrRegFace(cv::Mat)), this, SLOT(SetCurrRegFace(cv::Mat)));
	faceImageProcess->registerFlag = false;
}

void FaceRecognition::SetCurrRegFace(cv::Mat frmShow)
{
	//    if(!frmShow.empty())
	//    {
	//        double height = frmShow.rows;
	//        double width = frmShow.cols;

	//        double r = (double)height / (double)width;
	//        QSize size = ui->currRegFaceGV->size();
	//        if ((double)size.height() / (double)size.width() > r)
	//        {
	//            width = size.width();
	//            height = width * r;
	//        }
	//        else
	//        {
	//            height = size.height();
	//            width = height / r;
	//        }

	//        if(width <= 0 || height <=0)
	//        {
	//            QMessageBox::critical(this, "ERROR", "Resize error, Please contact the programmer.");
	//        }
	//        else
	//        {
	//            cv::resize(frmShow, frmShow, Size(width - 1, height - 1), 0, 0, CV_INTER_LINEAR);
	//            QImage img = PubFun::MatToQImage(frmShow);
	//            ui->currRegFaceGV->scene()->clear();
	//            ui->currRegFaceGV->scene()->addPixmap(QPixmap::fromImage(img));
	//            //            QGraphicsScene *scene = new QGraphicsScene;
	//            //            scene->addPixmap(QPixmap::fromImage(img));
	//            //            if(ui->currRegFaceGV->scene() != NULL)
	//            //            {
	//            //                ui->currRegFaceGV->scene()->clear();
	//            //            }
	//            //            ui->currRegFaceGV->setScene(scene);
	//            //            ui->currRegFaceGV->setAlignment(Qt::AlignHCenter);
	//        }
	//    }
	//    else
	//    {
	//        ui->currRegFaceGV->scene()->clear();
	//        emit WriteLogSig("[FaceRecognition] ERROR: Frame Face for Shown is NULL.");
	//    }
}

void FaceRecognition::SetFaceTrueOrFake(bool flag)
{
}

void FaceRecognition::StartIPCameraSlot(int id)
{
	myCamera->CloseCameraSlot();
	QString ip = cameras.at(id).IP;
	QString userName = cameras.at(id).userName;
	QString passwd = cameras.at(id).passWd;

	ipCameraHandler->StartRealPlay(userName, passwd, ip);
}

void FaceRecognition::CameraStartSlot()
{
	ipCameraHandler->StopRealPlayAndLogout();
	// Choose a Camera
	if (!cameraPickerStartFlag)
	{
		cameraPicker = new CameraPicker(this, cameras);
		connect(cameraPicker, SIGNAL(SendCameraIDSig(int)), this, SLOT(GetCameraIDSlot(int)));
		connect(cameraPicker, SIGNAL(SendStartIPCameraSig(int)), this, SLOT(StartIPCameraSlot(int)));
		cameraPickerStartFlag = true;
	}
	cameraPicker->exec();
}

void FaceRecognition::ClearVideoWindowSlot()
{
	scene[0]->clear();
}

void FaceRecognition::SetVideoFrameMat(cv::Mat frm)
{
#ifdef DEBUG
	cout << "FaceRecognition receive a frame." << endl;
#endif
	int height = frm.rows;
	int width = frm.cols;

	if (!frm.empty())
	{
		hwRadio = (double)height / (double)width;
		QSize size = ui->mainVideoGv->size();
		if ((double)size.height() / (double)size.width() > hwRadio)
		{
			width = size.width();
			height = width * hwRadio;
		}
		else
		{
			height = size.height();
			width = height / hwRadio;
		}
		videoSizeFlagForStart = false;
		cv::resize(frm, frm, cv::Size(width - 1, height - 1), 0, 0, CV_INTER_LINEAR);
		QImage img = PubFun::MatToQImage(frm);
		ui->mainVideoGv->scene()->clear();
		ui->mainVideoGv->scene()->addPixmap(QPixmap::fromImage(img));

		//        QGraphicsScene *sceneTmp = new QGraphicsScene;
		//        sceneTmp->addPixmap(QPixmap::fromImage(img));
		//        ui->mainVideoGv->setScene(sceneTmp);
	}
}

void FaceRecognition::GetCameraIDSlot(int ID)
{
	cameraID = ID;
	cout << "Local Camera Was Choosen." << endl;
	myCamera->StartCamera(cameraID);
	emit SendStartCameraSig();
}

void FaceRecognition::resizeEvent(QResizeEvent *)
{
	videoSize = videoSizeOri;
	hwRadio = (double)videoSize.height() / (double)videoSize.width();
	QSize size = ui->mainVideoGv->size();
	if ((double)size.height() / (double)size.width() > hwRadio)
	{
		videoSize.setWidth(size.width());
		videoSize.setHeight(size.width() * hwRadio);
	}
	else
	{
		videoSize.setHeight(size.height());
		videoSize.setWidth(size.height() / hwRadio);
	}
}

void FaceRecognition::VideoChooseSlot()
{
	QString path = QFileDialog::getOpenFileName(this, tr("Open Video"), ".", tr("Video Files(*.avi *.mp4)"));
	if (path.length() == 0)
	{
		QMessageBox::information(this, tr("Error"), tr("No Video has been Selected."));
	}
	else
	{
		ui->mainVideoGv->scene()->clear();

		videoName = path;
		videoReader->SetVideo(videoName);
	}
}

void FaceRecognition::ImgChooseSlot()
{
	QString path = QFileDialog::getOpenFileName(this, tr("Open Image"), ".", tr("Image Files(*.jpg *.png *.bmp *.jpeg)"));
	if (path.length() == 0)
	{
		QMessageBox::information(this, tr("Error"), tr("No Image has been Selected."));
	}
	else
	{
		if (myCamera != NULL)
		{
			myCamera->CloseCameraSlot();
		}
		if (videoReader != NULL)
		{
			videoReader->StopVideo();
		}
		imgName = path;
		imgMat = cv::imread(imgName.toStdString());
		ui->mainVideoGv->scene()->clear();
		cv::Mat frm = cv::imread(path.toStdString());


		if (!frm.empty())
		{
			int height = frm.rows;
			int width = frm.cols;

			hwRadio = (double)height / (double)width;
			QSize size = ui->mainVideoGv->size();
			if ((double)size.height() / (double)size.width() > hwRadio)
			{
				width = size.width();
				height = width * hwRadio;
			}
			else
			{
				height = size.height();
				width = height / hwRadio;
			}
			videoSizeFlagForStart = false;
			cv::resize(frm, frm, cv::Size(width - 1, height - 1), 0, 0, CV_INTER_LINEAR);

			ui->mainVideoGv->scene()->clear();
			QImage img = PubFun::MatToQImage(frm);
			QGraphicsScene *sceneTmp = new QGraphicsScene;
			sceneTmp->addPixmap(QPixmap::fromImage(img));
			ui->mainVideoGv->setScene(sceneTmp);
		}

		emit SendSingleImgMat(imgMat);
	}
}

void FaceRecognition::ReadConFile(QString fileName)
{
	QFile file(fileName);
	if (file.open(QIODevice::ReadOnly))
	{
		dom = new QDomDocument();
		if (!dom->setContent(&file))
		{
			cout << "[FaceRecognition::ReadConFile]# SetContent Failed!" << endl;
			file.close();
		}
		else
		{
			cout << "[FaceRecognition::ReadConFile]# SetContent Succeed!" << endl;
		}

		QDomElement root = dom->documentElement();
		QDomNodeList nodelist = root.childNodes();

		for (int i = 0; i < nodelist.count(); i++)
		{
			QDomNode node = nodelist.at(i);
			if (node.nodeName() == "max_score")
			{
				max_score = node.toElement().attribute("value").toFloat();
			}
			else if (node.nodeName() == "local_ip")
			{
				localIPStr = node.toElement().attribute("value");
			}
			else if (node.nodeName() == "camera")
			{
				CameraInfo cameraInfo;
				cameraInfo.name = node.toElement().attribute("name");
				QDomNodeList itemList = node.childNodes();
				for (int j = 0; j < itemList.count(); j++)
				{
					QDomNode mynode = itemList.at(j);
					if (mynode.nodeName() == "camera_id")
					{
						cameraInfo.ID = mynode.toElement().attribute("value").toUInt();
					}
					else if (mynode.nodeName() == "camera_ip")
					{
						cameraInfo.IP = mynode.toElement().attribute("value");
					}
					else if (mynode.nodeName() == "user_name")
					{
						cameraInfo.userName = mynode.toElement().attribute("value");
					}
					else if (mynode.nodeName() == "password")
					{
						cameraInfo.passWd = mynode.toElement().attribute("value");
					}
				}
				cameras.append(cameraInfo);
			}
			else if (node.nodeName() == "matlab_m_root")
			{
				matlabRoot = node.toElement().attribute("value");
			}
			else if (node.nodeName() == "down_sample_rate")
			{
				downSampleRate = node.toElement().attribute("value").toInt();
			}
			else if (node.nodeName() == "ip_camera_ip")
			{
				ipCameraIP = node.toElement().attribute("value");
			}
			else if (node.nodeName() == "ip_camera_user_name")
			{
				ipCameraUserName = node.toElement().attribute("value");
			}
			else if (node.nodeName() == "ip_camera_passwd")
			{
				ipCameraPasswd = node.toElement().attribute("value");
			}
		}

		file.close();
	}
	else
	{
		emit WriteLogSig("[FaceRecognition] FAILED to Open Configuration File. " + file.errorString());
		cout << "FAILED to Open Configuration File. " + file.errorString().toStdString() << endl;
	}
}

void FaceRecognition::SetRecogStateSlot(bool state)
{
	if (!state)
	{

	}
}

void FaceRecognition::SetFaceDetectedSlot(cv::Mat frmShow)
{
}

void FaceRecognition::SetGv(int i, QString imgName)
{
	QMessageBox::warning(this, tr("Warning"), imgName + "1", QMessageBox::Yes);
	QImage img(imgName);
	QGraphicsScene *scene = new QGraphicsScene;
	scene->addPixmap(QPixmap::fromImage(img));
	switch (i)
	{
	}
}

void FaceRecognition::closeEvent(QCloseEvent * e)
{
	cout << "[FaceRecognition::closeEvent] App is closing." << endl;
	emit WriteLogSig("[FaceRecognition::closeEvent] App is closing.");
	ipCameraHandler->StopRealPlayAndLogout();
	myCamera->CloseCameraSlot();
	faceImageProcessThd->terminate();
	recogniseCoreThd->terminate();
	videoReaderThd->terminate();
	logWriterThd->terminate();

	loadingDialog->close();
	loadingDialog->~LoadingDialog();
	loadingDialogThd->terminate();
	//peopleRegister->close();
}

void FaceRecognition::ErrorMsgSlot(QString info)
{
	QMessageBox::warning(this, tr("Warning"), info, QMessageBox::Yes);
}

void FaceRecognition::InitRogCoreSlot()
{
	//    cout << "Called" << endl;
	program_init_timer->stop();
	if (!faceImageProcess->Init())
	{
		QMessageBox::critical(this, "ERROR", "Face image process init failed!", QMessageBox::Yes);
	}
	//    loadingDialog->SetInfo("Face image process model init succeed.");
	//    cvWaitKey(1);

	if (!recogniseCore->Init())
	{
		QMessageBox::critical(this, "ERROR", "Recognise core init failed!", QMessageBox::Yes);
	}
	loadingDialog->close();
	this->setWindowFlags(this->windowFlags() | Qt::Window);
	this->showMaximized();
	//    this->showFullScreen();
	//    loadingDialog->close();
}

FaceRecognition::~FaceRecognition()
{
	delete ui;
}
