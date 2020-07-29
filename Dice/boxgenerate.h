#include "QtGuiApplication1.h"
#include <QtWidgets/QApplication>
#include <QtCore\qsharedmemory.h>
bool window = 0;
int setting(int argc, char* argv[])
{
	if (!window)
	{
		window = 1;
	}
	else
	{
		MessageBoxA(nullptr, "同时只能打开一个设置窗口", "warining", MB_OK | MB_ICONINFORMATION);
		return 0;
	}
	QApplication a(argc, argv);
	QtGuiApplication5 w;
	w.show();
	a.exec();
	window = 0;
	return 0;
}   
int reply_setting(int argc, char* argv[])
{
	if (!window)
	{
		window = 1;
	}
	else
	{
		MessageBoxA(nullptr, "同时只能打开一个设置窗口", "warining", MB_OK | MB_ICONINFORMATION);
		return 0;
	}
	QApplication b(argc, argv);
	Myreply c;
	c.show();
	b.exec();
	window = 0;
	return 0;
}